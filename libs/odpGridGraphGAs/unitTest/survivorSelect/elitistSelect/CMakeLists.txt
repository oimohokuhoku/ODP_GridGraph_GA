set(TEST_EXE survivorSelects_elitistSelectTest)

add_executable(${TEST_EXE} test.cpp)
target_include_directories(${TEST_EXE} PRIVATE "../../../include")
target_link_libraries(${TEST_EXE} PRIVATE odpGridGraphGAs)

add_test(NAME SurvivorSelects_ElitistSelectTest COMMAND ${TEST_EXE})
