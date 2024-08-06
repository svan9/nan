cmake_minimum_required(VERSION 3.16)
project(NAN LANGUAGES CXX)

set(PROJECT_NAME nan)
set(PROJECT_VERSION 1A00F)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-fconcepts)
add_compile_options(-fpermissive)

add_executable(${PROJECT_NAME} WIN32 src/main.cpp)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GTK_CFLAGS} -fconcepts -fpermissive -std=c++20")
# target_link_libraries(${PROJECT_NAME} PUBLIC sfml-graphics)
# target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_c++20)
target_include_directories(${PROJECT_NAME} PUBLIC "./include" PUBLIC "./glm")


install(TARGETS ${PROJECT_NAME} ARCHIVE DESTINATION)
set(CPACK_GENERATOR "ZIP")
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
set(CPACK_VERBATIM_VARIABLES YES)
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
# set(CPACK_PACKAGE_VENDOR "ft_so2u")

# if(INSTALL_RUNTIME_PREFIX STREQUAL ".")
#   set(install_prefix_for_set_property)
# else()
#   set(install_prefix_for_set_property ${INSTALL_RUNTIME_PREFIX}/)
# endif()


# set_property(
#   INSTALL 
#     "${install_prefix_for_set_property}$<TARGET_FILE_NAME:${PROJECT_NAME}>"
#   PROPERTY
#     CPACK_START_MENU_SHORTCUTS ${PROJECT_NAME}
# )

# set_property(
#   INSTALL 
#     "${install_prefix_for_set_property}$<TARGET_FILE_NAME:${PROJECT_NAME}>"
#   PROPERTY
#     CPACK_DESKTOP_SHORTCUTS ${PROJECT_NAME}
# )

include(CPack)

if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM)
endif()
