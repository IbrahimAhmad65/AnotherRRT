//
// Created by ibrahim on 8/30/23.
//

#ifndef CLIB_RRTPOINTMASS_H
#define CLIB_RRTPOINTMASS_H

#include <vector>
#include "Node.h"
#include "Tree.h"

double findDistance(Node n1, Node n2);

double findDistance2d(Node n1, Node n2);

double findDistance4d(Node n1, Node n2);

Node extend(Node start, Node end, double maxAccel);

Node createRandomNode(double maxX, double maxY, double maxVel);

std::vector<Node> findPathFromTree(const Tree &tree, Node goalNode);

struct RRTPointMassConfig {
    double maxX;
    double maxY;
    double maxAccel;
    double maxVel;
    double radiusOfCompletion;
    int iterations;
};


std::vector<Node> rrtPointMass(Node start, Node end, RRTPointMassConfig config);

Node findNearestNode(const Tree &tree, const Node &node);

std::vector<Node> rrtPointMass(Node start, Node end, RRTPointMassConfig config) {
    Tree tree = Tree();
    tree.__add_Node(tree, start);
    Node goalNode = end;
    for (int i = 0; i < config.iterations; ++i) {
        Node rand = createRandomNode(config.maxX, config.maxY, config.maxVel);
        Node nearest = findNearestNode(tree, rand);
        Node newNode = extend(nearest, rand, config.maxAccel);

        if (findDistance(newNode, end) < config.radiusOfCompletion && goalNode.time > newNode.time) {
            goalNode = newNode;
            std::cout << goalNode.time << std::endl;
        }
    }
    return findPathFromTree(tree, goalNode);

}


std::vector<Node> findPathFromTree(const Tree &tree, Node goalNode) {
    int maxPathLength = 100;
    Node currentNode = goalNode;
    uint8_t i = 0;
    std::vector<Node> fullPath = std::vector<Node>();
    while(!currentNode.parent.expired() && i < maxPathLength){
        fullPath.push_back(currentNode);
        i++;
    }
    return fullPath;
}

Node extend(Node start, Node end, double maxAccel) {
    Node newNode = end;

    Knot xKnotStart = Knot(start.x, start.vx);
    Knot xKnotEnd = Knot(end.x, end.vx);
    Knot yKnotStart = Knot(start.y, start.vy);
    Knot yKnotEnd = Knot(end.y, end.vy);
    Cubic xCubic = createCubicFromKnots(xKnotStart, xKnotEnd);
    Cubic yCubic = createCubicFromKnots(yKnotStart, yKnotEnd);
    double pathTime = getSecondsToTraverse(xCubic, yCubic, maxAccel);
    newNode.time = start.time + pathTime;
    return newNode;
}

Node createRandomNode(double maxX, double maxY, double maxVel) {
    double x = random() * maxX;
    double y = random() * maxY;
    double vx = 2 * maxVel * (random() - .5);
    double vy = 2 * maxVel * (random() - .5);
    return {x, y, vx, vy, nullptr, 1e307};
}


Node findNearestNode(const Tree &tree, const Node &node) {
    double minDistance = 1e307;
    Node nearestNode = Node();
    for (Node n: tree.nodes) {
        double distance = findDistance(n, node);
        if (distance < minDistance) {
            nearestNode = n;
            minDistance = distance;
        }
    }
    return nearestNode;

}


double findDistance2d(Node n1, Node n2) {
    double diffX = n1.x - n2.x;
    double diffY = n1.y - n2.y;
    return sqrt(diffX * diffX + diffY * diffY);
}

double findDistance4d(Node n1, Node n2) {
    double diffX = n1.x - n2.x;
    double diffY = n1.y - n2.y;
    double diffVX = n1.vx - n2.vx;
    double diffVY = n1.vy - n2.vy;
    return sqrt(diffX * diffX + diffY * diffY + diffVX * diffVX + diffVY * diffVY);
}

double findDistance(Node n1, Node n2) {
    return findDistance4d(n1, n2);
    return findDistance2d(n1, n2);
}


#endif //CLIB_RRTPOINTMASS_H
