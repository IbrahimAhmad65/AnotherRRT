//
// Created by ibrahim on 9/16/23.
//

#ifndef CLIB_FORCENTORQUE_H
#define CLIB_FORCENTORQUE_H

#include "Force.h"
#include <valarray>

namespace swerve {

struct ForceNTorque {
  swerve::Force f;
  double torque{};
};
} // namespace swerve
#endif // CLIB_FORCENTORQUE_H
