#include <iostream>
#include "mewall.h"
#include "virtual.hpp"
#if defined(_WIN32)

#include <windows.h>
#include <libloaderapi.h>

#endif

const char* executable_name() {
#if defined(PLATFORM_POSIX) || defined(__linux__) //check defines for your setup
	std::string sp;
	std::ifstream("/proc/self/comm") >> sp;
	return sp.c_str();

#elif defined(_WIN32)
	char* buf = new char[MAX_PATH];
	GetModuleFileNameA(NULL, buf, MAX_PATH);
	return buf;

#else
	MewUserAssert(false, "unrecognized platform");
#endif
}

char** SkipToExec(int argc, char** args) {
	const char* exec_name = executable_name(); 
	char** begin = args;
	char** end = args+(argc*sizeof(*args));
	while (begin != end) {
		char* arg = *(begin++);
		// printf("\n{[%s][%s]}", exec_name, arg);
		if (strcmp(arg, exec_name) == 0) {
			return begin;
		}
	}
	return nullptr;
}

// #include <stdafx.h>
#include <iostream>
using namespace std;
#if       _WIN32_WINNT < 0x0500
  #undef  _WIN32_WINNT
  #define _WIN32_WINNT   0x0500
#endif
#ifdef _WIN32
	#include <windows.h>
	#include "Wincon.h"
#endif

int main(int argc, char** argv) {
		if (argc < 2) {
		printf("Usage:\n");
		printf("> ./nanvm <path/to/file>");
		exit(1);
	}
	const char** real_args = (const char**)SkipToExec(argc, argv);
	const char* path = real_args[0];
	Virtual::Execute(path);

#ifdef _WIN32
	HWND consoleWnd = GetConsoleWindow();
	DWORD dwProcessId;
	GetWindowThreadProcessId(consoleWnd, &dwProcessId);
	if (GetCurrentProcessId()==dwProcessId) {
		printf("\n");
		system("pause");
	}	
#endif
	return 0;
}