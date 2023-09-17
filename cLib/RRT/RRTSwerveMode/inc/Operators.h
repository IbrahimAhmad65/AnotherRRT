//
// Created by ibrahim on 9/16/23.
//
#pragma once
#include "PController.h"
#include "Pose.h"
#include "RandomForces.h"
#include "Velocity.h"

namespace swerve {
double dot(swerve::ModulePosition &mod1, swerve::ModulePosition &mod2);
double dot(swerve::Force &force1, swerve::Force &force2);
double dot(swerve::Velocity &vel1, swerve::Velocity &vel2);
double dot(swerve::Force &force, swerve::Velocity &vel);
double dot(swerve::Velocity &vel, swerve::Force &force);
double dot(swerve::ModulePosition &mod, swerve::Velocity &vel);
double dot(swerve::Velocity &vel, swerve::ModulePosition &mod);
double dot(swerve::ModulePosition &mod, swerve::Force &force);
double dot(swerve::Force &force, swerve::ModulePosition &mod);
Pose plus(Pose &pose, Velocity &vel);
} // namespace swerve
