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

add_executable(cLib main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE RRT/RRTSwerveMode/inc)
target_include_directories(${PROJECT_NAME} PRIVATE RRT/RRTSwerveMode/src)
target_include_directories(${PROJECT_NAME} PRIVATE RRT/Djikstra)
target_include_directories(${PROJECT_NAME} PRIVATE RRT)


target_compile_options(cLib PRIVATE -Wdeprecated-declarations)
target_link_libraries(cLib PUBLIC wpimath)
#target_link_libraries(cLib PUBLIC ntcore)
target_compile_options(cLib PRIVATE -march=native)

#target_compile_options(cLib PRIVATE -fsanitize=address)
#target_link_options(cLib PRIVATE -fsanitize=address)