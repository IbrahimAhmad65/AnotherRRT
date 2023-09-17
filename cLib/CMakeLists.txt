cmake_minimum_required(VERSION 3.24)
project(cLib)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

FetchContent_Declare(
        wpilib
        GIT_REPOSITORY https://github.com/wpilibsuite/allwpilib
        GIT_TAG        main
)
FetchContent_GetProperties(wpilib)
if(NOT wpilib_POPULATED)
    FetchContent_Populate(wpilib)
    set(WITH_JAVA off)
    set(WITH_CSCORE off)
    set(WITH_WPIMATH on)
    set(WITH_WPILIB off)
    set(WITH_TESTS off)
    set(WITH_GUI off)
    set(WITH_SIMULATION_MODULES off)
    set(BUILD_SHARED_LIBS off)
    add_subdirectory(${wpilib_SOURCE_DIR} ${wpilib_BINARY_DIR})
endif()


add_executable(cLib main.cpp RRT/Node.h RRT/CubicHermite.h RRT/Tree.h RRT/RRTPointMassUtil.h Debug/Timer.h RRT/RRTPointMass.h RRT/RRTPointMassManager.h RRT/Djikstra/Graph.h RRT/Djikstra/GraphNode.h RRT/Djikstra/Djikstra.h RRT/RRTSwerveMode/dynamics_kinematics/SwerveDynamics.h RRT/RRTSwerveMode/structs/Hardware.h RRT/RRTSwerveMode/RRTSwerveMode.h RRT/RRTSwerveMode/structs/PhysicsStructs/PController.h RRT/RRTSwerveMode/SwerveRRTFuncs.h RRT/RRTSwerveMode/dynamics_kinematics/SwerveDriveKinematicsRRT.h RRT/RRTSwerveMode/structs/Config.h RRT/RRTSwerveMode/structs/PhysicsStructs/RandomForces.h RRT/RRTSwerveMode/structs/Operators.h RRT/RRTSwerveMode/structs/PhysicsStructs/Position.h RRT/RRTSwerveMode/structs/PhysicsStructs/ForceNTorque.h RRT/RRTSwerveMode/structs/dynamics_structs/ModulePosition.h RRT/RRTSwerveMode/structs/PhysicsStructs/Force.h RRT/RRTSwerveMode/structs/PhysicsStructs/Velocity.h RRT/RRTSwerveMode/structs/dynamics_structs/SwerveState.h RRT/RRTSwerveMode/structs/PhysicsStructs/Pose.h RRT/RRTSwerveMode/structs/rrt_structs/Node.h)
target_compile_options(cLib PRIVATE -Wdeprecated-declarations)
target_link_libraries(cLib PUBLIC wpimath)
#target_link_libraries(cLib PUBLIC ntcore)
target_compile_options(cLib PRIVATE -march=native)

#target_compile_options(cLib PRIVATE -fsanitize=address)
#target_link_options(cLib PRIVATE -fsanitize=address)