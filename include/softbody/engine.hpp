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
  int selected_point_index = -1;
  bool is_point_selected = false;
  Vector<float, 2> gravity{0.f, 681.f};
  float const elasticity = 0.5f;
  float const friction = 0.8f;
  float const floor_height = 750.f;
  uint8_t point_radius = 20;
  float spring_force = 1000.f;

  std::vector<distance_constraint> constraints;

  void update(float dt, Vector<float, 2> mouse_position) {
    if(selected_point_index >= 0){
      point& p = points[selected_point_index];
      float tracking_stiffnes = 30.f;
      p.velocity = (mouse_position - p.position) * tracking_stiffnes;
    }

    for(size_t i=0;i<points.size();i++){
      if (i == selected_point_index) 
      {
        point& p = points[selected_point_index];
        p.position += p.velocity * dt;
        continue;  // no update if it's selected
      }

      point &p = points[i];
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
    for (auto const& c : constraints) {
      auto& p0 = points[c.index0].position;
      auto& p1 = points[c.index1].position;
      auto& v0 = points[c.index0].velocity;
      auto& v1 = points[c.index1].velocity;

      auto delta = p1 - p0;
      auto distance = magnitude(delta);
      auto direction = delta / distance;

      auto required_delta = direction * c.distance;
      auto force = (required_delta - delta) * spring_force;

      // if(!points[c.index0].fixed) 
      v0 -= force * dt;
      // if(!points[c.index1].fixed) 
      v1 += force * dt;

      float vrel = dot(v1-v0, direction);
      float damping_factor = expf(-spring_force * dt);
      float new_vrel = vrel * damping_factor;
      float vrel_delta = new_vrel - vrel;

      auto impulse = direction * (vrel_delta * 0.5f);
      // if(!points[c.index0].fixed) 
      v0 -= impulse;
      // if(!points[c.index1].fixed) 
      v1 += impulse;
    }
  }

  void add_point(const Vector<float, 2>& pos) {
    points.push_back({pos, Vector<float, 2>{0.0f, 0.0f}, false});
  }
};

}  // namespace softbody
