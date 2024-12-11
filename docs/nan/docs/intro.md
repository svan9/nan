---
sidebar_position: 1
---

# Into
> `!!--WARNING--!!`
Now repository includes only ___Nan Virtual Machine___. In future should includes also ___Nan Language Compiler___ for ___Nan Virtual Machine___
> [See library native usage](#lib-usage)

![C++](https://img.shields.io/badge/cpp-blue?logo=cplusplus)
![CMake](https://img.shields.io/badge/cmake-blue?logo=cmake)
![TEST](https://img.shields.io/badge/✔_windows-47c119)
![TEST](https://img.shields.io/badge/✘_ubuntu-orange)
![GitHub last commit](https://img.shields.io/github/last-commit/svan9/nan)
![GitHub commit activity](https://img.shields.io/github/commit-activity/m/svan9/nan)
![GitHub License](https://img.shields.io/github/license/svan9/nan?color=47c119)
![GitHub User's stars](https://img.shields.io/github/stars/svan9)
![GitHub watchers](https://img.shields.io/github/watchers/svan9/nan)

___Nan Language___ compiler for ___Nan Virtual Machine___. Also includes own ___Nan Virtual Machine___. Uses _cmake_ for build. Binary ___nan___ ([./src](./src)) - test (in the future, a complete compiler for ___Nan Language___). Binary ___nanvm___ ([./vm](./vm)) - Nan Virtual Machine executable for `*.nb` file ak binary nvm files.

### Usage
```shell
./nan
```
```shell
./nanvm "path/to/file"
```

* Virtual Machine provides in [virtual.hpp](/include/virtual.hpp). 
* Virtual Machine Lib provides in [virtuallib.hpp](/include/virtuallib.hpp) 

> VM uses _virtual_ namespace. VM Lib uses _virtual::lib_ namespace

### code-docs
See [/nan](/nan) for in code documentation
* std::console - [/nan/write.nan](/nan/write.nan)
* std::allocator - [/nan/allocator.nan](/nan/allocator.nan)
* test std  - [/nan/test_std.nan](/nan/test_std.nan)
* test preprocessing  - [/nan/preprocess.nan](/nan/preprocess.nan)
* test pointers  - [/nan/pointers.nan](/nan/pointers.nan)

# References 
- [virtual.hpp](./docs/virtual.md)
- [mewlib.h](./docs/mewlib.md)

## Tests
- [x] windows - tested
- [ ] ubuntu - not full test (errored)

## lib-usage
### visual.hpp
print 'hellow word' to console
```cpp
#include "virtual.hpp"

int main() {
//! build simple code
  using namespace Virtual;
  CodeBuilder builder;
  // puts - print wchar_t string from data which ends with zero byte 
  builder << Instruction_PUTS;
  builder << 0U;
  // !important - exit of program, else can run data bytes
  // if used default vm flag HeapLockExecute should errored without 'EXIT'
  builder << Instruction_EXIT;
  // add data at offset +0
  builder += L"hellow word";
  // release code
  Code* code = *builder;
//! save & execute from saved file
  // save code to file
  Code_SaveFromFile(*code, "./hellow_word.nb");
  // execute from file
  Execute("./hellow_word.nb");
//! execute from runtime
  // execute from code
  Execute(*code);
//! manial execution 
  // execute with own vm
  VirtualMachine vm;
  // allocate memory needs for code
  Alloc(vm, *code);
  // load memory from code
  LoadMemory(vm, *code);
  // execute code
  Run(vm, *code);
}
```
> for the inserted code, it is best to use 'virtualdub.hpp'. Otherwise, you will have to count bytes for jumps. The 'CodeBuilder' from 'virtual' is used only by internal build tools

### virtuallib.hpp
print number from 1 to 10
```cpp
#include "virtuallib.hpp"

int main() {
  using namespace Virtual;
  using namespace Virtual::Lib;
  Builder b;
  b.BeginFunction("main");
  /* TEST 'for' */
  b.BeginFunction("l1");
  /* 'for (int i = 0; i < 10; i)' */
  b.BeginForI("i", 0, 10);
  /*{*/
  /* */ b.Puti();
  /*}*/
  b.EndForI("i");
  // save for read
  b.Save("./vlib-for-10.nb");
  // build & run code
  b.Run();
}
```
