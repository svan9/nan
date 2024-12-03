#ifndef _NAN_VIRTUAL_IMPL
#define _NAN_VIRTUAL_IMPL

#include "config.h"
#include "mewlib.h"
#include <stack>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <windows.h>
#include <fcntl.h>
#include <vector>

/*
Reference
  push <type:1b> <value:4b>
  pop -no args-
-- Math -- 
gets last elements from stack -> and push to top result
  add <type:1b> <type:1b>
  sub <type:1b> <type:1b>
  mul <type:1b> <type:1b>
  div <type:1b> <type:1b>
  xor <type:1b> <type:1b>
  or <type:1b> <type:1b>
  not <type:1b>
  and <type:1b> <type:1b>
  ls <type:1b> <type:1b>
  rs <type:1b> <type:1b>
<- todo float math 
  jmp <offset:4b>
  ret -no args-
  test -no args-
  j<if> <offset:4b>
  mov <type:1b> <address:4b>
 */

namespace Virtual {
  struct VirtualMachine;
  typedef void(*VM_Processor)(VirtualMachine&, byte*);

  enum Instruction: byte {
    Instruction_NONE = 0,
    Instruction_LDLL,
    Instruction_CALL,
    Instruction_PUSH,
    Instruction_POP,

    Instruction_ADD,
    Instruction_SUB,
    Instruction_MUL,
    Instruction_DIV,

    Instruction_INC,
    Instruction_DEC,

    Instruction_XOR,
    Instruction_OR,
    Instruction_NOT,
    Instruction_AND,
    Instruction_LS, // left shift
    Instruction_RS, // right shift

    Instruction_NUM,  // arg type | number
    Instruction_INT,  // arg type | int
    Instruction_FLT,  // arg type | float
    Instruction_DBL,  // arg type | double
    Instruction_UINT, // arg type | uint
    Instruction_BYTE, // arg type | char
    Instruction_MEM,  // arg type | memory
    Instruction_RMEM,  // arg type | memory
    /*depricated*/
    Instruction_HEAP, // arg type | heap begin
    Instruction_ST,   // arg type | stack top
    
    Instruction_JMP,
    Instruction_RET,
    Instruction_EXIT,
    Instruction_TEST,
    Instruction_JE,
    Instruction_JEL,
    Instruction_JEM,
    Instruction_JNE,
    Instruction_JL,
    Instruction_JM,
    Instruction_MOV,  // replace head data from stack to memory
    Instruction_MSET,
    
    Instruction_SWST,  // set used stream
    Instruction_WRITE, // write to used stream
    Instruction_READ,  // read used stream
    Instruction_OPEN,  // open file as destinator

    Instruction_PUTC,
    Instruction_PUTI,
    Instruction_PUTS,
  };

  #define VIRTUAL_VERSION (Instruction_PUTS*100)+44

  struct Code {
    size_t capacity;
    Instruction* playground;
    size_t data_size = 0;
    byte* data = nullptr;
  };

  struct CodeManifest {
    std::vector<VM_Processor> procs;
  };

  struct CodeExtended {
    CodeManifest* manifest;
    Code* code;
  };

#pragma region FILE
 
  void Code_SaveFromFileEx(const CodeExtended& code, const std::filesystem::path& path) {
    std::ofstream file(path, std::ios::out | std::ios::binary);
    MewAssert(file.is_open());
    file.seekp(std::ios::beg);
    /* version */
    uint vv = (uint)VIRTUAL_VERSION;
    file.write((const char*)(&vv), sizeof(uint));
    /* manifest */
    file << code.manifest->procs.size();
    for (auto proc: code.manifest->procs) {
      file << ((byte*)((uint)((void*)proc)));
    }
    /* code */
    file << code.code->capacity;
    for (int i = 0; i < code.code->capacity; i++) {
      file << ((byte*)code.code->playground)[i];
    }
    /* data */
    file << code.code->data_size;
    for (int i = 0; i < code.code->data_size; i++) {
      file << ((byte*)code.code->data)[i];
    }
    file.close();
  }

  void Code_SaveFromFile(const Code& code, const std::filesystem::path& path) {
    std::ofstream file(path, std::ios::out | std::ios::binary);
    MewAssert(file.is_open());
    file.seekp(std::ios::beg);
    uint vv = (uint)VIRTUAL_VERSION;
    file.write((const char*)(&vv), sizeof(uint));
    file << code.capacity;
    for (int i = 0; i < code.capacity; i++) {
      file << ((byte*)code.playground)[i];
    }
    file << code.data_size;
    for (int i = 0; i < code.data_size; i++) {
      file << ((byte*)code.data)[i];
    }
    file.close();
  }

