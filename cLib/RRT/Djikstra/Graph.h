//
// Created by ibrahim on 9/4/23.
//

#ifndef CLIB_GRAPH_H
#define CLIB_GRAPH_H

#include <vector>
#include "GraphNode.h"
#include "../RRTPointMassUtil.h"

struct Graph{
    std::vector<GraphNode> nodes;

    static Graph deepCopyGraph(const Graph& graph){
        Graph newGraph;
        newGraph.nodes.reserve(graph.nodes.size());
        for (GraphNode node: graph.nodes) {
            newGraph.nodes.push_back(GraphNode(node));
        }
        return newGraph;
    }
};

std::vector<GraphNode> generateFilledNodes(const std::vector<GraphNode>& nodes, double maxAccel){
    std::vector<GraphNode> filledNodes = nodes;
//    filledNodes.reserve(nodes.size());
    for (int i = 0; i < nodes.size(); ++i) {
        for (int j = i+1; j < nodes.size(); ++j) {
            Knot startX = {nodes[i].x, nodes[i].vx};
            Knot endX = {nodes[j].x, nodes[j].vx};
            Knot startY = {nodes[i].y, nodes[i].vy};
            Knot endY = {nodes[j].y, nodes[j].vy};
            Cubic xCubic = createCubicFromKnots(startX, endX);
            Cubic yCubic = createCubicFromKnots(startY, endY);
            double time = getSecondsToTraverse(xCubic, yCubic, maxAccel);
            Edge edge = {std::make_shared<GraphNode>(nodes[j]), time};
            filledNodes[i].neighbors.push_back(edge);
            Edge edge2 = {std::make_shared<GraphNode>(nodes[i]), time};
            filledNodes[j].neighbors.push_back(edge2);
//            GraphNode iNode = nodes[i];

        }
    }
    std::vector<std::shared_ptr< Edge>> edges;
    edges.reserve(nodes.size());
    for (GraphNode g: filledNodes) {
        for (Edge e: g.neighbors) {
            edges.push_back(std::make_shared<Edge>(e));
        }
    }

    return filledNodes;

}
#endif //CLIB_GRAPH_H
