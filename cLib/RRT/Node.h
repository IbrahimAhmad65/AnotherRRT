//
// Created by ibrahim on 8/30/23.
//

#ifndef CLIB_NODE_H
#define CLIB_NODE_H

#include <memory>

struct Node {
public:
    Node(double x, double y,double vx, double vy);
    Node(double x, double y,double vx, double vy, double time);
    Node(double x, double y,double vx, double vy, std::shared_ptr<Node> parent, double time);

    Node() = default;

    double x{};
    double y{};
    double vx{};
    double vy{};
    double time{};
    // Check if i want a weak pointer here or a full shared one
    std::weak_ptr<Node> parent;
};


Node::Node(double x, double y,double vx, double vy, std::shared_ptr<Node> parent, double time) {
    this->x = x;
    this->y = y;
    this-> vx = vx;
    this-> vy = vy;
    this->parent = parent;
    this->time = time;
}

Node::Node(double x, double y, double vx, double vy, double time) {
    this->x = x;
    this->y = y;
    this-> vx = vx;
    this-> vy = vy;
    this->time = time;
    this->parent = std::make_shared<Node>();
}

Node::Node(double x, double y, double vx, double vy) {
    this->x = x;
    this->y = y;
    this-> vx = vx;
    this-> vy = vy;
    this->time = 0;
    this->parent = std::make_shared<Node>();
}
#endif //CLIB_NODE_H
