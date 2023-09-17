//
// Created by ibrahim on 9/4/23.
//

#ifndef CLIB_GRAPHNODE_H
#define CLIB_GRAPHNODE_H

#include <vector>
#include <memory>

struct GraphNode;
struct Edge {
    std::shared_ptr<GraphNode> node;
    double cost;
};

struct GraphNode {

    double x;
    double y;
    double vx;
    double vy;
    double cost = std::numeric_limits<double>::infinity();
    std::vector<Edge> neighbors;
    bool isVisited = false;

    GraphNode(double x, double y, double vx, double vy) : x(x), y(y), vx(vx), vy(vy) {}
    GraphNode(double x, double y, double vx, double vy,double cost, std::vector<Edge> edge) : x(x), y(y), vx(vx), vy(vy), cost(cost), neighbors(edge) {}

    GraphNode(const GraphNode &node) {
        x = node.x;
        y = node.y;
        vx = node.vx;
        vy = node.vy;
        cost = node.cost;
        neighbors.reserve(node.neighbors.size());
        for (const Edge &edge: node.neighbors) {
            neighbors.push_back(edge);
        }
    }

//    ~GraphNode() {
//        std::cout << "deleting node" << std::endl;
//        for (int i = 0; i < neighbors.size(); ++i) {
//            std::cout << "deleting edge" << std::endl;
//            neighbors[i].node.reset();
//        }
//    }

};

bool compareNodeCostSharedPtr(const std::shared_ptr<GraphNode> &node1, const std::shared_ptr< GraphNode> &node2) {
    return node1->cost < node2->cost;
}

bool compareNodeCost(const GraphNode &node1, const GraphNode &node2) {
    return node1.cost < node2.cost;
}

bool compareEdgeCost(const Edge &edge1, const Edge &edge2) {
    return edge1.cost < edge2.cost;
}

#endif //CLIB_GRAPHNODE_H
