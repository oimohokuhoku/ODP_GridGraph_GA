cmake_minimum_required(VERSION 3.14)
set(PROJECT_VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(libName odpGridGraphGAs)
file(GLOB_RECURSE srcFiles "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(${libName} STATIC ${srcFiles})
target_link_libraries(${libName} PUBLIC odpGridGraphs)
target_include_directories(${libName} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_subdirectory(unitTest)