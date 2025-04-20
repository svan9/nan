cmake_minimum_required(VERSION 3.16)
project(nanvma LANGUAGES CXX)
set(PROJECT_VERSION 1A00F)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-fconcepts)
add_compile_options(-fpermissive)

aux_source_directory("./" SOURCE)
add_executable(${PROJECT_NAME} ${SOURCE})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/include")
set_target_properties(${PROJECT_NAME} PROPERTIES COMMON_LANGUAGE_RUNTIME "" VS_INTERFACE_NATVIS_FILE  "${CMAKE_BINARY_DIR}/mewlib/mew.natvis")

find_package(OpenMP)
# if(OpenMP_CXX_FOUND AND RELEASE)
  target_link_libraries(${PROJECT_NAME} PUBLIC ZLIB::ZLIB OpenMP::OpenMP_CXX -static-libgcc -static-libstdc++ -O3 -static -pthread)
# endif()


if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  target_compile_definitions(${PROJECT_NAME} PUBLIC "LINUX_OS")
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  target_compile_definitions(${PROJECT_NAME} PUBLIC "MACOS_OS")
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  target_compile_definitions(${PROJECT_NAME} PUBLIC "WINDOWS_OS")


endif()

install(TARGETS ${PROJECT_NAME})