#include <iostream>
#include "mewall.h"
#include "virtual.hpp"
#include "shell.hpp"
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
	"not have help page"
	// "Usage:\n" \
	// "> ./nan <path/to/file>\n" \
	// "Flags:\n" \
	// "-h, --help\t\tShow this help page\n" 

int main(int argc, char** argv) {
	using namespace Virtual::Shell;
	mew::args __args(argc, argv);
	__args.normalize();
	// __args.print();

	if (
		__args.has("-h")      ||
		__args.has("--help")
	) {
		printf(HELP_PAGE); exit(0);
	}
	
	Shell shell;
	while(shell.listen()) {}
	

	// char* path = __args.getNextPath();
	// auto outputs = mew::run_cmd_get_output(mew::string::Format("node E:/so2u/GITHUB/cuba/nan/nanasm/index.js %s"));
	// auto outputs2 = mew::run_cmd_get_output("E:/so2u/GITHUB/cuba/nan/build/bin/nanvm.exe E:/so2u/GITHUB/cuba/nan/nanasm/temp.nb");
	// std::cout << outputs << std::endl;
	// std::cout << outputs2 << std::endl;
	return 0;
}