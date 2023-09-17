//
// Created by ibrahim on 9/16/23.
//

#ifndef CLIB_OPERATORS_H
#define CLIB_OPERATORS_H
#include "RandomForces.h"
#include "PController.h"
#include "Velocity.h"
#include "Pose.h"

namespace swerve{
    double dot(swerve::ModulePosition &mod1, swerve::ModulePosition &mod2);
    double dot(swerve::Force &force1, swerve::Force &force2);
    double dot(swerve::Velocity &vel1, swerve::Velocity &vel2);
    double dot(swerve::Force &force, swerve::Velocity &vel);
    double dot(swerve::Velocity &vel, swerve::Force &force);
    double dot(swerve::ModulePosition &mod, swerve::Velocity &vel);
    double dot(swerve::Velocity &vel, swerve::ModulePosition &mod);
    double dot(swerve::ModulePosition &mod, swerve::Force &force);
    double dot(swerve::Force &force, swerve::ModulePosition &mod);
    Pose plus (Pose &pose, Velocity &vel);
}
double swerve::dot(swerve::ModulePosition &mod1, swerve::ModulePosition &mod2) {
    return mod1.x * mod2.x + mod1.y * mod2.y;
}
double swerve::dot(swerve::Force &force1, swerve::Force &force2) {
    return force1.fx * force2.fy + force1.fy * force2.fy;
}
double swerve::dot(swerve::Velocity &vel1, swerve::Velocity &vel2) {
    return vel1.vx * vel2.vx + vel1.vy * vel2.vy;
}
double swerve::dot(swerve::Force &force, swerve::Velocity &vel) {
    return force.fx * vel.vx + force.fy * vel.vy;
}
double swerve::dot(swerve::Velocity &vel, swerve::Force &force) {
    return force.fx * vel.vx + force.fy * vel.vy;
}
double swerve::dot(swerve::ModulePosition &mod, swerve::Velocity &vel) {
    return mod.x * vel.vx + mod.y * vel.vy;
}
double swerve::dot(swerve::Velocity &vel, swerve::ModulePosition &mod) {
    return mod.x * vel.vx + mod.y * vel.vy;
}
double swerve::dot(swerve::ModulePosition &mod, swerve::Force &force) {
    return mod.x * force.fx + mod.y * force.fy;
}
double swerve::dot(swerve::Force &force, swerve::ModulePosition &mod) {
    return mod.x * force.fx + mod.y * force.fy;
}

swerve::Pose swerve::plus(swerve::Pose &pose, swerve::Velocity &vel) {
    return {pose.p.x + vel.vx, pose.p.y + vel.vy, pose.theta};
}

#endif //CLIB_OPERATORS_H
