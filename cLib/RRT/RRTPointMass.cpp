#include <list>
#include <memory>
#include <vector>
#include "Node.cpp"
#include "Tree.cpp"
#include "Util.cpp"
//
// Created by ibrahim on 8/30/23.
//
#pragma once
double findDistance (Node n1, Node n2);
double findDistance2d (Node n1, Node n2);
double findDistance4d (Node n1, Node n2);
Node createRandomNode();

struct rrtPointMassConfig {
    double maxX;
    double maxY;
    double maxAccel;
    double maxVel;
    int iterations;
};


std::vector<Node> rrtPointMass(Node start, Node end, rrtPointMassConfig config);

Node findNearestNode(const Tree &tree, const Node &node);

std::vector<Node> rrtPointMass(Node start, Node end, rrtPointMassConfig config) {
    Tree tree = Tree();
    tree.__add_Node(tree, start);
    for (int i = 0; i < config.iterations; ++i) {

    }
}


Node createRandomNode(){
    return {random(), random(), random(), random(), nullptr}
}


Node findNearestNode(const Tree& tree, const Node& node) {
    double minDistance = 1e307;
    Node nearestNode = Node();
    for (Node n : tree.nodes) {
        double distance = findDistance(n, node);
        if(distance < minDistance){
            nearestNode = n;
            minDistance = distance;
        }
    }
    return nearestNode;

}


double findDistance2d(Node n1, Node n2){

}

double findDistance4d(Node n1, Node n2){

}
double findDistance(Node n1, Node n2){
    return findDistance4d(n1,n2);
    return findDistance2d(n1,n2);
}





