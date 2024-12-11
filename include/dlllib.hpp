#ifndef DLL_LIB_SO2U
#define DLL_LIB_SO2U

#include "mewall.h"
#ifdef _WIN32
  #include <windows.h>
#else
  #include <dlfcn.h>
#endif
namespace dll {

#ifdef _WIN32
typedef HANDLE    _dll_handle;
typedef HINSTANCE _dll_hinstance;
typedef FARPROC   _dll_farproc;
#else 
typedef void* _dll_handle;
typedef void* _dll_hinstance;
typedef int(*_dll_farproc)(void);
#endif
  _dll_hinstance LoadDll(const char* name) {
    #ifdef _WIN32
    return ::LoadLibraryA(name);
    #else
    return ::dlopen(name, RTLD_LAZY);
    #endif
  }

  _dll_farproc GetFunction(_dll_hinstance handle, const char* name) {
    # ifdef _WIN32
      return ::GetProcAddress(handle, name);
    #else
      return ::dlsym(handle, name);
    #endif
  }
}

#endif