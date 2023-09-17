//
// Created by ibrahim on 9/4/23.
//

#ifndef CLIB_DIJKSTRA_H
#define CLIB_DIJKSTRA_H

#include "Graph.h"
#include "GraphNode.h"
#include <vector>

// Mutates Start, also all other nodes must be 1e308
std::vector<GraphNode> dijkstra_(std::vector<std::shared_ptr<GraphNode>> nodes,
                                 std::shared_ptr<GraphNode> start,
                                 std::shared_ptr<GraphNode> end) {
  start->cost = 0;
  std::vector<std::shared_ptr<GraphNode>> &unvisited = nodes;

  while (!unvisited.empty()) {
    std::sort(unvisited.begin(), unvisited.end(), compareNodeCostSharedPtr);
    std::shared_ptr<GraphNode> currentNode = unvisited[0];
    std::cout << "hola soy bozo" << std::endl;
    for (Edge &e : currentNode->neighbors) {
      if (e.node->cost > e.cost + currentNode->cost) {
        e.node->cost = e.cost + currentNode->cost;
        std::cout << e.node->cost;
      }
    }
    unvisited.erase(unvisited.begin(), unvisited.begin() + 1);
  }

  return {};
}

#endif // CLIB_DIJKSTRA_H
