//
// Created by ibrahim on 9/4/23.
//

#ifndef CLIB_RRTPOINTMASSMANAGER_H
#define CLIB_RRTPOINTMASSMANAGER_H
#include "RRTPointMass.h"
#include <thread>

void rrtPointMassWrapper(const Node &start, const Node &end,
                         RRTPointMassConfig config, std::vector<Node> &arr) {
  Node startCopy = start;

  auto [goalNode, vec] = rrtPointMassTreeGen(startCopy, end, config);
  arr = vec;
}

std::vector<Node> rrtPointMassFull(Node &start, const Node &end,
                                   RRTPointMassConfig config) {
  std::vector<Node> workerTree;
  std::vector<Node> mainTree;
  std::thread worker1(rrtPointMassWrapper, std::ref(start), std::ref(end),
                      config, std::ref(workerTree));

  rrtPointMassWrapper(end, start, config, mainTree);
  worker1.join();
  mainTree.insert(mainTree.end(), workerTree.begin(), workerTree.end());
  for (int i = 0; i < mainTree.size(); ++i) {
    // update all times after tree merge
  }

  //    auto [goal, arr] = rrtPointMassTreeGen(start,end,config);
  //    return findPathFromTree(goal, start, config.maxTime);
}

#endif // CLIB_RRTPOINTMASSMANAGER_H
