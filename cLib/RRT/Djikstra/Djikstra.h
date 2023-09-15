//
// Created by ibrahim on 9/4/23.
//

#ifndef CLIB_DJIKSTRA_H
#define CLIB_DJIKSTRA_H

#include <vector>
#include "GraphNode.h"
#include "Graph.h"

// Mutates Start, also all other nodes must be 1e308
std::vector<GraphNode> djikstra_(std::vector<std::shared_ptr<GraphNode>> nodes, std::shared_ptr<GraphNode> start, std::shared_ptr<GraphNode> end) {
    start->cost = 0;
    std::vector<std::shared_ptr<GraphNode>>& unvisited = nodes;

    while (!unvisited.empty()){
        std::sort(unvisited.begin(), unvisited.end(), compareNodeCostSharedPtr);
        std::shared_ptr<GraphNode> currentNode = unvisited[0];
        std::cout << "hola soy bozo" << std::endl;
        for (Edge& e: currentNode->neighbors) {
            if(e.node->cost > e.cost + currentNode->cost){
                e.node->cost = e.cost + currentNode->cost;
                std::cout << e.node->cost;
            }

        }
        unvisited.erase(unvisited.begin(),unvisited.begin()+1);
    }

    return {};
}

#endif //CLIB_DJIKSTRA_H
