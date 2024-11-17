#pragma once
#include <iostream>
#include <softbody/collision.hpp>
#include <softbody/point.hpp>
#include <vector>
namespace softbody {

struct engine {
  std::vector<softbody::point> points;
  Vector<float, 2> gravity{0.f, 681.f};
  float const elasticity = 0.5f;
  float const friction = 0.8f;
  float const floor_height = 750.f;

  void update(float dt) {
    for (auto& p : points) {
      p.velocity += gravity * dt;
      p.position += p.velocity * dt;

      collision c = find_collision(p.position);
      // std::cout << c.depth << std::endl;
      if (c.depth < 0.f) continue;

      p.position += c.normal * c.depth;
      // Resolve velocity
      auto vn = c.normal * dot(c.normal, p.velocity);  // Normal component
      auto vt = p.velocity - vn;                       // Tangential component

      // Apply elasticity to normal component (bounce)
      vn = vn * -elasticity;

      // Apply friction to tangential component
      vt *= std::exp(-friction * dt);

      // Combine components
      p.velocity = vn + vt;
    }
  }

  void add_point(const Vector<float, 2>& pos) {
    points.push_back({pos, Vector<float, 2>{0.0f, 0.0f}});
  }
};

}  // namespace softbody
