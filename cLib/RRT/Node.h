//
// Created by ibrahim on 8/30/23.
//

#ifndef CLIB_NODE_H
#define CLIB_NODE_H

#include <memory>
#include <utility>

struct Node {
public:
    Node(double x, double y, double vx, double vy);

    Node(double x, double y, double vx, double vy, double time);

    Node(double x, double y, double vx, double vy, std::shared_ptr<Node> parent, double time);

    Node() = default;

    double x;
    double y;
    double vx;
    double vy;
    double time = 1e307;
    // Check if i want a weak pointer here or a full shared one
    std::shared_ptr<Node> parent;

    bool operator==(const Node &other) const {
        return this->x == other.x && this->y == other.y && this->vx == other.vx && this->vy == other.vy;
    }
};


Node::Node(double x, double y, double vx, double vy, std::shared_ptr<Node> parent, double time) {
    this->x = x;
    this->y = y;
    this->vx = vx;
    this->vy = vy;
    this->parent = std::move(parent);
    this->time = time;
}

Node::Node(double x, double y, double vx, double vy, double time) {
    this->x = x;
    this->y = y;
    this->vx = vx;
    this->vy = vy;
    this->time = time;
    this->parent = std::make_shared<Node>();
}

Node::Node(double x, double y, double vx, double vy) {
    this->x = x;
    this->y = y;
    this->vx = vx;
    this->vy = vy;
    this->time = 0;
    this->parent = std::make_shared<Node>();
}

#endif //CLIB_NODE_H
