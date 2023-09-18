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
if (NOT wpilib_POPULATED)
    FetchContent_Populate(wpilib)
    set(WITH_JAVA OFF CACHE INTERNAL "With Java")
    set(WITH_CSCORE OFF CACHE INTERNAL "With CSCore")
    set(WITH_WPIMATH ON CACHE INTERNAL "With WPIMath")
    set(WITH_WPILIB OFF CACHE INTERNAL "With WPILib")
    set(WITH_TESTS OFF CACHE INTERNAL "With Tests")
    set(WITH_GUI OFF CACHE INTERNAL "With GUI")
    set(WITH_SIMULATION_MODULES OFF CACHE INTERNAL "With Simulation Modules")
    set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "Build Shared Libs")
    add_subdirectory(${wpilib_SOURCE_DIR} ${wpilib_BINARY_DIR})
endif()

file(GLOB_RECURSE cLib_src RRT/*.cpp)
add_executable(cLib main.cpp ${cLib_src})


target_include_directories(cLib PRIVATE RRT
                                        RRT/Dijkstra
                                        RRT/RRTSwerveMode/inc
                                        RRT/RRTSwerveMode/src)


target_compile_options(cLib PRIVATE -Wdeprecated-declarations)
target_link_libraries(cLib PUBLIC wpimath)
#target_link_libraries(cLib PUBLIC ntcore)
target_compile_options(cLib PRIVATE -march=native)
# Generate compile_commands.json by default
if (NOT CMAKE_EXPORT_COMPILE_COMMANDS)
    set(CMAKE_EXPORT_COMPILE_COMMANDS "YES" CACHE STRING "" FORCE)
endif()
#include "frc/kinematics/SwerveDriveKinematics.h"
#target_compile_options(cLib PRIVATE -fsanitize=address)
#target_link_options(cLib PRIVATE -fsanitize=address)
