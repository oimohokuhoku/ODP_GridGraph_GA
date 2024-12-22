cmake_minimum_required(VERSION 3.14)

project(OdpGridGraphGAExperiment CXX)
set(PROJECT_VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g -Wall -Wextra -Wshadow -Wfloat-equal")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -mtune=native -march=native")

enable_testing()

add_subdirectory(./libs/odpGridGraphs/)
add_subdirectory(./libs/odpGridGraphGAs/)
add_subdirectory(./libs/commonLibraries/)

set(mainExeName grid)
add_executable(${mainExeName} main.cpp)
target_link_libraries(${mainExeName} PRIVATE odpGridGraphGAs commonLibraries)

set_target_properties(${mainExeName} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)