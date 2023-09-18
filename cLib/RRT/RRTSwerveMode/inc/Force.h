//
// Created by ibrahim on 9/16/23.
//

#pragma once
namespace swerve {
struct Force {
  double fx;
  double fy;

  Force operator+(const Force &other) const;
  double operator*(const Force &other) const;
  Force operator*(double scalar) const;
};

} // namespace swerve
