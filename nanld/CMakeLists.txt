cmake_minimum_required(VERSION 3.16)
set(PROJECT_NAME "nanld")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-fconcepts)
add_compile_options(-fpermissive)

include_directories("./" "../include" "../nanvm" "../nanler/asm/")

add_executable("nanld" main.cpp)
# add_library(${PROJECT_NAME} STATIC
# 	"./compiler/compiler.hpp" 
# )

# target_include_directories(${PROJECT_NAME} 
# 	PUBLIC "${CMAKE_SOURCE_DIR}/include"
# 	PUBLIC "${CMAKE_SOURCE_DIR}/nanler/"
	
# 	)