  void Code_SaveFromFile(const Code& code, const char* path) {
    std::filesystem::path __path(path);
    if (!__path.is_absolute()) {
      __path = std::filesystem::absolute(__path.lexically_normal());
    }
    Code_SaveFromFile(code, __path);
  }

  void Code_SaveFromFileEx(const CodeExtended& code, const char* path) {
    std::filesystem::path __path(path);
    if (!__path.is_absolute()) {
      __path = std::filesystem::absolute(__path.lexically_normal());
    }
    Code_SaveFromFileEx(code, __path);
  }

  void Code_SaveFromFileEx(Code& code, const char* path) {
    CodeExtended ce;
    ce.code = &code;
    Code_SaveFromFileEx(ce, path);
  }

  CodeExtended* Code_LoadFromFileEx(const std::filesystem::path& path) {
    std::ifstream file(path, std::ios::in | std::ios::binary);
    MewAssert(file.is_open());
    file.seekg(std::ios::beg);
    file >> std::noskipws;
    uint file_version;
    char vv[sizeof(uint)];
    file.read(vv, sizeof(uint));
    memcpy(&file_version, vv, sizeof(uint));
    if (file_version != VIRTUAL_VERSION) {
      MewWarn("file version not support (%i != %i)", file_version, VIRTUAL_VERSION); 
      return nullptr;
    }
    CodeExtended* code = new CodeExtended();
    /* manifest */
    uint size;
    file >> size;
    for (int i = 0; i < size; i++) {
      uint raw_r;
      file >> raw_r;
      code->manifest->procs.push_back((VM_Processor)((void*)(raw_r)));
    }
    /* code */
    file >> code->code->capacity;
    code->code->playground = new Instruction[code->code->capacity];
    for (int i = 0; i < code->code->capacity; i++) {
      file >> ((byte*)code->code->playground)[i];
    }
    /* data */
    file >> code->code->data_size;
    code->code->data = new byte[code->code->data_size];
    for (int i = 0; i < code->code->data_size; i++) {
      file >> ((byte*)code->code->data)[i];
    }
    file.close();
    return code;
  }

  Code* Code_LoadFromFile(const std::filesystem::path& path) {
    std::ifstream file(path, std::ios::in | std::ios::binary);
    MewAssert(file.is_open());
    file.seekg(std::ios::beg);
    file >> std::noskipws;
    uint file_version;
    char vv[sizeof(uint)];
    file.read(vv, sizeof(uint));
    memcpy(&file_version, vv, sizeof(uint));
    if (file_version != VIRTUAL_VERSION) {
      MewWarn("file version not support (%i != %i)", file_version, VIRTUAL_VERSION); 
      return nullptr;
    }
    Code* code = new Code();
    file >> code->capacity;
    code->playground = new Instruction[code->capacity];
    for (int i = 0; i < code->capacity; i++) {
      file >> ((byte*)code->playground)[i];
    }
    file >> code->data_size;
    code->data = new byte[code->data_size];
    for (int i = 0; i < code->data_size; i++) {
      file >> ((byte*)code->data)[i];
    }

    file.close();
    return code;
  }

  Code* Code_LoadFromFile(const char* path) {
    std::filesystem::path __path(path);
    if (!__path.is_absolute()) {
      __path = std::filesystem::absolute(__path.lexically_normal());
    }
    return Code_LoadFromFile(__path);
  }
  
  CodeExtended* Code_LoadFromFileEx(const char* path) {
    std::filesystem::path __path(path);
    if (!__path.is_absolute()) {
      __path = std::filesystem::absolute(__path.lexically_normal());
    }
    return Code_LoadFromFileEx(__path);
  }

  Code* Code_LoadFromFileExR(const char* path) {
    std::filesystem::path __path(path);
    if (!__path.is_absolute()) {
      __path = std::filesystem::absolute(__path.lexically_normal());
    }
    CodeExtended* ce = Code_LoadFromFileEx(__path);
    return ce->code;
  }

  enum VM_Status: byte {
    VM_Status_Panding = 0,
    VM_Status_Execute = 1 << 1,
    VM_Status_Ret     = 1 << 2,
  };
  
  enum VM_TestStatus: byte {
    VM_TestStatus_Skip = 0,
    VM_TestStatus_Equal = 1 << 1,
    VM_TestStatus_Less  = 1 << 2,
    VM_TestStatus_More  = 1 << 3,
    VM_TestStatus_EqualMore  = VM_TestStatus_Equal | VM_TestStatus_More,
    VM_TestStatus_EqualLess  = VM_TestStatus_Equal | VM_TestStatus_Less,
  };

#pragma region VM


