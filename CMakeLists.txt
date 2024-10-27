cmake_minimum_required(VERSION 3.14)

project(OdpGridGraphGAExperiment CXX)
set(PROJECT_VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED True)
#set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./)

set(CMAKE_CXX_FLAGS "-std=c++17 -O0 -g -Wall -Wextra -Wshadow -Wfloat-equal") #Debug Mode
#set(CMAKE_CXX_FLAGS "-std=c++17 -O3 -mtune=native -march=native") #Release Mode

file(GLOB LIBRARY_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/libs/*")
file(GLOB INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/libs/*/include")

add_subdirectory(./libs/odpGridGraphGAs/)
add_subdirectory(./libs/commonLibraries/)

add_executable(grid main.cpp)
target_link_libraries(grid PRIVATE odpGridGraphGAs commonLibraries)
target_include_directories(grid PRIVATE ${INCLUDE_DIRS})

enable_testing()