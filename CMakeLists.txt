cmake_minimum_required(VERSION 3.16)

set(RELEASE 0)
add_compile_definitions("DEBUG=$<CONFIG:Debug>")

# set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall -O3")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")

include_directories("${CMAKE_SOURCE_DIR}/mewlib")
configure_file("${CMAKE_SOURCE_DIR}/mewlib/mew.natvis" "${CMAKE_BINARY_DIR}/mew.natvis" COPYONLY)

add_subdirectory(nanshell)
add_subdirectory(vm)
add_subdirectory(vma)
add_subdirectory(vm-test)