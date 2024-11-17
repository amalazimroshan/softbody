#pragma once
#include <iostream>
#include <softbody/vector.hpp>
namespace softbody {
struct collision {
  Vector<float, 2> normal{0.f, 0.f};
  float depth = -std::numeric_limits<float>::infinity();
};

collision plane_collision(Vector<float, 2> const& position,
                          Vector<float, 2> const& plane_normal,
                          float plane_distance) {
  float depth = -1 * dot(position, plane_normal) - plane_distance;
  if (depth > 0.f) return collision{plane_normal, depth};
  return collision{};
};

collision find_collision(Vector<float, 2> const& position,
                         float window_width = 800.f,
                         float window_height = 750.f,
                         float point_radius = 20.f) {
  collision result{};
  collision floor = plane_collision(position, Vector<float, 2>{0.f, -1.f},
                                    (window_height - point_radius));
  if (floor.depth > result.depth) result = floor;

  collision ceiling =
      plane_collision(position, Vector<float, 2>{0.f, 1.f}, (0 - point_radius));
  if (ceiling.depth > result.depth) result = ceiling;

  collision right = plane_collision(position, Vector<float, 2>{-1.f, 0.f},
                                    (window_width - point_radius));
  if (right.depth > result.depth) result = right;

  collision left =
      plane_collision(position, Vector<float, 2>{1.f, 0.f}, (0 - point_radius));
  if (left.depth > result.depth) result = left;

    return result;
}
}  // namespace softbody
