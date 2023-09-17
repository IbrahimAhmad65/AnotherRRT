//
// Created by ibrahim on 9/3/23.
//

#ifndef CLIB_RRTPOINTMASS_H
#define CLIB_RRTPOINTMASS_H

#include "RRTPointMassUtil.h"
inline std::tuple<Node, std::vector<Node>>
rrtPointMassTreeGen(Node &start, const Node &end, RRTPointMassConfig config) {
  Tree tree = Tree();
  start.time = 0;
  tree.nodes.push_back(start);
  tree.nodes.reserve(config.iterations + 1);
  Node goalNode = end;
  goalNode.time = 1e307;

  for (int i = 0; i < config.iterations; ++i) {
    {
      //            Timer timer;
      Node rand = createRandomNode(config.maxX, config.maxY, config.maxVel, i);
      Node nearest;
      nearest = findOptimalParent(tree, rand, config.maxAccel);

      Node newNode;
      newNode = extend(nearest, rand, config.maxAccel);
      if (newNode.time > goalNode.time) {
        continue;
      }
      tree.nodes.push_back(newNode);
      if (findDistance4d(newNode, end) < config.radiusOfCompletion &&
          goalNode.time > newNode.time) {
        goalNode = newNode;
        tree.nodes = findPathFromTree(goalNode, start, config.maxTime);
        //                __pruneTree(tree, goalNode.time);
      }
    }
  }
  return {goalNode, tree.nodes};
}
std::vector<Node> rrtPointMass(Node &start, const Node &end,
                               RRTPointMassConfig config) {
  auto [goal, arr] = rrtPointMassTreeGen(start, end, config);
  return findPathFromTree(goal, start, config.maxTime);
}

#endif // CLIB_RRTPOINTMASS_H
