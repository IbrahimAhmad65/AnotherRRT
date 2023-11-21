cmake_minimum_required(VERSION 3.25)
project(rrtDynamics)

set(CMAKE_CXX_STANDARD 23)


file(GLOB_RECURSE rrtDynamics_src src/*.cpp)
add_executable(rrtDynamics main.cpp ${rrtDynamics_src})


target_include_directories(rrtDynamics PRIVATE
        inc
        src)


target_compile_options(rrtDynamics PRIVATE -march=native)
# Generate compile_commands.json by default
if (NOT CMAKE_EXPORT_COMPILE_COMMANDS)
    set(CMAKE_EXPORT_COMPILE_COMMANDS "YES" CACHE STRING "" FORCE)
endif ()


