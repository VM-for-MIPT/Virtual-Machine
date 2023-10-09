set(SOURCES
    decoder.cpp
    interpreter.cpp
)

add_library(runtime STATIC ${SOURCES})
target_include_directories(runtime PUBLIC
                           ${PROJECT_SOURCE_DIR}/runtime/includes
                           ${PROJECT_SOURCE_DIR}/configs)

add_subdirectory(tests)