  struct VirtualMachine {
    size_t capacity;
    byte *memory, *heap, 
      *begin, *end;
    std::stack<uint> stack;
    // std::stack<byte> byte_stack;
    std::stack<byte*> begin_stack;
    std::vector<VM_Processor> procs;
    // std::vector<void*> libs_funcs;
    FILE* r_stream;
    byte test;
    byte status;
  };

  #ifndef VM_ALLOC_ALIGN
    #define VM_ALLOC_ALIGN 512
  #endif
  #ifndef VM_MINHEAP_ALIGN
    #define VM_MINHEAP_ALIGN 128
  #endif
  #ifndef VM_CODE_ALIGN
    #define VM_CODE_ALIGN 8
  #endif
  #define __VM_ALIGN(_val, _align) (((int)((_val) / (_align)) + 1) * (_align))

  void Alloc(VirtualMachine& vm) {
    if (vm.memory != nullptr) {
      free(vm.memory);
    }
    vm.memory = new byte[VM_ALLOC_ALIGN];
    memset(vm.memory, Instruction_NONE, VM_ALLOC_ALIGN);
    vm.capacity = VM_ALLOC_ALIGN;
  }

  void Alloc(VirtualMachine& vm, Code& code) {
    size_t size = __VM_ALIGN(code.capacity+code.data_size, VM_ALLOC_ALIGN);
    if ((size - code.capacity - code.data_size) <= 0) {
      size += VM_MINHEAP_ALIGN;
    }
    vm.memory = new byte[size];
    memset(vm.memory, Instruction_NONE, size);
    vm.capacity = size;
  }

  uint DeclareProccessor(VirtualMachine& vm, VM_Processor proc) {
    vm.procs.push_back(proc);
    return vm.procs.size()-1;
  }

  void LoadMemory(VirtualMachine& vm, Code& code) {
    vm.memory = (byte*)code.playground;
  }

  void VM_ManualPush(VirtualMachine& vm, uint x) {
    vm.stack.push(x);
  }

  void VM_Push(VirtualMachine& vm, byte* line) {
    byte head_byte = line[1];
    switch (head_byte) {
      case 0:
      case Instruction_FLT:
      case Instruction_NUM: {
        uint number = 0;
        memcpy(&number, line+2, sizeof(number));
        vm.stack.push(number);
      } break;
      case Instruction_MEM: {
        uint number = 0;
        memcpy(&number, line+2, sizeof(number));
        MewUserAssert(vm.heap+number < vm.end, "out of memory");
        byte* pointer = vm.heap+number;
        uint x; memcpy(&x, pointer, sizeof(x));
        vm.stack.push(x);
      } break;
      case Instruction_RMEM: {
        uint number = 0;
        memcpy(&number, line+2, sizeof(number));
        MewUserAssert(vm.heap+number < vm.end, "out of memory");
        // byte* pointer = vm.heap+number;
        // uint x; memcpy(&x, pointer, sizeof(x));
        vm.stack.push(number);
      } break;

      default: MewNot(); break;
    }
  }
  
  void VM_Pop(VirtualMachine& vm, byte* line) {
    MewAssert(!vm.stack.empty());
    vm.stack.pop();
  }
  
  void VM_StackTop(VirtualMachine& vm, byte type, uint* x, byte** mem = nullptr) {
    switch (type) {
      case 0:
      case Instruction_FLT:
      case Instruction_NUM: {
        MewUserAssert(!vm.stack.empty(), "stack is empty");
        uint _top = vm.stack.top();
        // *x = _top;
        memmove(x, &_top, sizeof(_top));
      } break;
      case Instruction_MEM: {
        MewUserAssert(!vm.stack.empty(), "stack is empty");
        uint _top = vm.stack.top();
        uint offset = _top;
        MewUserAssert(vm.heap+offset < vm.end, "out of memory");
        byte* pointer = vm.heap+offset;
        if (mem != nullptr) {
          *mem = pointer;
        }
        memmove(x, pointer, sizeof(*x));
      } break;

      default: MewNot(); break;
    }
    vm.stack.pop();
  }

  void VM_Call(VirtualMachine& vm, byte* line) {
    uint x; /* storage processors idx */
    memcpy(&x, line, sizeof(x));
    MewUserAssert(x < vm.procs.size(), "cannot find loaded proccessor by idx");
    auto proc = vm.procs.at(x);
    proc(vm, line);
  }

