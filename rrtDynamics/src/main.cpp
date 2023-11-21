#include "RRTPointMass.h"
#include <iostream>
int main()
{
  pmass::Params params = {{{0, 0}, {0, 0}}, {{.3, .3}, {1.2, 1.2}}, 2, 2, 3, 3, 2};
  pmass::Configs configs = {100000, .1};
  auto k = pmass::rrt(params, configs);
  std::cout << k.size() << std::endl;
  for (auto j : k) {
    if (j->parent != nullptr) {
      std::cout << "\\operatorname{polygon}\\left(\\left(" << j->p.x << "," << j->p.y << "\\right),\\left(" << j->parent->p.y << "," << j->parent->p.y << "\\right)\\right)" << std::endl;
    }
  }
  return 0;
}
