//
// Created by ibrahim on 9/15/23.
//

#pragma once
namespace swerve {

struct PController {
  double kP;

  double get(double setpoint, double goal) const;
};

} // namespace swerve