  void VM_MathBase(VirtualMachine& vm, byte* line, uint* x, uint* y, byte** mem = nullptr) {
    byte type_x = line[1];
    byte type_y = line[2];
    VM_StackTop(vm, type_x, x, mem);
    VM_StackTop(vm, type_y, y);
  }
  void VM_Add(VirtualMachine& vm, byte* line) {
    int x, y;
    byte* mem;
    VM_MathBase(vm, line, (uint*)&x, (uint*)&y, &mem);
    x += y;
    VM_ManualPush(vm, x);
    if (line[1] == Instruction_MEM) {
      memcpy(mem, &x, sizeof(x));
    }
  }
  void VM_Sub(VirtualMachine& vm, byte* line) {
    int x, y;
    byte* mem;
    VM_MathBase(vm, line, (uint*)&x, (uint*)&y, &mem);
    x -= y;
    VM_ManualPush(vm, x);
    if (line[1] == Instruction_MEM) {
      memcpy(mem, &x, sizeof(x));
    }
  }
  void VM_Mul(VirtualMachine& vm, byte* line) {
    int x, y;
    byte* mem;
    VM_MathBase(vm, line, (uint*)&x, (uint*)&y, &mem);
    x *= y;
    VM_ManualPush(vm, x);
    if (line[1] == Instruction_MEM) {
      memcpy(mem, &x, sizeof(x));
    }
  }
  void VM_Div(VirtualMachine& vm, byte* line) {
    int x, y;
    byte* mem;
    VM_MathBase(vm, line, (uint*)&x, (uint*)&y, &mem);
    x /= y;
    VM_ManualPush(vm, x);
    if (line[1] == Instruction_MEM) {
      memcpy(mem, &x, sizeof(x));
    }
  }
  void VM_Inc(VirtualMachine& vm, byte* line) {
    uint x;
    byte* mem;
    VM_StackTop(vm, line[1], &x, &mem);
    x++;
    VM_ManualPush(vm, x);
    if (line[1] == Instruction_MEM) {
      memcpy(mem, &x, sizeof(x));
    }
  }
  void VM_Dec(VirtualMachine& vm, byte* line) {
    uint x;
    byte* mem;
    VM_StackTop(vm, line[1], &x, &mem);
    x--;
    VM_ManualPush(vm, x);
    if (line[1] == Instruction_MEM) {
      memcpy(mem, &x, sizeof(x));
    }
  }
  void VM_Xor(VirtualMachine& vm, byte* line) {
    uint x, y;
    byte* mem;
    VM_MathBase(vm, line, (uint*)&x, (uint*)&y, &mem);
    x ^= y;
    VM_ManualPush(vm, x);
    if (line[1] == Instruction_MEM) {
      memcpy(mem, &x, sizeof(x));
    }
  }
  void VM_Or(VirtualMachine& vm, byte* line) {
    uint x, y;
    byte* mem;
    VM_MathBase(vm, line, (uint*)&x, (uint*)&y, &mem);
    x |= y;
    VM_ManualPush(vm, x);
    if (line[1] == Instruction_MEM) {
      memcpy(mem, &x, sizeof(x));
    }
  }
  void VM_Not(VirtualMachine& vm, byte* line) {
    uint x;
    byte* mem;
    VM_StackTop(vm, line[1], &x, &mem);
    x = ~x;
    VM_ManualPush(vm, x);
    if (line[1] == Instruction_MEM) {
      memcpy(mem, &x, sizeof(x));
    }
  }
  void VM_And(VirtualMachine& vm, byte* line) {
    uint x, y;
    byte* mem;
    VM_MathBase(vm, line, (uint*)&x, (uint*)&y, &mem);
    x &= y;
    VM_ManualPush(vm, x);
    if (line[1] == Instruction_MEM) {
      memcpy(mem, &x, sizeof(x));
    }
  }
  void VM_LS(VirtualMachine& vm, byte* line) {
    uint x, y;
    byte* mem;
    VM_MathBase(vm, line, (uint*)&x, (uint*)&y, &mem);
    x <<= y;
    VM_ManualPush(vm, x);
    if (line[1] == Instruction_MEM) {
      memcpy(mem, &x, sizeof(x));
    }
  }
  void VM_RS(VirtualMachine& vm, byte* line) {
    uint x, y;
    byte* mem;
    VM_MathBase(vm, line, (uint*)&x, (uint*)&y, &mem);
    x >>= y;
    VM_ManualPush(vm, x);
    if (line[1] == Instruction_MEM) {
      memcpy(mem, &x, sizeof(x));
    }
  }
  
  void VM_ManualJmp(VirtualMachine& vm, int offset) {
    MewUserAssert(MEW_IN_RANGE(vm.memory, vm.end, vm.begin+offset), 
      "out of memory");
    vm.begin_stack.push(vm.begin+VM_CODE_ALIGN);
    vm.begin += offset;
  }
  
