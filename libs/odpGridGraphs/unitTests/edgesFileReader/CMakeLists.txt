set(testExeName edgesFileReaderTest)
set(testName EdgesFileReaderTest)

add_executable(${testExeName} test.cpp)
target_link_libraries(${testExeName} PRIVATE odpGridGraphs)

add_custom_command(
    TARGET ${testExeName} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/test.edges
            $<TARGET_FILE_DIR:${testExeName}>
)

add_test(
    NAME ${testName}
    COMMAND ${testExeName}
)
set_tests_properties(${testName}
    PROPERTIES
    LABELS GridGraphTests
)