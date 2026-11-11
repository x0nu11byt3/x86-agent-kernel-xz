
cmake_minimum_required(VERSION 3.20)

project(
    x86-agent-kernel
    VERSION 0.1.0
    DESCRIPTION "A symbolic debugging agent for Linux x86-64"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(x86agent_core INTERFACE)

target_include_directories(
    x86agent_core
    INTERFACE
        ${PROJECT_SOURCE_DIR}/include
)

target_compile_features(
    x86agent_core
    INTERFACE
        cxx_std_20
)

add_executable(x86-agent src/main.cpp)

target_link_libraries(
    x86-agent
    PRIVATE
        x86agent_core
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(
        x86-agent
        PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Wconversion
            -Wshadow
    )
endif()

install(
    TARGETS x86-agent
    RUNTIME DESTINATION bin
)