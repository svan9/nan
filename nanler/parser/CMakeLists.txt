cmake_minimum_required(VERSION 3.16)
set(PROJECT_NAME "nanler-parser")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-fconcepts)
add_compile_options(-fpermissive)

include_directories("../")

add_library(${PROJECT_NAME} STATIC 
"./array_in_round.cpp"
"./assign.cpp"
"./bin_wutil.cpp"
"./block.cpp"
"./expression.cpp"
"./extra.cpp"
"./flag.cpp"
"./function_call.cpp"
"./function.cpp"
"./if_else_final.cpp"
"./incapsulate.cpp"
"./iternal_name.cpp"
"./line.cpp"
"./name.cpp"
"./namespace_expand.cpp"
"./namespace_narrow.cpp"
"./namespace.cpp"
"./operator.cpp"
"./return.cpp"
"./structure.cpp"
"./template.cpp"
"./trait.cpp"
"./type.cpp"
"./typedef.cpp")

target_include_directories(${PROJECT_NAME} 
	PUBLIC "${CMAKE_SOURCE_DIR}/include"
	PUBLIC "${CMAKE_SOURCE_DIR}/nanler/"
	
	)