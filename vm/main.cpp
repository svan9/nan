#include <iostream>
#include "mewall.h"
#include "virtual.hpp"
#if defined(_WIN32)

#include <windows.h>
#include <libloaderapi.h>

#endif

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

#define HELP_PAGE \
	"Usage:\n" \
	"> ./nanvm <path/to/file>\n" \
	"Flags:\n" \
	"-h, --help\t\tShow this help page\n" 

int main(int argc, char** argv) {
	mew::args __args(argc, argv);
	__args.normalize();
	// __args.print();

	if (
		!__args.has_needs(1)   ||
		__args.has("-h")      ||
		__args.has("--help")
	) {
		printf(HELP_PAGE); exit(0);
	}

	// auto libs = __args.getStartsWith("-L");
	// mew::stack<mew::_dll_hinstance, 8U> hdlls;
	// for (int i = 0; i < libs.size(); i++) {
	// 	hdlls.push(mew::LoadDll(libs.at(i)));
	// }
	
	const char* path = __args.getNextPath();//;
	Virtual::VirtualMachine vm;
	Virtual::Code* code = Virtual::Code_LoadFromFile(path);
	// vm.hdlls = hdlls;
	int exit_code = Virtual::Execute(vm, *code);

#ifdef _WIN32
	HWND consoleWnd = GetConsoleWindow();
	DWORD dwProcessId;
	GetWindowThreadProcessId(consoleWnd, &dwProcessId);
	if (GetCurrentProcessId()==dwProcessId) {
		printf("\n");
		system("pause");
	}	
#endif
	return exit_code;
}