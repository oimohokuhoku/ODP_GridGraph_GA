cmake_minimum_required(VERSION 3.14)
set(PROJECT_VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB srcFiles "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(commonLibraries STATIC ${srcFiles})
target_include_directories(commonLibraries PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
