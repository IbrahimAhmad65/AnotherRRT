cmake_minimum_required(VERSION 3.24)
project(cLib)

set(CMAKE_CXX_STANDARD 23)
add_executable(cLib main.cpp RRT/Node.h RRT/CubicHermite.h RRT/Tree.h RRT/RRTPointMassUtil.h Debug/Timer.h RRT/RRTPointMass.h RRT/RRTPointMassManager.h RRT/Djikstra/Graph.h RRT/Djikstra/GraphNode.h RRT/Djikstra/Djikstra.h RRT/RRTSwerveMode/SwerveDynamics.h RRT/RRTSwerveMode/Hardware.h RRT/RRTSwerveMode/RRTSwerveMode.h RRT/RRTSwerveMode/SwerveNode.h RRT/RRTSwerveMode/SwerveDynamicsStructs.h RRT/RRTSwerveMode/SwerveRRTFuncs.h)
target_compile_options(cLib PRIVATE -march=native)
#target_compile_options(cLib PRIVATE -fsanitize=address)
#target_link_options(cLib PRIVATE -fsanitize=address)