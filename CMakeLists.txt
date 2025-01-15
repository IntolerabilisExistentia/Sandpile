cmake_minimum_required(VERSION 3.12)

project(
    labwork3
    VERSION 1.0
    DESCRIPTION "C++ Year 2023 labwork3"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(lib)
add_subdirectory(bin)