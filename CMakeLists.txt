cmake_minimum_required(VERSION 3.14)

project(OdpGridGraphGAExperiment CXX)
set(MAIN_EXE_NAME grid)
set(PROJECT_VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)

#Debug Mode↓
#set(CMAKE_CXX_FLAGS "-std=c++17 -O0 -g -Wall -Wextra -Wshadow -Wfloat-equal")
 
#Release Mode↓
set(CMAKE_CXX_FLAGS "-std=c++17 -O3 -mtune=native -march=native") 

add_subdirectory(./libs/odpGridGraphGAs/)
add_subdirectory(./libs/commonLibraries/)

add_executable(${MAIN_EXE_NAME} main.cpp)
target_link_libraries(${MAIN_EXE_NAME} PRIVATE odpGridGraphGAs commonLibraries)
target_include_directories(${MAIN_EXE_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/libs/commonLibraries/include")
target_include_directories(${MAIN_EXE_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/libs/odpGridGraphGAs/include")

set_target_properties(${MAIN_EXE_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

enable_testing()