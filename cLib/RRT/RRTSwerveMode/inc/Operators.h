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


#endif //CLIB_OPERATORS_H