  void VM_Jmp(VirtualMachine& vm, byte* line) {
    int offset;
    memcpy(&offset, line+1, sizeof(int));
    MewUserAssert(MEW_IN_RANGE(vm.memory, vm.end, vm.begin+offset), 
      "out of memory");
    vm.begin_stack.push(vm.begin);
    vm.begin += offset;
  }


  void VM_Ret(VirtualMachine& vm, byte* line) {
    if (vm.begin_stack.empty()) {
      vm.status = VM_Status_Ret; return;
    }
    byte* begin = vm.begin_stack.top();
    vm.begin = begin;
    vm.begin_stack.pop();
  }

  void VM_Test(VirtualMachine& vm, byte* line) {
    int x, y;
    VM_MathBase(vm, line, (uint*)&x, (uint*)&y);
    int result = memcmp(&x, &y, sizeof(x));
    if (result > 0) {
      vm.test = VM_TestStatus_More;
    } else if (result < 0) {
      vm.test = VM_TestStatus_Less;
    } else {
      vm.test = VM_TestStatus_Equal;
    }
  }

  void VM_JE(VirtualMachine& vm, byte* line) {
    int offset; 
    memcpy(&offset, line+1, sizeof(int));
    if (vm.test == VM_TestStatus_Equal) {
      VM_ManualJmp(vm, offset);
    }
  }
  void VM_JEL(VirtualMachine& vm, byte* line) {
    int offset; 
    memcpy(&offset, line+1, sizeof(int));
    if (MEW_FIND_MASK(VM_TestStatus_EqualLess, vm.test)) {
      VM_ManualJmp(vm, offset);
    }
  }
  void VM_JEM(VirtualMachine& vm, byte* line) {
    int offset; 
    memcpy(&offset, line+1, sizeof(int));
    if (MEW_FIND_MASK(VM_TestStatus_EqualMore, vm.test)) {
      VM_ManualJmp(vm, offset);
    }
  }
  void VM_JL(VirtualMachine& vm, byte* line) {
    int offset; 
    memcpy(&offset, line+1, sizeof(int));
    if (vm.test == VM_TestStatus_Less) {
      VM_ManualJmp(vm, offset);
    }
  }
  void VM_JM(VirtualMachine& vm, byte* line) {
    int offset; 
    memcpy(&offset, line+1, sizeof(int));
    if (vm.test == VM_TestStatus_More) {
      VM_ManualJmp(vm, offset);
    }
  }
  void VM_JNE(VirtualMachine& vm, byte* line) {
    int offset; 
    memcpy(&offset, line+1, sizeof(int));
    if (vm.test != VM_TestStatus_Equal) {
      VM_ManualJmp(vm, offset);
    }
  }

  void VM_Mov(VirtualMachine& vm, byte* line) {
    uint x; 
    VM_StackTop(vm, line[1], &x);
    uint offset;
    memcpy(&offset, line+2, sizeof(uint));
    MewUserAssert(vm.heap+offset < vm.end, "out of memory");
    byte* pointer = vm.heap+offset;
    memcpy(pointer, &x, sizeof(x));
  }
  
  void VM_MSet(VirtualMachine& vm, byte* line) {
    uint x; /* start */
    uint y; /* size  */
    uint z; /* value */
    VM_StackTop(vm, Instruction_NUM, &x);
    VM_StackTop(vm, Instruction_NUM, &y);
    VM_StackTop(vm, Instruction_NUM, &z);
    MewUserAssert(vm.heap+x < vm.end, "out of memory");
    MewUserAssert(vm.heap+x+y < vm.end, "out of memory");
    memset(vm.heap+x, z, y);
  }

  void VM_Putc(VirtualMachine& vm, byte* line) {
    wchar_t long_char;
    memcpy(&long_char, line+1, sizeof(wchar_t));
    putwchar(long_char);
  }
  
  void VM_Puti(VirtualMachine& vm, byte* line) {
    int x;
    VM_StackTop(vm, line[1], (uint*)&x);
    char str[12] = {0};
    itoa(x, str, 10);
    fputs(str, stdout);
  }

  void VM_Puts(VirtualMachine& vm, byte* line) {
    uint offset;
    memcpy(&offset, line+1, sizeof(uint));
    MewUserAssert(vm.heap+offset < vm.end, "out of memory");
    byte* pointer = vm.heap+offset;
    wchar_t* begin = (wchar_t*)pointer;
    while (*(begin) != 0) {
      putwchar(*(begin++));
    }
  }

