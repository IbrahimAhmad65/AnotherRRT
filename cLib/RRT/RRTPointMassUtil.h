//
// Created by ibrahim on 8/30/23.
//

#ifndef CLIB_RRTPOINTMASSUTIL_H
#define CLIB_RRTPOINTMASSUTIL_H

#include <vector>
#include <future>
#include <iostream>
#include "Node.h"
#include "Tree.h"
#include "CubicHermite.h"
#include "../Debug/Timer.h"


struct RRTPointMassConfig {
    double maxX;
    double maxY;
    double maxAccel;
    double maxVel;
    double radiusOfCompletion;
    double maxTime;
    int iterations;
};


inline double findDistance4d(const Node &n1, const Node &n2) {
    double diffX = n1.x - n2.x;
    double diffY = n1.y - n2.y;
    double diffVX = n1.vx - n2.vx;
    double diffVY = n1.vy - n2.vy;
    return (diffX * diffX + diffY * diffY + diffVX * diffVX + diffVY * diffVY);
}


std::vector<Node> rrtPointMass(const Node &start, const Node &end, RRTPointMassConfig config);

inline void printPath(std::vector<Node> path) {
    if (path.size() > 0) {
        for (int i = 0; i < path.size() - 1; ++i) {
            Node n1 = path[i];
            Node n2 = path[i + 1];
            std::string string =
                    R"(\operatorname{polygon}\left(\left()" + std::to_string(n1.x) + "," + std::to_string(n1.y) +
                    "\\right),\\left(" + std::to_string(n2.x) + "," + std::to_string(n2.y) + "\\right)\\right)";
            std::cout << string << std::endl;
        }
    }
}


inline void printTree(const Tree &tree) {
    for (int i = 0; i < tree.nodes.size() - 1; ++i) {
        Node n1 = tree.nodes[i];
        Node n2 = tree.nodes[i + 1];
        std::string string =
                R"(\operatorname{polygon}\left(\left()" + std::to_string(n1.x) + "," + std::to_string(n1.y) +
                "\\right),\\left(" + std::to_string(n2.x) + "," + std::to_string(n2.y) + "\\right)\\right)";
        std::cout << string << std::endl;
    }
}

inline std::vector<Node> findPathFromTree(const Node &goalNode, const Node &startNode, double maxTime) {
    int maxPathLength = 100;
    Node currentNode = goalNode;
    uint8_t i = 0;
    std::vector<Node> fullPath = std::vector<Node>();
    if (goalNode.time > maxTime) {
        return fullPath;
    }
    while (!(currentNode == startNode) && i < maxPathLength) {
        fullPath.push_back(currentNode);
        currentNode = *currentNode.parent;
        i++;
    }
    if (!fullPath.empty()) {
        fullPath.push_back(startNode);
    }
    return fullPath;
}

Node extend(const Node &start, const Node &end, double maxAccel) {
    Node newNode = end;

    Knot xKnotStart = {start.x, start.vx};
    Knot xKnotEnd = {end.x, end.vx};
    Knot yKnotStart = {start.y, start.vy};
    Knot yKnotEnd = {end.y, end.vy};
    Cubic xCubic = createCubicFromKnots(xKnotStart, xKnotEnd);
    Cubic yCubic = createCubicFromKnots(yKnotStart, yKnotEnd);
    double pathTime = getSecondsToTraverse(xCubic, yCubic, maxAccel);
    newNode.time = start.time + pathTime;
    newNode.parent = std::make_shared<Node>(start);
    return newNode;
}


inline Node createRandomNode(double maxX, double maxY, double maxVel, int seed) {
//    double rand = random(seed);

    double x = (((double) rand()) / RAND_MAX) * maxX;
    double y = (((double) rand()) / RAND_MAX) * maxY;
    double vx = 2 * maxVel * ((((double) rand()) / RAND_MAX) - .5);
    double vy = 2 * maxVel * ((((double) rand()) / RAND_MAX) - .5);
//    double x = (random(seed)) * maxX;
//    double y = (random(seed >> 1)) * maxY;
//    double vx = 2 * maxVel * ((random(seed >> 2)) - .5);
//    double vy = 2 * maxVel * ((random(seed >> 3)) - .5);
    return {x, y, vx, vy, nullptr, 1e307};
}

inline void
findNearestNodeOnRange(const Tree &tree, const Node &node, int start, int end, int index, std::vector<Node> nodeArray) {
    double minDistance = 1e307;
    Node nearestNode = Node();
    for (int i = start; i < end; ++i) {
        double distance = findDistance4d(tree.nodes[i], node);
        if (distance < minDistance) {
            nearestNode = tree.nodes[i];
            minDistance = distance;
        }
    }
    nodeArray[index] = nearestNode;
}


inline Node findNearestNode(const Tree &tree, const Node &node) {
    double minDistance = 1e307;
    Node nearestNode = Node();
    for (int i = 0; i < tree.nodes.size(); ++i) {
        double distance = findDistance4d(tree.nodes[i], node);
        if (distance < minDistance) {
            nearestNode = tree.nodes[i];
            minDistance = distance;
        }
    }
    return nearestNode;

}

inline double findDistance2d(const Node &n1, const Node &n2) {
    double diffX = n1.x - n2.x;
    double diffY = n1.y - n2.y;
    return sqrt(diffX * diffX + diffY * diffY);
}

inline Node findOptimalParent(const Tree &tree, const Node &node, double maxVel) {
    double minTime = 1e307;
    Node n;
    for (int i = 0; i < tree.nodes.size(); i++) {
        double timeOfParent = tree.nodes[i].time;
        Cubic xCubic = createCubicFromKnots({tree.nodes[i].x, tree.nodes[i].vx}, {node.x, node.vx});
        Cubic yCubic = createCubicFromKnots({tree.nodes[i].y, tree.nodes[i].vy}, {node.y, node.vy});
        double pathTime = getSecondsToTraverse(xCubic, yCubic, maxVel);
        double totalTime = timeOfParent + pathTime;
        if (totalTime < minTime) {
            n = tree.nodes[i];
            minTime = totalTime;
        }
    }
    return n;
}

inline void __pruneTree(Tree &tree, double maxCost) {
    for (int i = 0; i < tree.nodes.size(); i++) {
        if (tree.nodes[i].time > maxCost) {
            std::remove(tree.nodes.begin(), tree.nodes.end(), tree.nodes[i]);
//            std::cout << "Pruned node" << std::endl;
        }
    }
}

//double findDistance(const Node &n1, const Node &n2) {
//    return findDistance4d(n1, n2);
//    return findDistance2d(n1, n2);


#endif //CLIB_RRTPOINTMASSUTIL_H
