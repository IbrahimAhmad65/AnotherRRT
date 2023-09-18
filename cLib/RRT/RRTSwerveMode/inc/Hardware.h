//
// Created by ibrahim on 9/14/23.
//
#pragma once
namespace swerve {
struct Falcon {
public:
  double kT = .0192;
  double kV = 509.2;
};
double getTorqueFalcon(double rpm);
} // namespace swerve
