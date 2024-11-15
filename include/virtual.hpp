#ifndef _NAN_VIRTUAL_IMPL
#define _NAN_VIRTUAL_IMPL

#include "config.h"
#include "mewlib.h"
#include <stack>
#include <cstring>
#include <filesystem>
#include <fstream>

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
  enum Instruction: byte {
    Instruction_NONE = 0,
    Instruction_PUSH,
    Instruction_POP,
    Instruction_ADD,
    Instruction_SUB,
    Instruction_MUL,
    Instruction_DIV,

    Instruction_XOR,
    Instruction_OR,
    Instruction_NOT,
    Instruction_AND,
    Instruction_LS, // left shift
    Instruction_RS, // right shift

    Instruction_NUM,  // arg type | number
    Instruction_MEM,  // arg type | memory
    /*depricated*/
    Instruction_HEAP, // arg type | heap begin
    Instruction_ST,   // arg type | stack top
    
    Instruction_JMP,
    Instruction_RET,
    Instruction_TEST,
    Instruction_JE,
    Instruction_JEL,
    Instruction_JEM,
    Instruction_JNE,
    Instruction_JL,
    Instruction_JM,
    Instruction_MOV,  // replace head data from stack to memory
    Instruction_PUTC,
    Instruction_PUTI,
    Instruction_PUTS,
  };

  struct Code {
    size_t capacity;
    Instruction* playground;
    size_t data_size = 0;
    byte* data = nullptr;
  };
 
  void Code_SaveFromFile(const Code& code, const std::filesystem::path& path) {
    std::ofstream file(path, std::ios::out | std::ios::binary);
    MewAssert(file.is_open());
    file.seekp(std::ios::beg);
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

  [[deprecated]]
  void Code_SaveFromFile(const Code& code, const wchar_t* path) {
    std::filesystem::path __path(path);
    __path = std::filesystem::absolute(__path.lexically_normal());
    Code_SaveFromFile(code, __path);
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

  [[deprecated]]
  Code* Code_LoadFromFile(const wchar_t* path) {
    std::filesystem::path __path(path);
    __path = std::filesystem::absolute(__path.lexically_normal());
    return Code_LoadFromFile(__path);
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

  struct VirtualMachine {
    size_t capacity;
    byte *memory, *heap, 
      *begin, *end;
    std::stack<uint> stack;
    std::stack<byte*> begin_stack;
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

  void LoadMemory(VirtualMachine& vm, Code& code) {
    vm.memory = (byte*)code.playground;
  }

  void VM_ManualPush(VirtualMachine& vm, uint x) {
    vm.stack.push(x);
  }

  void VM_Push(VirtualMachine& vm, byte* line) {
    byte head_byte = line[1];
    switch (head_byte) {
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
        vm.stack.push(*pointer);
      } break;

      default: MewNot(); break;
    }
  }
  
  void VM_Pop(VirtualMachine& vm, byte* line) {
    MewAssert(!vm.stack.empty());
    vm.stack.pop();
  }
  
  void VM_StackTop(VirtualMachine& vm, byte type, uint* x) {
    switch (type) {
      case Instruction_NUM: {
        MewUserAssert(!vm.stack.empty(), "stack is empty");
        uint _top = vm.stack.top();
        *x = _top;
      } break;
      case Instruction_MEM: {
        MewUserAssert(!vm.stack.empty(), "stack is empty");
        uint _top = vm.stack.top();
        uint offset = _top;
        MewUserAssert(vm.heap+offset < vm.end, "out of memory");
        byte* pointer = vm.heap+offset;
        *x = *pointer;
      } break;

      default: MewNot(); break;
    }
    vm.stack.pop();
  }

  void VM_MathBase(VirtualMachine& vm, byte* line, uint* x, uint* y) {
    byte type_x = line[1];
    byte type_y = line[2];
    VM_StackTop(vm, type_x, x);
    VM_StackTop(vm, type_x, y);
  }
  void VM_Add(VirtualMachine& vm, byte* line) {
    int x, y, c;
    VM_MathBase(vm, line, (uint*)&x, (uint*)&y);
    c = x+y;
    VM_ManualPush(vm, (uint)c);
  }
  void VM_Sub(VirtualMachine& vm, byte* line) {
    int x, y, c;
    VM_MathBase(vm, line, (uint*)&x, (uint*)&y);
    c = x-y;
    VM_ManualPush(vm, (uint)c);
  }
  void VM_Mul(VirtualMachine& vm, byte* line) {
    int x, y, c;
    VM_MathBase(vm, line, (uint*)&x, (uint*)&y);
    c = x*y;
    VM_ManualPush(vm, (uint)c);
  }
  void VM_Div(VirtualMachine& vm, byte* line) {
    int x, y, c;
    VM_MathBase(vm, line, (uint*)&x, (uint*)&y);
    c = x/y;
    VM_ManualPush(vm, (uint)c);
  }
  void VM_Xor(VirtualMachine& vm, byte* line) {
    uint x, y, c;
    VM_MathBase(vm, line, &x, &y);
    c = x ^ y;
    VM_ManualPush(vm, c);
  }
  void VM_Or(VirtualMachine& vm, byte* line) {
    uint x, y, c;
    VM_MathBase(vm, line, &x, &y);
    c = x | y;
    VM_ManualPush(vm, c);
  }
  void VM_Not(VirtualMachine& vm, byte* line) {
    uint x;
    VM_StackTop(vm, line[1], &x);
    VM_ManualPush(vm, ~x);
  }
  void VM_And(VirtualMachine& vm, byte* line) {
    uint x, y, c;
    VM_MathBase(vm, line, &x, &y);
    c = x & y;
    VM_ManualPush(vm, c);
  }
  void VM_LS(VirtualMachine& vm, byte* line) {
    uint x, y, c;
    VM_MathBase(vm, line, &x, &y);
    c = x << y;
    VM_ManualPush(vm, c);
  }
  void VM_RS(VirtualMachine& vm, byte* line) {
    uint x, y, c;
    VM_MathBase(vm, line, &x, &y);
    c = x >> y;
    VM_ManualPush(vm, c);
  }
  
  void VM_ManualJmp(VirtualMachine& vm, int offset) {
    MewUserAssert(MEW_IN_RANGE(vm.memory, vm.end, vm.begin+offset), 
      "out of memory");
    vm.begin_stack.push(vm.begin);
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
    if (vm.test == VM_TestStatus_EqualLess) {
      VM_ManualJmp(vm, offset);
    }
  }
  void VM_JEM(VirtualMachine& vm, byte* line) {
    int offset; 
    memcpy(&offset, line+1, sizeof(int));
    if (vm.test == VM_TestStatus_EqualMore) {
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
    puts(str);
    free(str);
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
      case Instruction_PUTC: {
        VM_Putc(vm, line);
      } break;
      case Instruction_PUTI: {
        VM_Puti(vm, line);
      } break;
      case Instruction_PUTS: {
        VM_Puts(vm, line);
      } break;
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
      RunLine(vm, begin);
      begin += VM_CODE_ALIGN;
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

  void Execute(const wchar_t* path) {
    Code* code = Code_LoadFromFile(path);
    Execute(*code);
  }

  void Execute(const char* path) {
    Code* code = Code_LoadFromFile(path);
    Execute(*code);
  }


  // template<size_t alloc_size = 8>
  class CodeBuilder {
  public:
    static const size_t alloc_size = 8;
  private:
    size_t capacity, size, code_cursor = 0;
    byte* code;
    size_t data_size = 0;
    byte* data = nullptr;
    byte cursor = 0;
    byte line[alloc_size];
  public:
    CodeBuilder(): capacity(alloc_size), size(0), 
      code(new byte[alloc_size]) { memset(line, 0, alloc_size); memset(code, 0, alloc_size); }

    size_t code_size() const noexcept {
      return size;
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
      size_t __size = i.data_size;
      size_t __rsize = __size;
      if (!cb.data) {
        cb.data = new byte[__rsize];
      } else {
        byte* __new = new byte[cb.data_size+__rsize];
        memcpy(__new, cb.data, cb.data_size);
        byte* __old = cb.data; 
        cb.data = __new;
        free(__old);
      }
      memset(cb.data+cb.data_size, 0, __rsize);
      memcpy(cb.data+cb.data_size, i.data, __rsize);
      cb.data_size += __rsize;
      return cb;
    }
    friend CodeBuilder& operator+(CodeBuilder& cb, const wchar_t* text) {
      size_t __size = wcslen(text);
      size_t __rsize = (__size+1)*sizeof(wchar_t);
      if (!cb.data) {
        cb.data = new byte[__rsize];
      } else {
        byte* __new = new byte[cb.data_size+__rsize];
        memcpy(__new, cb.data, cb.data_size);
        byte* __old = cb.data; 
        cb.data = __new;
        free(__old);
      }
      memset(cb.data+(cb.data_size*sizeof(wchar_t)), 0, __rsize);
      memcpy(cb.data+(cb.data_size*sizeof(wchar_t)), text, __rsize);
      cb.data_size += __rsize;
      return cb;
    }

    CodeBuilder& operator+=(const wchar_t* text) {
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
      memcpy(cb.line+cb.cursor+1, &i, sizeof(i));
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
      memcpy(cb.line+cb.cursor+1, &i, sizeof(i));
      cb.cursor += sizeof(i); 
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
      c->data_size  = data_size;
      c->data       = data;
      return c;
    }
    Code operator*(int) {
      Code c;
      c.capacity    = size;
      c.playground  = (Instruction*)code;
      c.data_size   = data_size;
      c.data        = data;
      return c;
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
      printf("[%u|%u]\n", code->capacity, code->data_size);
      Execute("./hellow_word.nb");
    } catch (std::exception e) {
      MewPrintError(e);
      return false;
    }
    return true;
  }
}

#endif