  void VM_Open(VirtualMachine& vm, byte* line) {
    uint offset;
    memcpy(&offset, line+1, sizeof(uint));
    MewUserAssert(vm.heap+offset < vm.end, "out of memory");
    byte* pointer = vm.heap+offset;
    char* begin = (char*)pointer;
    int flags;
    VM_StackTop(vm, line[4], (uint*)&flags);
    int dest = open(begin, flags);
    VM_ManualPush(vm, dest);
  }

  void VM_Swst(VirtualMachine& vm, byte* line) {
    int idx;
    bool use_stack;
    memcpy(&use_stack, line+1, sizeof(use_stack));
    if (use_stack) {
      VM_StackTop(vm, line[2], (uint*)&idx);
    } else {
      memcpy(&idx, line+2, sizeof(idx));
    }
    vm.r_stream = fdopen(idx, "r+");
  }
  
  void VM_Write(VirtualMachine& vm, byte* line) {
    uint offset;
    memcpy(&offset, line+1, sizeof(uint));
    MewUserAssert(vm.heap+offset < vm.end, "out of memory");
    byte* pointer = vm.heap+offset;
    fputws((wchar_t*)pointer, vm.r_stream);
  }
  
  void VM_Read(VirtualMachine& vm, byte* line) {
    uint offset;
    memcpy(&offset, line+1, sizeof(uint));
    MewUserAssert(vm.heap+offset < vm.end, "out of memory");
    byte* pointer = vm.heap+offset;
    short int chunk_size;
    memcpy(&chunk_size, line+1+sizeof(uint), sizeof(chunk_size));
    MewUserAssert(vm.heap+offset+(chunk_size*2) < vm.end, "out of memory (chunk too big)");
    fgetws((wchar_t*)pointer, chunk_size, vm.r_stream);
  }

  void RunLine(VirtualMachine& vm, byte* line) {
    byte head_byte = line[0];
    switch (head_byte) {
      case Instruction_NONE: break;
      case Instruction_PUSH: {
        VM_Push(vm, line);
      } break;
      case Instruction_POP: {
        VM_Pop(vm, line);
      } break;
      case Instruction_ADD: {
        VM_Add(vm, line);
      } break;
      case Instruction_SUB: {
        VM_Sub(vm, line);
      } break;
      case Instruction_MUL: {
        VM_Mul(vm, line);
      } break;
      case Instruction_DIV: {
        VM_Div(vm, line);
      } break;
      case Instruction_INC: {
        VM_Inc(vm, line);
      } break;
      case Instruction_DEC: {
        VM_Dec(vm, line);
      } break;
      case Instruction_XOR: {
        VM_Xor(vm, line);
      } break;
      case Instruction_OR: {
        VM_Or(vm, line);
      } break;
      case Instruction_NOT: {
        VM_Not(vm, line);
      } break;
      case Instruction_LS: {
        VM_LS(vm, line);
      } break;
      case Instruction_RS: {
        VM_RS(vm, line);
      } break;
      case Instruction_JMP: {
        VM_Jmp(vm, line);
      } break;
      case Instruction_RET: {
        VM_Ret(vm, line);
      } break;
      case Instruction_TEST: {
        VM_Test(vm, line);
      } break;
      case Instruction_JE: {
        VM_JE(vm, line);
      } break;
      case Instruction_JEL: {
        VM_JEL(vm, line);
      } break;
      case Instruction_JEM: {
        VM_JEM(vm, line);
      } break;
      case Instruction_JL: {
        VM_JL(vm, line);
      } break;
      case Instruction_JM: {
        VM_JM(vm, line);
      } break;
      case Instruction_JNE: {
        VM_JNE(vm, line);
      } break;
      case Instruction_MOV: {
        VM_Mov(vm, line);
      } break;
      case Instruction_MSET: {
        VM_MSet(vm, line);
      } break;
      case Instruction_PUTC: {
        VM_Putc(vm, line);
      } break;
      case Instruction_PUTI: {
        VM_Puti(vm, line);
      } break;
      case Instruction_PUTS: {
        VM_Puts(vm, line);
      } break;
      case Instruction_CALL: {
        VM_Call(vm, line);
      } break;
      case Instruction_SWST: {
        VM_Swst(vm, line);
      } break;
      case Instruction_WRITE: {
        VM_Write(vm, line);
      } break;
      case Instruction_READ: {
        VM_Read(vm, line);
      } break;
      case Instruction_OPEN: {
        VM_Open(vm, line);
      } break;
      case Instruction_EXIT: {
        vm.status = VM_Status_Ret;
      } break;
      default: MewUserAssert(false, "unsupported instruction");
    }
  }

