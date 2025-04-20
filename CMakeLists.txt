cmake_minimum_required(VERSION 3.16)

set(RELEASE 0)
add_compile_definitions("DEBUG=$<CONFIG:Debug>")

# set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall -O3")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")

include_directories("${CMAKE_SOURCE_DIR}/mewlib")
configure_file("${CMAKE_SOURCE_DIR}/mewlib/mew.natvis" "${CMAKE_BINARY_DIR}/mew.natvis" COPYONLY)

add_subdirectory(zlib)
# add_subdirectory(libzip)
add_subdirectory(nanshell)
add_subdirectory(vm)
add_subdirectory(vma)
add_subdirectory(vm-test)
add_subdirectory(opt-test)
add_subdirectory(opt-m)

add_custom_target(copy_bin ALL
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_BINARY_DIR}/bin ${CMAKE_BINARY_DIR}/../build-win
	COMMENT "Copying bin folder to build-win"
)

# add_custom_target(copy_zlib ALL
# 	COMMAND ${CMAKE_COMMAND} -E copy
# 	${CMAKE_BINARY_DIR}/zlib/libz.dll ${CMAKE_BINARY_DIR}/bin
# 	COMMENT "Copying bin folder to build-win"
# )

# add_custom_target(copy_zlibd ALL
# 	COMMAND ${CMAKE_COMMAND} -E copy
# 	${CMAKE_BINARY_DIR}/zlib/libzd.dll ${CMAKE_BINARY_DIR}/bin
# 	COMMENT "Copying bin folder to build-win"
# )

