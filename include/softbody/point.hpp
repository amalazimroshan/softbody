#pragma once
#include <softbody/vector.hpp>
namespace softbody {
struct point {
  Vector<float, 2> position;
  Vector<float, 2> velocity;
};

}  // namespace softbody
