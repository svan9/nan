#ifndef DLL_LIB_SO2U
#define DLL_LIB_SO2U

#include "mewlib.h"
#ifdef _WIN32
  #include <windows.h>
#else
  #include <dlfcn.h>
#endif
#include <functional>

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

namespace internal {
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

class DLL {
public:
  const char* name;
  _dll_hinstance handle;
  _dll_farproc fproc;
  ////////////////////////////////////////////////////////////
  DLL(const char* dll_path) {
    LoadLib(dll_path);
  }

  ////////////////////////////////////////////////////////////
  DLL(const char* dll_path, const char* func_name) {
    LoadLib(dll_path);
    GetFunction(func_name);
  }

  ////////////////////////////////////////////////////////////
  void LoadLib(const char* dll_path) {
    name = dll_path;
    handle = internal::LoadDll(dll_path);
  }

  ////////////////////////////////////////////////////////////
  _dll_farproc GetFunction(const char* name) {
    fproc = internal::GetFunction(handle, name);
    return fproc;
  }

  ////////////////////////////////////////////////////////////
  template<typename T>
  T GetFunction(const char* name) {
    fproc = (T)internal::GetFunction(handle, name);
    return fproc;
  }

  ////////////////////////////////////////////////////////////
  _dll_farproc GetFunction() {
    return fproc;
  }

  ////////////////////////////////////////////////////////////
  template<typename T>
  T GetFunction() {
    return (T)fproc;
  }

  ////////////////////////////////////////////////////////////
  template<typename T>
  T Call(char* format, ...) {
    size_t size = strlen(format);
    va_list factor;
    va_start(factor, format);
    for(int i = 0; i < size; i++) {
      switch(format[i]) {
        case 'i':
          int n = va_arg(factor, int);
          asm ( "push %0" : : "r"(n) );
          break;
        case 'f': 
          float n = va_arg(factor, float);
          asm ( "push %0" : : "r"(n) );
          break;
        case 'd':
          double n = va_arg(factor, double);
          asm ( "push %0" : : "r"(n) );
          break;
        case 'c':
          char n = va_arg(factor, char);
          asm ( "push %0" : : "r"(n) );
          break;
        case 's':
          short n = va_arg(factor, short);
          asm ( "push %0" : : "r"(n) );
          break;
        default: MewUserAssert(false, "unknown type");
      }
    }
    T result = (T(*)(void))fproc();
    va_end(factor);
    return result;
  }
};

}

#endif