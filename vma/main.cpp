#include <iostream>
#include "mewall.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "virtual.hpp"
#include "asm.hpp"

#if defined(_WIN32)

#include <windows.h>
#include <libloaderapi.h>
#include "Wincon.h"

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

char** SkipToExec(int& argc, char** args) {
  const char* exec_name = executable_name(); 
  char** begin = args;
  char** end = args+(argc*sizeof(*args));
  while (begin != end) {
    argc--;
    char* arg = *(begin++);
    if (strcmp(arg, exec_name) == 0) {
      return begin;
    }
  }
  return nullptr;
}

#include <iostream>
using namespace std;
#if       _WIN32_WINNT < 0x0500
  #undef  _WIN32_WINNT
  #define _WIN32_WINNT   0x0500
#endif

#include "asm.hpp"

enum CompilerFlags_: uint {
  CompilerFlags_None    = 0, 
  CompilerFlags_Compile = 1 << 1, 
  CompilerFlags_Run     = 1 << 2, 
  CompilerFlags_Test    = 1 << 3, 
};

static const char* test_string = 
"loop:\n"
"push num 9\n"
"push mem 0\n"
"test mem num\n"
"push rmem 0\n"
"inc mem\n"
"jmp loop\n"
;

int main(int argc, char** argv) {
  if (argc < 2) {
    printf("Usage:\n");
    printf("> ./nanvma <path/to/file>");
    exit(1);
  }
  const char** real_args = (const char**)SkipToExec(argc, argv);
  uint cflags = 0;
  if (argc == 1) {
    cflags = CompilerFlags_Compile | CompilerFlags_Run;
  }
  for (int i = 0; i < argc; i++) {
    const char* str = real_args[i];
    if (memcmp(str, "-c", 2)) {
      cflags = MEW_ADD_MASK((uint)CompilerFlags_Compile, cflags);
    } 
    else if (memcmp(str, "-r", 2)) {
      cflags = MEW_ADD_MASK((uint)CompilerFlags_Run, cflags);
    }
    else if (memcmp(str, "-t", 2)) {
      cflags = MEW_ADD_MASK((uint)CompilerFlags_Test, cflags);
    }
  }
  const char* path = real_args[0];
  std::filesystem::path __path(path);
  if (!__path.is_absolute()) {
    __path = std::filesystem::absolute(__path.lexically_normal());
  }
  std::ifstream file(path, std::ios::in | std::ios::binary);
  MewAssert(file.is_open());
  file.seekg(std::ios::beg);
  file >> std::noskipws;
  size_t size = file.tellg();
  char buffer[size] = {0};
  file.read(buffer, size);
  file.close();
  Virtual::Code* code = Virtual::Asm::ProccessCode((const char*)buffer);
  if (MEW_FIND_MASK(cflags, (uint)CompilerFlags_Compile)) {
    char* saved;
    if (argc > 2) {
      saved = (char*)real_args[1];
    } else {
      saved = "./temp.nb";
    }
    Virtual::Code_SaveFromFile(*code, (const char*)saved);
  }
  if (MEW_FIND_MASK(cflags, (uint)CompilerFlags_Run)) {
    Virtual::Execute(*code);
  }
  // wait
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