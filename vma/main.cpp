#include <iostream>
#include "mewall.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "virtual.hpp"
#include "nan.hpp"
#define HELP_PAGE \
	"Usage:\n" \
	"> ./nanvm <path/to/file>\n" \
	"Flags:\n" \
	"-h, --help\t\tShow this help page\n" 

int main(int argc, char** argv) {
	mew::args __args(argc, argv);
	__args.normalize();

	if (
		!__args.has_needs(1)   ||
		__args.has("-h")      ||
		__args.has("--help")
	) {
		printf(HELP_PAGE); exit(0);
	}
	
  // const char* path = "E:/so2u/GITHUB/cuba/nan/build/bin/asm.nsm";
  // const char* out = "./nan-temp.nb";
  // Virtual::Asm::compileFile(path, out);
	using namespace Virtual::Asm;
	
  const char* path = __args.getNextPath();
  const char* out = ValueOrDefault(__args.getOneStartsWith("-o"), "./nan-temp.nb");
  CompileOutFlags cof = compileFile(path, out);
	bool can_run = __args.has("-r");
	if (can_run && cof == CompileOutFlags::Warn) {
		printf("Message: Cannot auto run with warns");
		return 0;
	}
	if (can_run && cof == CompileOutFlags::Error) {
		printf("Message: Cannot auto run with errors");
		return 0;
	}
	if (can_run && cof == CompileOutFlags::Clear) {
		return Virtual::Execute(out);
	}

  return 0;
}