  void Run(VirtualMachine& vm, Code& code) {
    size_t code_size = __VM_ALIGN(code.capacity, VM_CODE_ALIGN);
    MewAssert(vm.capacity > code_size);
    byte* begin = vm.memory;
    byte* end   = begin+vm.capacity;
    byte* alloc_space = begin+code_size+1;
    vm.heap = alloc_space;
    vm.begin = begin;
    vm.end = end;
    vm.status = VM_Status_Execute;
    if (code.data != nullptr) {
      memcpy(vm.heap, code.data, code.data_size*sizeof(*code.data));
    }
    while (vm.begin < vm.end && vm.status != VM_Status_Ret) {
      RunLine(vm, vm.begin);
      vm.begin += VM_CODE_ALIGN;
    }
    vm.status = VM_Status_Panding;
  }

  void Execute(VirtualMachine& vm, Code& code) {
    Alloc(vm, code);
    LoadMemory(vm, code);
    Run(vm, code);
  }
  
  void Execute(Code& code) {
    VirtualMachine vm;
    Alloc(vm, code);
    LoadMemory(vm, code);
    Run(vm, code);
  }

  void Execute(const char* path) {
    Code* code = Code_LoadFromFile(path);
    Execute(*code);
  }

  void ExecuteEx(VirtualMachine& vm, CodeExtended& code) {
    Alloc(vm, *code.code);
    LoadMemory(vm, *code.code);
    Run(vm, *code.code);
    vm.procs = code.manifest->procs;
  }
  
  void ExecuteEx(CodeExtended& code) {
    VirtualMachine vm;
    ExecuteEx(vm, code);
  }

  void ExecuteEx(const char* path) {
    CodeExtended* code = Code_LoadFromFileEx(path);
    ExecuteEx(*code);
  }

  // template<size_t alloc_size = 8>
  class CodeBuilder {
  public:
    struct untyped_pair {
      byte* data;
      byte size;
    };
    static const size_t alloc_size = 8;
  private:
    size_t capacity, size, code_cursor = 0;
    byte* code;
    size_t _data_size = 0;
    byte* data = nullptr;
    byte cursor = 0;
    byte line[alloc_size];
  public:
    CodeBuilder(): capacity(alloc_size), size(0), 
      code(new byte[alloc_size]), _data_size(0) { memset(line, 0, alloc_size); memset(code, 0, alloc_size); }

    size_t code_size() const noexcept {
      return size;
    }

    size_t abs_code_size() const noexcept {
      return size+cursor;
    }
    
    size_t data_size() const noexcept {
      return _data_size;
    }

    void Upsize(size_t _size = alloc_size) {
      byte* __new_code = new byte[capacity+_size];
      memset(__new_code, 0, capacity);
      memcpy(__new_code, code, capacity);
      capacity += _size;
      byte* __old_code = code;
      code = __new_code;
      free(__old_code);
    }

    void Enter() {
      /* skip */
      if (cursor == 0) { return; }
      Upsize();
      memcpy(code+size, line, alloc_size);
      memset(line, 0, alloc_size);
      size += alloc_size;
      cursor = 0;
      code_cursor++;
    }

    size_t Rows() {
      return size/alloc_size;
    }

    void ShiftCursor(int offset) {
      code_cursor += offset;
      code_cursor = code_cursor % (size+1);
      code_cursor = code_cursor < 0? 0: code_cursor;
      code += code_cursor*alloc_size;
    }
    void ResetCursor(int offset) {
      code -= size - (code_cursor*alloc_size);
      code_cursor = size/alloc_size;
    }
    
