set(libName odpGridGraphs)

file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(${libName} STATIC ${SRC_FILES})

target_include_directories(${libName} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_subdirectory(unitTests)