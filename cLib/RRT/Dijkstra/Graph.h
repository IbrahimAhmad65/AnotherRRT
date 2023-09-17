//
// Created by ibrahim on 9/4/23.
//
#pragma once

#include "../RRTPointMassUtil.h"
#include "GraphNode.h"
#include <vector>

struct Graph {
  std::vector<GraphNode> nodes;
  static Graph deepCopyGraph(const Graph &graph) {
    Graph newGraph;
    newGraph.nodes.reserve(graph.nodes.size());
    for (const GraphNode &node : graph.nodes) {
      newGraph.nodes.emplace_back(node);
    }
    return newGraph;
  }
};

std::vector<std::shared_ptr<GraphNode>>
generateFilledNodes(const std::vector<GraphNode> &nodes, double maxAccel) {
  std::vector<std::shared_ptr<GraphNode>> filledNodes;
  filledNodes.reserve(nodes.size());
  for (auto g : nodes) {
    filledNodes.push_back(std::make_shared<GraphNode>(g));
  }
  for (int i = 0; i < nodes.size(); ++i) {
    for (int j = i + 1; j < nodes.size(); ++j) {
      Knot startX = {nodes[i].x, nodes[i].vx};
      Knot endX = {nodes[j].x, nodes[j].vx};
      Knot startY = {nodes[i].y, nodes[i].vy};
      Knot endY = {nodes[j].y, nodes[j].vy};
      Cubic xCubic = createCubicFromKnots(startX, endX);
      Cubic yCubic = createCubicFromKnots(startY, endY);
      double time = getSecondsToTraverse(xCubic, yCubic, maxAccel);
      Edge edge = {filledNodes[j], time};
      filledNodes[i]->neighbors.push_back(edge);
      Edge edge2 = {filledNodes[i], time};

      filledNodes[j]->neighbors.push_back(edge2);
    }
  }
  std::vector<std::shared_ptr<Edge>> edges;
  edges.reserve(nodes.size());
  for (auto g : filledNodes) {
    for (Edge e : g->neighbors) {
      edges.push_back(std::make_shared<Edge>(e));
    }
  }

  return filledNodes;
}
