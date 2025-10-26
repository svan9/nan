#include "mewargs.hpp"
#include "ld.hpp"

#ifdef _WIN32

#include <windows.h>
#include <libloaderapi.h>

#endif

#define HELP_PAGE                                             \
	"Usage: nanld <output> <...sources>\n"                      \
	"Flags:\n"                                                  \
	"\t\t -nll <name> -- link nan dynamic library (OPTIONAL)\n" \
	"\t\t -pll <name> -- link dynamic `pipe` library (OPTIONAL)"

int main(int argc, char** argv) {
	mew::args __args(argc, argv);
	__args.normalize();
	
	if (
		!__args.has_needs(2) ||
		__args.has("-h") ||
		__args.has("--help")
	) {
		printf(HELP_PAGE); exit(0);
	}

	return 0;	
}