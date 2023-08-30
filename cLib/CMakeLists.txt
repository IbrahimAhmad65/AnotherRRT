cmake_minimum_required(VERSION 3.25)
project(cLib)

set(CMAKE_CXX_STANDARD 23)

add_executable(cLib main.cpp RRT/Node.cpp RRT/Tree.cpp RRT/RRTPointMass.cpp)
