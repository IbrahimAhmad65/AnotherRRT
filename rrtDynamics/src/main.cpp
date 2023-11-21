#include "RRTPointMass.h"
#include <iostream>
int main()
{
  pmass::Params params = {{{0, 0}, {1, 1}}, {{1, 1}, {2, 2}}, 2, 2, 2, 2, 2};
  pmass::Configs configs = {100, 1};
  auto k = pmass::rrt(params, configs);
  for (auto j : k) {
    std::cout << (*j).p.x << (*j).p.y << std::endl;
  }
  return 0;
}
