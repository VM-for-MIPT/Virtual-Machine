set(QUADR_SRC
    ./quadratic.cpp
)

set(QUADR_EXEC_NAME quadratic)

add_executable(${QUADR_EXEC_NAME} ${QUADR_SRC})
target_link_libraries(${QUADR_EXEC_NAME} runtime)

target_include_directories(${QUADR_EXEC_NAME} PUBLIC
                          ${PROJECT_SOURCE_DIR}/runtime/includes
                          ${PROJECT_SOURCE_DIR}/configs
                          ${PROJECT_BINARY_DIR}/gen)

add_custom_target(
    run_${QUADR_EXEC_NAME}
    COMMENT "Running quadratic equation, please enter your coeffs:"
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${QUADR_EXEC_NAME}
)

add_dependencies(run_${QUADR_EXEC_NAME} ${QUADR_EXEC_NAME})