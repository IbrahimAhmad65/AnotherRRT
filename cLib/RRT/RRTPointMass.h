//
// Created by ibrahim on 8/30/23.
//

#ifndef CLIB_RRTPOINTMASS_H
#define CLIB_RRTPOINTMASS_H

#include <vector>
#include <future>
#include <iostream>
#include "Node.h"
#include "Tree.h"
#include "CubicHermite.h"
#include "../Debug/Timer.h"

//double findDistance(const Node &n1, const Node &n2);

double findDistance2d(const Node &n1, const Node &n2);

double findDistance4d(const Node &n1, const Node &n2);

Node extend(const Node &start, const Node &end, double maxAccel);

Node createRandomNode(double maxX, double maxY, double maxVel);

std::vector<Node> findPathFromTree(const Node &goalNode, const Node &startNode, double maxTime);

struct RRTPointMassConfig {
    double maxX;
    double maxY;
    double maxAccel;
    double maxVel;
    double radiusOfCompletion;
    double maxTime;
    int iterations;
};


std::vector<Node> rrtPointMass(const Node &start, const Node &end, RRTPointMassConfig config);

static Node findNearestNode(const Tree &tree, const Node &node);

void findNearestNodeOnRange(const Tree &tree, const Node &node, int start, int end, int index, std::vector<Node>);

void printTree(const Tree &tree);

Node findNearestNodeMultithreaded(const Tree &tree, int threads, const Node &other);

std::vector<Node> rrtPointMass(const Node &start, const Node &end, RRTPointMassConfig config) {
    int threads = 4;
    Tree tree = Tree();
//    __add_Node(tree, start);
    tree.nodes.push_back(start);
    tree.nodes.reserve(config.iterations + 1);
    Node goalNode = end;
    goalNode.time = 1e307;

    for (int i = 0; i < config.iterations; ++i) {
//        std::cout << "Iteration " << i << std::endl;
//        {
//            Timer timer;
        Node rand = createRandomNode(config.maxX, config.maxY, config.maxVel);
        Node nearest;
        nearest = findNearestNode(tree, rand);

        Node newNode;
        newNode = extend(nearest, rand, config.maxAccel);
        if (newNode.time > goalNode.time) {
            continue;
        }
        tree.nodes.push_back(newNode);
        if (findDistance4d(newNode, end) < config.radiusOfCompletion && goalNode.time > newNode.time) {
            goalNode = newNode;
        }
//        }
    }


//    printTree(tree);
    return findPathFromTree(goalNode, start, config.maxTime);

}

void printPath(std::vector<Node> path) {
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

Node findNearestNodeMultithreaded(const Tree &tree, int threads, const Node &other) {
    std::vector<std::future<void>> future;
    std::vector<Node> nodeArr(4);
    int width = tree.nodes.size() / threads;
    for (int j = 0; j < threads; ++j) {
        future.push_back(
                std::async(std::launch::async, findNearestNodeOnRange, tree, other, j * width, (j + 1) * width, j,
                           nodeArr));
    }
    Node nearest = nodeArr[0];
    double dist = findDistance4d(nearest, other);
    for (int j = 1; j < threads; ++j) {
        double distTemp = findDistance4d(nodeArr[j], other);
        if (distTemp < dist) {
            dist = distTemp;
            nearest = nodeArr[j];
        }
    }
    return nearest;
}

void printTree(const Tree &tree) {
    for (int i = 0; i < tree.nodes.size() - 1; ++i) {
        Node n1 = tree.nodes[i];
        Node n2 = tree.nodes[i + 1];
        std::string string =
                R"(\operatorname{polygon}\left(\left()" + std::to_string(n1.x) + "," + std::to_string(n1.y) +
                "\\right),\\left(" + std::to_string(n2.x) + "," + std::to_string(n2.y) + "\\right)\\right)";
        std::cout << string << std::endl;
    }
}

std::vector<Node> findPathFromTree(const Node &goalNode, const Node &startNode, double maxTime) {
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

Node createRandomNode(double maxX, double maxY, double maxVel) {
    double x = ((double) rand() / (RAND_MAX)) * maxX;
    double y = ((double) rand() / (RAND_MAX)) * maxY;
    double vx = 2 * maxVel * (((double) rand() / (RAND_MAX)) - .5);
    double vy = 2 * maxVel * (((double) rand() / (RAND_MAX)) - .5);
    return {x, y, vx, vy, nullptr, 1e307};
}


void
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

Node findNearestNode(const Tree &tree, const Node &node) {
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


double findDistance2d(const Node &n1, const Node &n2) {
    double diffX = n1.x - n2.x;
    double diffY = n1.y - n2.y;
    return sqrt(diffX * diffX + diffY * diffY);
}

double findDistance4d(const Node &n1, const Node &n2) {
    double diffX = n1.x - n2.x;
    double diffY = n1.y - n2.y;
    double diffVX = n1.vx - n2.vx;
    double diffVY = n1.vy - n2.vy;
    return sqrt(diffX * diffX + diffY * diffY + diffVX * diffVX + diffVY * diffVY);
}

//double findDistance(const Node &n1, const Node &n2) {
//    return findDistance4d(n1, n2);
//    return findDistance2d(n1, n2);


#endif //CLIB_RRTPOINTMASS_H
