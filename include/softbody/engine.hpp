#pragma once
#include <iostream>
#include <softbody/collision.hpp>
#include <softbody/point.hpp>
#include <vector>
namespace softbody {

struct distance_constraint {
  uint32_t index0, index1;
  float distance;
};

struct engine {
  std::vector<softbody::point> points;
  point* selected_point = nullptr;
  bool is_point_selected = false;
  Vector<float, 2> gravity{0.f, 681.f};
  float const elasticity = 0.5f;
  float const friction = 0.8f;
  float const floor_height = 750.f;
  uint8_t point_radius = 20;

  std::vector<distance_constraint> constraints;

  void update(float dt) {
    for (auto& p : points) {
      if (&p == selected_point) continue;  // no update if it's selected

      // velocity integration
      p.velocity += gravity * dt;
      p.position += p.velocity * dt;

      // collision resolution
      collision c = find_collision(p.position);
      // std::cout << c.depth << std::endl;
      if (c.depth < 0.f) continue;
      p.position += c.normal * c.depth;
      // Resolve velocity
      auto vn = c.normal * dot(c.normal, p.velocity);  // Normal component
      auto vt = p.velocity - vn;                       // Tangential component
      vn = vn * -elasticity;  // Apply elasticity to normal component (bounce)
      vt *= std::exp(-friction * dt);  // Apply friction to tangential component

      p.velocity = vn + vt;
    }

    // constraint
    int constraint_damping = 10;
    for (auto const& c : constraints) {
      auto& p0 = points[c.index0].position;
      auto& p1 = points[c.index1].position;

      auto delta = p1 - p0;
      auto distance = magnitude(delta);

      auto required_delta = delta * (c.distance / distance);
      float damping_factor = 1.f - std::exp(-constraint_damping * dt);
      auto offset = (required_delta - delta) * damping_factor;

      p0 -= offset / static_cast<float>(2.0);
      p1 += offset / static_cast<float>(2.0);
    }
  }

  void add_point(const Vector<float, 2>& pos) {
    points.push_back({pos, Vector<float, 2>{0.0f, 0.0f}});
  }
};

}  // namespace softbody
