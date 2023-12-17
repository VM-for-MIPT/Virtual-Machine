enable_testing()

set(SOURCES
    interpreter_tests.cpp
)

add_executable(interpreter_tests ${SOURCES})
target_link_libraries(interpreter_tests runtime GTest::gtest_main)
target_include_directories(interpreter_tests PUBLIC
                          ${PROJECT_SOURCE_DIR}/runtime/includes
                          ${PROJECT_SOURCE_DIR}/configs
                          ${PROJECT_BINARY_DIR}/gen
                          ${PROJECT_SOURCE_DIR}/${PROJECT_THIRD_PARTY}/googletest)
target_compile_options(interpreter_tests PUBLIC -fsanitize=address -g)
set_target_properties(interpreter_tests PROPERTIES LINK_FLAGS "-fsanitize=address")

add_custom_target(
    interpreter_gtests
    COMMENT "Running interpreter tests"
    COMMAND ./interpreter_tests
)
add_dependencies(interpreter_gtests interpreter_tests)