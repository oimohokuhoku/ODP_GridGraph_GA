add_executable(groupTest test.cpp)
target_include_directories(groupTest PRIVATE "../../include")
target_link_libraries(groupTest PRIVATE odpGridGraphGAs)

add_test(NAME GroupTest COMMAND groupTest)