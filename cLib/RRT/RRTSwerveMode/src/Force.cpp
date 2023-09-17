// Created by ibrahim on 9/17/23.
//
#include "Force.h"

namespace swerve{

Force Force::operator+(const Force &other) const {
    return {fx + other.fx, fy + other.fy};
}

double Force::operator*(const Force &other) const {
    return fx * other.fx + fy * other.fy;
}

Force Force::operator*(double scalar) const {
    return {fx * scalar, fy * scalar};
}

}
