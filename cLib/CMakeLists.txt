cmake_minimum_required(VERSION 3.24)
project(cLib)

set(CMAKE_CXX_STANDARD 23)
add_executable(cLib main.cpp RRT/Node.h RRT/CubicHermite.h RRT/Tree.h RRT/RRTPointMassUtil.h Debug/Timer.h RRT/RRTPointMass.h RRT/RRTPointMassManager.h RRT/Djikstra/Graph.h RRT/Djikstra/GraphNode.h RRT/Djikstra/Djikstra.h)
target_compile_options(cLib PRIVATE -march=native)
#target_compile_options(cLib PRIVATE -fsanitize=address)
#target_link_options(cLib PRIVATE -fsanitize=address)