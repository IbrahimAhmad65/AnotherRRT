#pragma once
#include "Vector.h"
#include <memory>
namespace pmass {
struct Point {
  Vector p;
  Vector v;
  // std::weak_ptr<Point> parent;
  Point *parent;
  double cost = 1e300;
};
} // namespace pmass
