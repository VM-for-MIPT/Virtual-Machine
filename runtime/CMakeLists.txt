set(SOURCES
    decoder.cpp
    interpreter.cpp
    mem/frame.cpp
    coretypes/array.cpp
    coretypes/object_header.cpp
)

add_library(runtime STATIC ${SOURCES})
target_include_directories(runtime PUBLIC
                           ${PROJECT_SOURCE_DIR}/runtime/includes
                           ${PROJECT_SOURCE_DIR}/configs
                           ${PROJECT_SOURCE_DIR}/isa)

add_subdirectory(tests)
add_subdirectory(usability_check)
