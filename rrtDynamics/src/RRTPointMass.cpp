#include "RRTPointMass.h"
#include "Hermite.h"
#include "Point.h"
#include "Tree.h"
#include "Vector.h"
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>
namespace pmass {
Point *findNearestPoint(const std::vector<std::shared_ptr<Point>> &list, const Point &point);
Point *getOptimalParent(const std::vector<std::shared_ptr<Point>> &list, const Point &point, const Params &params);
std::vector<std::shared_ptr<Point>> retraceFromEnd(const std::vector<std::shared_ptr<Point>> list, Point *end);
Point createRandomPoint(const Params &params);
double timeToInterp(const Point &start, const Point &end, const Params &params);
double findDistanceBetween(const Point &p1, const Point &p2)
{
  double xDiff = p1.p.x - p2.p.x;
  double yDiff = p1.p.y - p2.p.y;
  double xDiffV = p1.v.x - p2.v.x;
  double yDiffV = p1.v.y - p2.v.y;
  return std::sqrt(xDiff * xDiff + yDiff * yDiff + xDiffV * xDiffV + yDiffV * yDiffV);
}
std::vector<std::shared_ptr<Point>> rrt(const Params &params, const Configs &configs)
{
  // Prime Tree
  Tree tree = Tree();
  tree.root = std::make_shared<Point>(params.start);
  tree.list = std::vector<std::shared_ptr<Point>>();
  tree.list.reserve(configs.iterations);
  tree.list.push_back(tree.root);
  Point goal = params.goal;
  for (int itr = 0; itr < configs.iterations; itr++) {
    // Find and link a Point
    Point p = createRandomPoint(params);
    p.parent = getOptimalParent(tree.list, p, params);
    p.cost = p.parent->cost + timeToInterp(*p.parent, p, params);
    tree.list.push_back(std::make_shared<Point>(p));
    std::cout << findDistanceBetween(p, goal) << std::endl;
    std::cout << (findDistanceBetween(p, goal) < configs.threshold) << std::endl;
    if (findDistanceBetween(p, goal) < configs.threshold) {
      return retraceFromEnd(tree.list, &p);
    }
  }
  return {};
}
Point *findNearestPoint(const std::vector<std::shared_ptr<Point>> &list, const Point &point)
{
  double minDistance = 1e300;
  auto closest = list[0];
  for (auto k : list) {
    double dist = findDistanceBetween(*k, point);
    if (dist < minDistance) {
      closest = k;
      minDistance = dist;
    }
  }
  return closest.get();
}
Point createRandomPoint(const Params &params)
{
  double randX = params.x * (2 * ((double)rand() / (RAND_MAX)) - 1);
  double randY = params.y * (2 * ((double)rand() / (RAND_MAX)) - 1);
  double randVX = params.vx * (2 * ((double)rand() / (RAND_MAX)) - 1);
  double randVY = params.vy * (2 * ((double)rand() / (RAND_MAX)) - 1);
  return {{randX, randY}, {randVX, randVY}, nullptr};
}

double timeToInterp(const Point &start, const Point &end, const Params &params)
{
  Vector xCouple = {start.p.x, start.v.x};
  Vector xCoupleEnd = {end.p.x, end.v.x};
  Vector yCouple = {start.p.y, start.v.y};
  Vector yCoupleEnd = {end.p.y, end.v.y};
  Cubic xCubic = createCubicFromKnots(xCouple, xCoupleEnd);
  Cubic yCubic = createCubicFromKnots(yCouple, yCoupleEnd);
  double timeToInterp = getSecondsToTraverse(xCubic, yCubic, params.maxAccel);
  return timeToInterp;
}
Point *getOptimalParent(const std::vector<std::shared_ptr<Point>> &list, const Point &point, const Params &params)
{
  double minCost = 1e300;
  auto parent = list[0];
  for (auto k : list) {
    double cost = k->cost + timeToInterp(*k, point, params);
    if (cost < minCost) {
      parent = k;
      minCost = cost;
    }
  }
  return parent.get();
}
std::vector<std::shared_ptr<Point>> retraceFromEnd(const std::vector<std::shared_ptr<Point>> list, Point *end)
{
  std::vector<std::shared_ptr<Point>> pathFromGoal = std::vector<std::shared_ptr<Point>>();
  Point *current = end;
  while (current->parent != nullptr) {
    pathFromGoal.push_back(std::make_shared<Point>(*current));
    current = current->parent;
  }
  pathFromGoal.push_back(std::make_shared<Point>(*current));
  return pathFromGoal;
}
} // namespace pmass