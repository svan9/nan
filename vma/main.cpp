#include <iostream>
#include "mewlib.h"
#include "config.h"
#include "virtual.hpp"

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
    char* arg = *(begin++);
    // printf("\n{[%s][%s]}", exec_name, arg);
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
};

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
  }
  const char* path = real_args[0];
  // if (MEW_FIND_MASK(cflags, (uint)CompilerFlags_Compile)) {
  // }
  const char* temp_path = "./temp.nb";
  Virtual::Compile(path, temp_path);

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