set(TEST_EXE crossover_EmbeddMapTest)

add_executable(${TEST_EXE} test.cpp)
target_include_directories(${TEST_EXE} PRIVATE "../../../include")
target_link_libraries(${TEST_EXE} PRIVATE odpGridGraphGAs)

add_test(NAME Crossover_EmbeddMapTest COMMAND ${TEST_EXE})
