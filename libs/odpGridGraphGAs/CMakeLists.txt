
set(LibName odpGridGraphGAs)

file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(${LibName} STATIC ${SRC_FILES})
target_link_libraries(${LibName} PUBLIC odpGridGraphs)
target_include_directories(${LibName} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_subdirectory(unitTest)