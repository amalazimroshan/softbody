#pragma once
#include <iostream>
#include <softbody/vector.hpp>
namespace softbody {
struct collision {
  Vector<float, 2> normal{0.f, 0.f};
  float depth = -std::numeric_limits<float>::infinity();
};

collision find_collision(Vector<float, 2> const& position) {
  Vector<float, 2> direction;
  float depth = (position.y + 20) - 750.f;
  if (depth > 0.f) return collision{Vector<float, 2>{0.f, -1.f}, depth};
  return collision{};
}
}  // namespace softbody
