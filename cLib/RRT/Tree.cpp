#include <list>
#include <vector>
#include "Node.cpp"
//
// Created by ibrahim on 8/30/23.
//
#pragma once
struct Tree {

public:
     std::vector<Node> nodes;
     static void __add_Node(Tree tree, Node node);
};

void Tree::__add_Node(Tree tree, const Node node) {
    tree.nodes.push_back(node);
}