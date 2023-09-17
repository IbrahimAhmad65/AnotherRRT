
// Created by ibrahim on 9/17/23.
//
#include "../inc/Force.h"
namespace swerve{

    struct Force {
        double fx;
        double fy;

        Force operator+(const Force &other) const {
            return {fx + other.fx, fy + other.fy};
        }

        double operator*(const Force &other) const {
            return fx * other.fx + fy * other.fy;
        }

        Force operator*(double scalar) const {
            return {fx * scalar, fy * scalar};
        }


    };
}