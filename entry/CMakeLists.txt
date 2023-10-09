set(SOURCES
    entry.cpp
)

set(EXEC_NAME
  vm
)

add_executable(${EXEC_NAME} ${SOURCES})

add_custom_target(run_${EXEC_NAME}
    COMMENT Running ${EXEC_NAME}
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXEC_NAME}
)