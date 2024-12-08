#ifndef _NAN_VIRTUAL_IMPL
#define _NAN_VIRTUAL_IMPL

#include "config.h"
#include "mewlib.h"
#include <stack>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <fcntl.h>
#include <vector>
#ifndef _WIN32
#include <windows.h>
#endif
// #include "dlllib.hpp"

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

  #define VIRTUAL_VERSION (Instruction_PUTS*100)+0x30

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

  enum VM_flags {
    None = 0,
    HeapLockExecute = 1 << 1,
  };

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
    VM_flags flags = HeapLockExecute;
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

  void VM_Push(VirtualMachine& vm) {
    byte head_byte = *vm.begin++;
    switch (head_byte) {
      case 0:
      case Instruction_FLT:
      case Instruction_NUM: {
        uint number = 0;
        memcpy(&number, vm.begin, sizeof(number));
        vm.stack.push(number);
        vm.begin += sizeof(number);
      } break;
      case Instruction_MEM: {
        uint number = 0;
        memcpy(&number, vm.begin, sizeof(number));
        MewUserAssert(vm.heap+number < vm.end, "out of memory");
        byte* pointer = vm.heap+number;
        uint x; memcpy(&x, pointer, sizeof(x));
        vm.stack.push(x);
        vm.begin += sizeof(number);
      } break;
      case Instruction_RMEM: {
        uint number = 0;
        memcpy(&number, vm.begin, sizeof(number));
        MewUserAssert(vm.heap+number < vm.end, "out of memory");
        vm.stack.push(number);
        vm.begin += sizeof(number);
      } break;

      default: MewNot(); break;
    }
  }
  
  void VM_Pop(VirtualMachine& vm) {
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

  void VM_Call(VirtualMachine& vm) {
    MewNotImpl();
  }

  void VM_MathBase(VirtualMachine& vm, uint* x, uint* y, byte** mem = nullptr) {
    byte type_x = *vm.begin++;
    byte type_y = *vm.begin++;
    VM_StackTop(vm, type_x, x, mem);
    VM_StackTop(vm, type_y, y);
  }
  void VM_Add(VirtualMachine& vm) {
    int x, y;
    byte* mem;
    byte type = *vm.begin;
    VM_MathBase(vm, (uint*)&x, (uint*)&y, &mem);
    x += y;
    VM_ManualPush(vm, x);
    if (type == Instruction_MEM) {
      memcpy(mem, &x, sizeof(x));
    }
  }
  void VM_Sub(VirtualMachine& vm) {
    int x, y;
    byte* mem;
    byte type = *vm.begin;
    VM_MathBase(vm, (uint*)&x, (uint*)&y, &mem);
    x -= y;
    VM_ManualPush(vm, x);
    if (type == Instruction_MEM) {
      memcpy(mem, &x, sizeof(x));
    }
  }
  void VM_Mul(VirtualMachine& vm) {
    int x, y;
    byte* mem;
    byte type = *vm.begin;
    VM_MathBase(vm, (uint*)&x, (uint*)&y, &mem);
    x *= y;
    VM_ManualPush(vm, x);
    if (type == Instruction_MEM) {
      memcpy(mem, &x, sizeof(x));
    }
  }
  void VM_Div(VirtualMachine& vm) {
    int x, y;
    byte* mem;
    byte type = *vm.begin;
    VM_MathBase(vm, (uint*)&x, (uint*)&y, &mem);
    x /= y;
    VM_ManualPush(vm, x);
    if (type == Instruction_MEM) {
      memcpy(mem, &x, sizeof(x));
    }
  }
  void VM_Inc(VirtualMachine& vm) {
    uint x;
    byte* mem;
    byte type = *vm.begin++;
    VM_StackTop(vm, type, &x, &mem);
    x++;
    VM_ManualPush(vm, x);
    if (type == Instruction_MEM) {
      memcpy(mem, &x, sizeof(x));
    }
  }
  void VM_Dec(VirtualMachine& vm) {
    uint x;
    byte* mem;
    byte type = *vm.begin++;
    VM_StackTop(vm, type, &x, &mem);
    x--;
    VM_ManualPush(vm, x);
    if (type == Instruction_MEM) {
      memcpy(mem, &x, sizeof(x));
    }
  }
  void VM_Xor(VirtualMachine& vm) {
    int x, y;
    byte* mem;
    byte type = *vm.begin;
    VM_MathBase(vm, (uint*)&x, (uint*)&y, &mem);
    x ^= y;
    VM_ManualPush(vm, x);
    if (type == Instruction_MEM) {
      memcpy(mem, &x, sizeof(x));
    }
  }
  void VM_Or(VirtualMachine& vm) {
    int x, y;
    byte* mem;
    byte type = *vm.begin;
    VM_MathBase(vm, (uint*)&x, (uint*)&y, &mem);
    x |= y;
    VM_ManualPush(vm, x);
    if (type == Instruction_MEM) {
      memcpy(mem, &x, sizeof(x));
    }
  }
  void VM_Not(VirtualMachine& vm) {
    uint x;
    byte* mem;
    byte type = *vm.begin++;
    VM_StackTop(vm, type, &x, &mem);
    x = ~x;
    VM_ManualPush(vm, x);
    if (type == Instruction_MEM) {
      memcpy(mem, &x, sizeof(x));
    }
  }
  void VM_And(VirtualMachine& vm) {
    int x, y;
    byte* mem;
    byte type = *vm.begin;
    VM_MathBase(vm, (uint*)&x, (uint*)&y, &mem);
    x &= y;
    VM_ManualPush(vm, x);
    if (type == Instruction_MEM) {
      memcpy(mem, &x, sizeof(x));
    }
  }
  void VM_LS(VirtualMachine& vm) {
    int x, y;
    byte* mem;
    byte type = *vm.begin;
    VM_MathBase(vm, (uint*)&x, (uint*)&y, &mem);
    x <<= y;
    VM_ManualPush(vm, x);
    if (type == Instruction_MEM) {
      memcpy(mem, &x, sizeof(x));
    }
  }
  void VM_RS(VirtualMachine& vm) {
    int x, y;
    byte* mem;
    byte type = *vm.begin;
    VM_MathBase(vm, (uint*)&x, (uint*)&y, &mem);
    x >>= y;
    VM_ManualPush(vm, x);
    if (type == Instruction_MEM) {
      memcpy(mem, &x, sizeof(x));
    }
  }
  
  void VM_ManualJmp(VirtualMachine& vm, int offset) {
    MewUserAssert(MEW_IN_RANGE(vm.memory, vm.end, vm.begin+offset), 
      "out of memory");
    vm.begin_stack.push(vm.begin);
    vm.begin += offset;
  }
  
  void VM_Jmp(VirtualMachine& vm) {
    int offset;
    memcpy(&offset, vm.begin, sizeof(int)); vm.begin += sizeof(int);
    MewUserAssert(MEW_IN_RANGE(vm.memory, vm.end, vm.begin+offset), 
      "out of memory");
    vm.begin_stack.push(vm.begin);
    vm.begin += offset;
  }

  void VM_Ret(VirtualMachine& vm) {
    if (vm.begin_stack.empty()) {
      vm.status = VM_Status_Ret; return;
    }
    byte* begin = vm.begin_stack.top();
    vm.begin = begin;
    vm.begin_stack.pop();
  }

  void VM_Test(VirtualMachine& vm) {
    int x, y;
    VM_MathBase(vm, (uint*)&x, (uint*)&y);
    int result = memcmp(&x, &y, sizeof(x));
    if (result > 0) {
      vm.test = VM_TestStatus_More;
    } else if (result < 0) {
      vm.test = VM_TestStatus_Less;
    } else {
      vm.test = VM_TestStatus_Equal;
    }
  }

  void VM_JE(VirtualMachine& vm) {
    int offset; 
    memcpy(&offset, vm.begin, sizeof(int));
    vm.begin += sizeof(int);
    if (vm.test == VM_TestStatus_Equal) {
      VM_ManualJmp(vm, offset);
    }
  }
  void VM_JEL(VirtualMachine& vm) {
    int offset; 
    memcpy(&offset, vm.begin, sizeof(int));
    vm.begin += sizeof(int);
    if (MEW_FIND_MASK(VM_TestStatus_EqualLess, vm.test)) {
      VM_ManualJmp(vm, offset);
    }
  }
  void VM_JEM(VirtualMachine& vm) {
    int offset; 
    memcpy(&offset, vm.begin, sizeof(int));
    vm.begin += sizeof(int);
    if (MEW_FIND_MASK(VM_TestStatus_EqualMore, vm.test)) {
      VM_ManualJmp(vm, offset);
    }
  }
  void VM_JL(VirtualMachine& vm) {
    int offset; 
    memcpy(&offset, vm.begin, sizeof(int));
    vm.begin += sizeof(int);
    if (vm.test == VM_TestStatus_Less) {
      VM_ManualJmp(vm, offset);
    }
  }
  void VM_JM(VirtualMachine& vm) {
    int offset; 
    memcpy(&offset, vm.begin, sizeof(int));
    vm.begin += sizeof(int);
    if (vm.test == VM_TestStatus_More) {
      VM_ManualJmp(vm, offset);
    }
  }
  void VM_JNE(VirtualMachine& vm) {
    int offset; 
    memcpy(&offset, vm.begin, sizeof(int));
    vm.begin += sizeof(int);
    if (vm.test != VM_TestStatus_Equal) {
      VM_ManualJmp(vm, offset);
    }
  }

  void VM_Mov(VirtualMachine& vm) {
    uint x; 
    VM_StackTop(vm, *vm.begin++, &x);
    uint offset;
    memcpy(&offset, vm.begin++, sizeof(uint));
    MewUserAssert(vm.heap+offset < vm.end, "out of memory");
    byte* pointer = vm.heap+offset;
    memcpy(pointer, &x, sizeof(x));
  }
  
  void VM_MSet(VirtualMachine& vm) {
    uint x; /* start */
    uint y; /* size  */
    uint z; /* value */
    memcpy(&x, vm.begin, sizeof(x)); vm.begin += sizeof(x);
    memcpy(&y, vm.begin, sizeof(y)); vm.begin += sizeof(y);
    memcpy(&z, vm.begin, sizeof(z)); vm.begin += sizeof(z);
    MewUserAssert(vm.heap+x < vm.end, "out of memory");
    MewUserAssert(vm.heap+x+y < vm.end, "out of memory");
    memset(vm.heap+x, z, y);
  }

  void VM_Putc(VirtualMachine& vm) {
    wchar_t long_char;
    memcpy(&long_char, vm.begin, sizeof(wchar_t)); vm.begin+=sizeof(wchar_t);
    putwchar(long_char);
  }
  
  void VM_Puti(VirtualMachine& vm) {
    int x;
    VM_StackTop(vm, *vm.begin++, (uint*)&x);
    char str[12] = {0};
    itoa(x, str, 10);
    fputs(str, stdout);
  }

  void VM_Puts(VirtualMachine& vm) {
    uint offset;
    memcpy(&offset, vm.begin, sizeof(uint)); vm.begin+=sizeof(uint);
    MewUserAssert(vm.heap+offset < vm.end, "out of memory");
    byte* pointer = vm.heap+offset;
    wchar_t* begin = (wchar_t*)pointer;
    while (*(begin) != 0) {
      putwchar(*(begin++));
    }
  }

  void VM_Open(VirtualMachine& vm) {
    uint offset;
    memcpy(&offset, vm.begin, sizeof(uint)); vm.begin+=sizeof(uint);
    MewUserAssert(vm.heap+offset < vm.end, "out of memory");
    byte* pointer = vm.heap+offset;
    char* begin = (char*)pointer;
    int flags;
    memcpy(&flags, vm.begin, sizeof(int)); vm.begin+=sizeof(int);
    int dest = open(begin, flags);
    VM_ManualPush(vm, dest);
  }

  void VM_Swst(VirtualMachine& vm) {
    int idx;
    bool use_stack;
    memcpy(&use_stack, vm.begin++, sizeof(use_stack));
    if (use_stack) {
      VM_StackTop(vm, *vm.begin++, (uint*)&idx);
    } else {
      memcpy(&idx, vm.begin, sizeof(idx)); vm.begin+=sizeof(idx);
    }
    vm.r_stream = fdopen(idx, "r+");
  }
  
  void VM_Write(VirtualMachine& vm) {
    uint offset;
    memcpy(&offset, vm.begin, sizeof(uint)); vm.begin+=sizeof(uint);
    MewUserAssert(vm.heap+offset < vm.end, "out of memory");
    byte* pointer = vm.heap+offset;
    fputws((wchar_t*)pointer, vm.r_stream);
  }
  
  void VM_Read(VirtualMachine& vm) {
    uint offset;
    memcpy(&offset, vm.begin, sizeof(uint)); vm.begin+=sizeof(uint);
    MewUserAssert(vm.heap+offset < vm.end, "out of memory");
    byte* pointer = vm.heap+offset;
    short int chunk_size;
    memcpy(&chunk_size, vm.begin, sizeof(chunk_size)); vm.begin+=sizeof(chunk_size);
    MewUserAssert(vm.heap+offset+(chunk_size*2) < vm.end, "out of memory (chunk too big)");
    fgetws((wchar_t*)pointer, chunk_size, vm.r_stream);
  }

  void RunLine(VirtualMachine& vm) {
    byte head_byte = *vm.begin++;
    if (MEW_FIND_MASK(vm.flags,VM_flags::HeapLockExecute)) { 
      MewAssert(vm.begin < vm.heap);
    }
    switch (head_byte) {
      case Instruction_NONE: break;
      case Instruction_PUSH: {
        VM_Push(vm);
      } break;
      case Instruction_POP: {
        VM_Pop(vm);
      } break;
      case Instruction_ADD: {
        VM_Add(vm);
      } break;
      case Instruction_SUB: {
        VM_Sub(vm);
      } break;
      case Instruction_MUL: {
        VM_Mul(vm);
      } break;
      case Instruction_DIV: {
        VM_Div(vm);
      } break;
      case Instruction_INC: {
        VM_Inc(vm);
      } break;
      case Instruction_DEC: {
        VM_Dec(vm);
      } break;
      case Instruction_XOR: {
        VM_Xor(vm);
      } break;
      case Instruction_OR: {
        VM_Or(vm);
      } break;
      case Instruction_NOT: {
        VM_Not(vm);
      } break;
      case Instruction_LS: {
        VM_LS(vm);
      } break;
      case Instruction_RS: {
        VM_RS(vm);
      } break;
      case Instruction_JMP: {
        VM_Jmp(vm);
      } break;
      case Instruction_RET: {
        VM_Ret(vm);
      } break;
      case Instruction_TEST: {
        VM_Test(vm);
      } break;
      case Instruction_JE: {
        VM_JE(vm);
      } break;
      case Instruction_JEL: {
        VM_JEL(vm);
      } break;
      case Instruction_JEM: {
        VM_JEM(vm);
      } break;
      case Instruction_JL: {
        VM_JL(vm);
      } break;
      case Instruction_JM: {
        VM_JM(vm);
      } break;
      case Instruction_JNE: {
        VM_JNE(vm);
      } break;
      case Instruction_MOV: {
        VM_Mov(vm);
      } break;
      case Instruction_MSET: {
        VM_MSet(vm);
      } break;
      case Instruction_PUTC: {
        VM_Putc(vm);
      } break;
      case Instruction_PUTI: {
        VM_Puti(vm);
      } break;
      case Instruction_PUTS: {
        VM_Puts(vm);
      } break;
      case Instruction_CALL: {
        VM_Call(vm);
      } break;
      case Instruction_SWST: {
        VM_Swst(vm);
      } break;
      case Instruction_WRITE: {
        VM_Write(vm);
      } break;
      case Instruction_READ: {
        VM_Read(vm);
      } break;
      case Instruction_OPEN: {
        VM_Open(vm);
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
      RunLine(vm);
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

  // template<size_t alloc_size = 8>
  class CodeBuilder {
  public:
    struct untyped_pair {
      byte* data;
      byte size;
    };
    static const size_t alloc_size = 8;
  private:
    size_t capacity, size;
    byte* code = nullptr, *code_cursor;
    size_t _data_size = 0;
    byte* data = nullptr;
    byte cursor = 0;
    byte line[alloc_size];
  public:
    CodeBuilder(): capacity(alloc_size), size(0), 
      code((byte*)realloc(NULL, alloc_size)), _data_size(0) { memset(line, 0, alloc_size); memset(code, 0, alloc_size); }

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
      byte* __temp_p = (byte*)realloc(code, capacity+_size);
      code = __temp_p;
      capacity += _size;
    }

    void UpsizeIfNeeds(size_t needs_size) {
      if (size+needs_size > capacity) {
        Upsize(needs_size);
      }
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
      cb.Upsize(i.capacity);
      memcpy(cb.code+cb.size, i.code, i.capacity);
      cb.size += i.capacity;
      cb += i;
      return cb;
    } 

    friend CodeBuilder& operator<<(CodeBuilder& cb, byte i) {
      cb.UpsizeIfNeeds(sizeof(i));
      cb.code[cb.size++] = i;
      return cb;
    } 
    friend CodeBuilder& operator<<(CodeBuilder& cb, uint i) {
      cb.UpsizeIfNeeds(sizeof(i));
      memcpy(cb.code+cb.size, &i, sizeof(i));
      cb.size += sizeof(i);
      return cb;
    }
    friend CodeBuilder& operator<<(CodeBuilder& cb, Instruction i) {
      cb.UpsizeIfNeeds(sizeof(i));
      cb.code[cb.size++] = i;
      return cb;
    }
    friend CodeBuilder& operator<<(CodeBuilder& cb, int i) {
      cb.UpsizeIfNeeds(sizeof(i));
      memcpy(cb.code+cb.size, &i, sizeof(i));
      cb.size += sizeof(i);
      return cb;
    }
    friend CodeBuilder& operator<<(CodeBuilder& cb, untyped_pair i) {
      cb.UpsizeIfNeeds(i.size);
      memcpy(cb.code+cb.size, &i.data, i.size);
      cb.size += i.size;
      return cb;
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
      builder << Instruction_EXIT;
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