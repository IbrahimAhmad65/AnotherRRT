#pragma once
#include "Point.h"
#include <memory>
#include <vector>
namespace pmass {
struct Tree {
  std::vector<std::shared_ptr<Point>> list;
  std::shared_ptr<Point> root;
};
} // namespace pmass
