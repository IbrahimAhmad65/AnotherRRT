//
// Created by ibrahim on 9/16/23.
//

#pragma once
namespace swerve {
struct Force {
  double fx;
  double fy;

  Force operator+(const Force &other);
  double operator*(const Force &other);
  Force operator*(double scalar);
};

} // namespace swerve
