set(TEST_EXE survivorSelects_rankingSelectTest)

add_executable(${TEST_EXE} test.cpp)
target_include_directories(${TEST_EXE} PRIVATE "../../../include")
target_link_libraries(${TEST_EXE} PRIVATE odpGridGraphGAs)

set(TEST_FILES
    h5w5d4r2_d4l226667.edges
    h5w5d4r2_d4l227333.edges
    h5w5d4r2_d4l227667.edges
    h5w5d4r2_d4l230333.edges
    h5w5d4r2_d4l231000.edges
)

foreach(FILE ${TEST_FILES})
    add_custom_command(
        TARGET ${TEST_EXE} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/${FILE}
                $<TARGET_FILE_DIR:${TEST_EXE}>
    )
endforeach()

add_test(NAME SurvivorSelects_rankingSelectTest COMMAND ${TEST_EXE})
