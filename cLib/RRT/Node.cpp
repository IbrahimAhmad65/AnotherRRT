#include <memory>

//
// Created by ibrahim on 8/30/23.
//
#pragma once
struct Node {
public:
    Node(double x, double y,double vx, double vy, std::shared_ptr<Node> parent);

    Node() = default;

    double x;
    double y;
    double vx;
    double vy;
    std::shared_ptr<Node> parent;
};


Node::Node(double x, double y,double vx, double vy, std::shared_ptr<Node> parent) {
    this->x = x;
    this->y = y;
    this-> vx = vx;
    this-> vy = vy;
    this->parent = parent;
}
