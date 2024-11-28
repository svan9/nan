cmake_minimum_required(VERSION 3.16)

set(RELEASE 0)
add_compile_definitions("DEBUG=$<CONFIG:Debug>")

set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall -O3")

add_subdirectory(src)
add_subdirectory(vm)