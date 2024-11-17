#pragma once
#include <softbody/vector.hpp>
namespace softbody {
struct point {
  Vector<float, 2> position;
  Vector<float, 2> velocity;
  uint8_t point_radius = 20;
  bool is_selected = false;
};

}  // namespace softbody
