#include <iostream>
// #include "mewall.hpp"
// #include "virtual.hpp"
// #include "shell.hpp"
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

#include "Config.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

#define HELP_PAGE \
	"not have help page"
	// "Usage:\n" \
	// "> ./nan <path/to/file>\n" \
	// "Flags:\n" \
	// "-h, --help\t\tShow this help page\n" 

int main(int argc, char** argv) {
		// nanler::Lexer::TestLexer();
	// using namespace Virtual::Shell;
	// mew::args __args(argc, argv);
	// __args.normalize();
	// // __args.print();

	// if (
	// 	__args.has("-h")      ||
	// 	__args.has("--help")
	// ) {
	// 	printf(HELP_PAGE); exit(0);
	// }

	// if (__args.has("--test") || __args.) {
	// 	return 0;
	// }



	return 0;
}