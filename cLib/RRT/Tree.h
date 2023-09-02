//
// Created by ibrahim on 8/30/23.
//

#ifndef CLIB_TREE_H
#define CLIB_TREE_H

#include <vector>
#include "Node.h"

struct Tree {

public:
    std::vector<Node> nodes;
    static void __add_Node(Tree tree, Node node);
};

void Tree::__add_Node(Tree tree, const Node node) {
    tree.nodes.push_back(node);
}
#endif //CLIB_TREE_H
