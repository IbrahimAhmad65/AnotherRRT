//
// Created by ibrahim on 9/15/23.
//

#ifndef CLIB_PCONTROLLER_H
#define CLIB_PCONTROLLER_H

namespace swerve {

struct PController {
  double kP;

  double get(double setpoint, double goal) const;
};

} // namespace swerve
#endif // CLIB_PCONTROLLER_H
