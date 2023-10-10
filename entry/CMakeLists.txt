set(SOURCES
    entry.cpp
)

add_executable(vm ${SOURCES})

add_custom_target(run_vm
    COMMENT Running VM
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/vm
)