    friend CodeBuilder& operator+(CodeBuilder& cb, const CodeBuilder& i) {
      size_t __size = i._data_size;
      size_t __rsize = __size;
      if (!cb.data) {
        cb.data = new byte[__rsize];
      } else {
        byte* __new = new byte[cb._data_size+__rsize];
        memcpy(__new, cb.data, cb._data_size);
        byte* __old = cb.data; 
        cb.data = __new;
        free(__old);
      }
      memset(cb.data+cb._data_size, 0, __rsize);
      memcpy(cb.data+cb._data_size, i.data, __rsize);
      cb._data_size += __rsize;
      return cb;
    }
    friend CodeBuilder& operator+(CodeBuilder& cb, const char* text) {
      size_t __size = strlen(text);
      size_t __rsize = (__size+1)*sizeof(char);
      if (!cb.data) {
        cb.data = new byte[__rsize];
      } else {
        byte* __new = new byte[cb._data_size+__rsize];
        memcpy(__new, cb.data, cb._data_size);
        byte* __old = cb.data; 
        cb.data = __new;
        free(__old);
      }
      memset(cb.data+(cb._data_size*sizeof(char)), 0, __rsize);
      memcpy(cb.data+(cb._data_size*sizeof(char)), text, __rsize);
      cb._data_size += __rsize;
      return cb;
    }
    friend CodeBuilder& operator+(CodeBuilder& cb, const wchar_t* text) {
      size_t __size = wcslen(text);
      size_t __rsize = (__size+1)*sizeof(wchar_t);
      if (!cb.data) {
        cb.data = new byte[__rsize];
      } else {
        byte* __new = new byte[cb._data_size+__rsize];
        memcpy(__new, cb.data, cb._data_size);
        byte* __old = cb.data; 
        cb.data = __new;
        free(__old);
      }
      memset(cb.data+(cb._data_size*sizeof(wchar_t)), 0, __rsize);
      memcpy(cb.data+(cb._data_size*sizeof(wchar_t)), text, __rsize);
      cb._data_size += __rsize;
      return cb;
    }

    CodeBuilder& operator+=(const wchar_t* text) {
      return (*this)+text;
    }
    CodeBuilder& operator+=(const char* text) {
      return (*this)+text;
    }
    CodeBuilder& operator+=(CodeBuilder& i) {
      return (*this)+i;
    }
    
    friend CodeBuilder& operator<<(CodeBuilder& cb, CodeBuilder& i) {
      cb.Enter();
      cb.Upsize(i.capacity);
      memcpy(cb.code+cb.size, i.code, i.capacity);
      cb.size += i.capacity;
      cb += i;
      return cb;
    } 

    friend CodeBuilder& operator<<(CodeBuilder& cb, byte i) {
      if (cb.cursor+1 >= alloc_size) {
        cb.Enter();
      }
      cb.line[cb.cursor++] = i;
      return cb;
    } 
    friend CodeBuilder& operator<<(CodeBuilder& cb, uint i) {
      if (cb.cursor+sizeof(i) >= alloc_size) {
        cb.Enter();
      }
      memcpy(cb.line+cb.cursor, &i, sizeof(i));
      cb.cursor += sizeof(i); 
      return cb;
    }
    friend CodeBuilder& operator<<(CodeBuilder& cb, Instruction i) {
      if (cb.cursor+1 >= alloc_size) {
        cb.Enter();
      }
      cb.line[cb.cursor++] = i;
      return cb;
    }
    friend CodeBuilder& operator<<(CodeBuilder& cb, int i) {
      if (cb.cursor+sizeof(i) >= alloc_size) {
        cb.Enter();
      }
      memcpy(cb.line+cb.cursor, &i, sizeof(i));
      cb.cursor += sizeof(i); 
      return cb;
    }
    friend CodeBuilder& operator<<(CodeBuilder& cb, untyped_pair i) {
      if (cb.cursor+i.size >= alloc_size) {
        cb.Enter();
      }
      memcpy(cb.line+cb.cursor, &i.data, i.size);
      cb.cursor += i.size; 
      return cb;
    }

    CodeBuilder operator++(int) {
      Enter();
      return *this;
    }

    Code* operator*() {
      Code* c = new Code();
      c->capacity   = size;
      c->playground = (Instruction*)(code);
      c->data_size  = _data_size;
      c->data       = data;
      return c;
    }
    Code operator*(int) {
      Code c;
      c.capacity    = size;
      c.playground  = (Instruction*)code;
      c.data_size   = _data_size;
      c.data        = data;
      return c;
    }

    byte* at(int idx) {
      uint real_idx = (size + idx) % size;
      MewAssert(real_idx < size);
      return (code+real_idx);
    }

    byte* operator[](int idx) {
      return at(idx);
    }

    void force_data(uint _size) {
      byte* _ndata = new byte[_data_size+_size];
      memcpy(_ndata, data, _data_size);
      _data_size += _size;
      data = _ndata;
    }
    
  };
}
namespace Tests {
  bool test_Virtual() {
    try {
      using namespace Virtual;
      CodeBuilder builder;
      builder << Instruction_PUTS;
      builder << 0U;
      builder++;
      builder << Instruction_RET;
      builder++;
      builder += L"hellow word";
      Code* code = *builder;
      Code_SaveFromFile(*code, "./hellow_word.nb");
      // printf("[%u|%u]\n", code->capacity, code->data_size);
      Execute("./hellow_word.nb");
    } catch (std::exception e) {
      MewPrintError(e);
      return false;
    }
    return true;
  }
}

#endif