set(GTEST_ROOT "../googletest")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(my_code_test my_code_test.cpp ../src/my_code.cpp)

target_link_libraries(my_code_test ${GTEST_LIBRARIES} pthread)

add_test(NAME MyCodeTest COMMAND my_code_test)
