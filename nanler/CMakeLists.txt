cmake_minimum_required(VERSION 3.16)
project(nanler LANGUAGES CXX)

set(PROJECT_VERSION 1A00F)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-fconcepts)
add_compile_options(-fpermissive)

add_subdirectory("./parser")
add_subdirectory("./compiler")
add_subdirectory("./asm")
include_directories("./" "./parser")

add_executable(${PROJECT_NAME} "./main.cpp")
target_include_directories(${PROJECT_NAME}
	PUBLIC "${CMAKE_SOURCE_DIR}/include"
	PUBLIC "${CMAKE_SOURCE_DIR}/nanler/"
)

target_link_libraries(${PROJECT_NAME} -static-libgcc -static-libstdc++ nanler-parser
	# nanler-compiler
	)