cmake_minimum_required(VERSION 3.16)
project(optm LANGUAGES CXX)
set(PROJECT_VERSION 1A00F)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-fconcepts)
add_compile_options(-fpermissive)
add_compile_options(-save-temps)

aux_source_directory("./" SOURCE)
add_executable(${PROJECT_NAME} ${SOURCE})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/include")
set_target_properties(${PROJECT_NAME} PROPERTIES COMMON_LANGUAGE_RUNTIME "")
find_package(OpenMP)

if(OpenMP_CXX_FOUND AND RELEASE)
  target_link_libraries(${PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX -static-libgcc -static-libstdc++ -O3 -static -pthread)
endif()
