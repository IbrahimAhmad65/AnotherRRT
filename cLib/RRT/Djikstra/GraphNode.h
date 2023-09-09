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
    double cost = 1e308;
    std::vector<Edge> neighbors;
    bool isVisited = false;

//    ~GraphNode() {
//        std::cout << "deleting node" << std::endl;
//        for (int i = 0; i < neighbors.size(); ++i) {
//            std::cout << "deleting edge" << std::endl;
//            neighbors[i].node.reset();
//        }
//    }

};

bool compareEdgeCost(const Edge &edge1, const Edge &edge2) {
    return edge1.cost < edge2.cost;
}

#endif //CLIB_GRAPHNODE_H
