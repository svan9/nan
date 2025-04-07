project(opt_test)

add_executable(opt_test
	main.cpp
)

target_link_libraries(opt_test PUBLIC -static-libgcc -static-libstdc++ -O3 -static -pthread)