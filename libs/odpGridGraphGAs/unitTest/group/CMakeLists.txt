set(TEST_EXE groupTest)

add_executable(${TEST_EXE} test.cpp)
target_include_directories(${TEST_EXE} PRIVATE "../../include")
target_link_libraries(${TEST_EXE} PRIVATE odpGridGraphGAs)

add_test(NAME GroupTest COMMAND ${TEST_EXE})