cmake_minimum_required(VERSION 3.10)
project(DynoraEngine C)

# ==== Padrão C ====
set(CMAKE_C_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ==== Paths ====
#set(DYNORA_ENGINE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
#set(DYNORA_ENGINE_SRC_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/src)
#set(DYNORA_ENGINE_INCLUDE_INTERNAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(DYNORA_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

set(DYNORA_ENGINE_DIR ${DYNORA_ROOT}/engine)
set(DYNORA_BACKENDS_DIR ${DYNORA_ROOT}/engine/logger/backends)
set(DYNORA_INCLUDE_DIR ${DYNORA_ROOT}/include)

# ==== Sources ====
# Core systems
set(DYNORA_ENGINE_SOURCES
    ${DYNORA_ENGINE_DIR}/logger/logger.c
)

# Backends
set(DYNORA_BACKEND_SOURCES
    ${DYNORA_BACKENDS_DIR}/logger_console.c
)

# ==== Library ====
add_library(DynoraEngine STATIC
    ${DYNORA_ENGINE_SOURCES}
    ${DYNORA_BACKEND_SOURCES}
)

# ==== Includes ====
target_include_directories(DynoraEngine
    PUBLIC
        ${DYNORA_INCLUDE_DIR}
    PRIVATE
        ${DYNORA_ENGINE_DIR}
        ${DYNORA_BACKENDS_DIR}
)

# ==== Examples ====
option(BUILD_EXAMPLES "Build examples" ON)

if(BUILD_EXAMPLES)
    add_executable(dynora_example examples/hello_logger.c)
    target_link_libraries(dynora_example PRIVATE DynoraEngine)
endif()
