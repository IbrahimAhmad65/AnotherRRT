//
// Created by ibrahim on 9/4/23.
//

#ifndef CLIB_DJIKSTRA_H
#define CLIB_DJIKSTRA_H

#include <vector>
#include "GraphNode.h"
#include "Graph.h"

// Mutates Start, also all other nodes must be 1e308
std::vector<GraphNode> __djikstra(const Graph &graph, GraphNode &start, GraphNode &end) {
    // mark all finalPath as unvisited
//    std::vector<GraphNode> copy = graph.nodes;

    std::vector<GraphNode> unvisited = graph.nodes;
    std::vector<GraphNode> visited;
    visited.reserve(graph.nodes.size());
    // assign a tenative distance of zero to the start and infinity to all other finalPath
//    start.cost = 0;/
    start.cost = 0;
    GraphNode &currentNode = start;

    int count = 0;
    GraphNode endCopy = end;
    while (count < unvisited.size() + 4) {
//        currentNode.x = 5;
        // for the current node, consider all of its unvisited neighbors and calculate their tentative distances
        for (Edge &e: currentNode.neighbors) {
            e.node->cost = fmin(e.cost + currentNode.cost, e.node->cost);
            e.cost = fmin(e.node->cost - currentNode.cost, e.cost);
        }
        // When we are done considering all of the neighbors of the current node, mark the current node as visited
        GraphNode &newMinNode = *currentNode.neighbors[0].node;
        auto minCostEdgeIter = std::min_element(currentNode.neighbors.begin(), currentNode.neighbors.end(),
                                                compareEdgeCost);
        Edge minCostEdge = *minCostEdgeIter;
        newMinNode = *minCostEdge.node;
        bool checkX = currentNode.x == endCopy.x;
        bool checkY = currentNode.y == endCopy.y;
        bool checkVx = currentNode.vx == endCopy.vx;
        bool checkVy = currentNode.vy == endCopy.vy;
        if (checkX && checkY && checkVx && checkVy) {
//             find path from goal to start
            std::cout << "hey" << std::endl;
            break;
        }
        const GraphNode &remove = currentNode;
        visited.push_back(remove);
        for (int i = 0; i < unvisited.size(); ++i) {
            if (remove.x == unvisited[i].x && remove.y == unvisited[i].y && remove.vx == unvisited[i].vx &&
                remove.vy == unvisited[i].vy) {
                unvisited.erase(unvisited.begin() + i);
                break;
            }
        }
        currentNode = newMinNode;
        count++;
    }

//    const auto startIndex = std::find(unvisited.begin(), unvisited.end(),remove);
//    unvisited.erase(startIndex);
//    }
    GraphNode &currentNodeSearching = end;
    std::vector<GraphNode> finalPath;
    finalPath.push_back(currentNodeSearching);
    while (count < visited.size() + 4) {
        Edge &minEdge = currentNodeSearching.neighbors[0];
        for (const Edge &e: currentNodeSearching.neighbors) {
            if (minEdge.node->cost > e.node->cost) {
                minEdge = e;
            }
        }
        currentNodeSearching = *minEdge.node.get();


        std::cout << "hey v2" << std::endl;
        finalPath.push_back(currentNodeSearching);
        if (currentNodeSearching.x == start.x && currentNodeSearching.y == start.y &&
            currentNodeSearching.vx == start.vx && currentNodeSearching.vy == start.vy) {
            break;
        }

        count++;
    }
    return finalPath;
}

#endif //CLIB_DJIKSTRA_H
