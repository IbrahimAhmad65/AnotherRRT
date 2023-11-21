#pragma once
#include "Hermite.h"
#include "Point.h"
#include "Vector.h"
#include <vector>
namespace pmass {
struct Configs {
  int iterations;
  double threshold;
};
struct Params {
  Point start, goal;
  double x, y, vx, vy; // maxes
  double maxAccel;
};
std::vector<std::shared_ptr<Point>> rrt(const Params &params, const Configs &configs);
} // namespace pmass