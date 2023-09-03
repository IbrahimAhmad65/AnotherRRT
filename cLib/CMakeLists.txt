cmake_minimum_required(VERSION 3.24)
project(cLib)

set(CMAKE_CXX_STANDARD 23)

add_executable(cLib main.cpp RRT/Node.h RRT/CubicHermite.h RRT/Tree.h RRT/RRTPointMass.h Debug/Timer.h)
