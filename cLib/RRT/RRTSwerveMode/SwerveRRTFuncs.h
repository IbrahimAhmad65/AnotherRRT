//
// Created by ibrahim on 9/15/23.
//

#ifndef CLIB_SWERVERRTFUNCS_H
#define CLIB_SWERVERRTFUNCS_H

#include "SwerveNode.h"

namespace swerve {
    swerve::Node
    iterateWithController(const swerve::Node &start, const swerve::Node &end, const swerve::SwerveConfig &config,
                          const swerve::RRTConfig &rrtConfig) {
//        Pose error = end.state.position - start.state.position;
//        Pose errorOfVelocities = end.state.firstDerivative - start.state.firstDerivative;
//        swerve::Force positionTranslationalForce = {config.xController.get(end.state.position.p.x, error.p.x),
//                                                    config.yController.get(end.state.position.p.y, error.p.y)};
//        swerve::Force velTranslationalForce = {config.vxController.get(end.state.firstDerivative.p.y, errorOfVelocities.p.x),
//                                               config.vyController.get(end.state.firstDerivative.p.y, errorOfVelocities.p.y)};
//        swerve::F
//// Just do forward kinematics for swerve then grab the dynamics for the output, kinda expensive, but i can think of a better way rn bc its almost 4 am sadness
    }


    swerve::Node extend(const swerve::Node &start, const swerve::Node &end, const swerve::SwerveConfig &config,
                        const swerve::RRTConfig &rrtConfig) {
        int count = 0;
        SwerveState currentState = start.state;
        while (count < rrtConfig.extendIterations &&
               (currentState.position - end.state.position).getMagnitude() < rrtConfig.extendthreshold) {

        }


    }


}
#endif //CLIB_SWERVERRTFUNCS_H
