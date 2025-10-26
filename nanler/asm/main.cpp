#include "mewargs.hpp"
#include "asm.hpp"

#ifdef _WIN32

#include <windows.h>
#include <libloaderapi.h>

#endif

#define HELP_PAGE \
	"Usage: nanasm <input> -o <output>"

int main(int argc, char** argv) {
	mew::args __args(argc, argv);
	__args.normalize();
	
	if (
		!__args.has_needs(1) ||
		__args.has("-h") ||
		__args.has("--help")
	) {
		printf(HELP_PAGE); exit(0);
	}

	struct {
		debug: 1 = false,
	} flags;

	flags.debug = __args.has("-d") || __args.has("--debug");

	const char* output_name = __args.getNextOr("-o", "./temp.nb");
	const char* input_name  = __args.getNextPath();

	if (!input_name) {
		printf(HELP_PAGE); exit(1);
	}

	const char* content = mew::ReadFullFile(input_name);
	nanasm::Compiler comp;
	comp.compile(content);
	if (flags.debug) {
		comp.debugSave(output_name);
	} else {
		comp.save(output_name);
	}
	return 0;	
}