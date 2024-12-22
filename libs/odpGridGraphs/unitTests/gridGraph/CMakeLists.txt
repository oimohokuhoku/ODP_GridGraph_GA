set(testExeName gridGraphTest)
set(testName GridGraphTest)

add_executable(${testExeName} test.cpp)
target_link_libraries(${testExeName} PRIVATE odpGridGraphs)

add_test(
    NAME ${testName}
    COMMAND ${testExeName}
)
set_tests_properties(${testName}
    PROPERTIES
    LABELS GridGraphTests
)