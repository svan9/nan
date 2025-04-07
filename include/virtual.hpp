#ifndef _NAN_VIRTUAL_IMPL
#define _NAN_VIRTUAL_IMPL

#include <stack>
#include <stdlib.h>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <fcntl.h>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#endif
#include "mewall.h"
#include "mewmath.hpp"
#include "dlllib.hpp"
#pragma pack(push, 1)

// todo 
// stack offset as argument wheve   
namespace Virtual {
  using byte = mew::byte;
  struct VirtualMachine;
  typedef void(*VM_Processor)(VirtualMachine&, byte*);

  enum Instruction: byte {
    Instruction_NONE = 0,
    Instruction_LDLL,
    Instruction_CALL,
    Instruction_PUSH,
    Instruction_POP,
    Instruction_RPOP,

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
    Instruction_REG,  // arg type | memory
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
    Instruction_MOV,   // replace head data from stack to memory
    Instruction_SWAP,   // replace head data from stack to memory
    Instruction_MSET,

    Instruction_SWST,  // set used stream
    Instruction_WRITE, // write to used stream
    Instruction_READ,  // read used stream
    Instruction_OPEN,  // open file as destinator

    Instruction_LM,

    Instruction_PUTC,
    Instruction_PUTI,
    Instruction_PUTS,
    Instruction_GETCH,
    Instruction_MOVRDI,
  };

  #define VIRTUAL_VERSION (Instruction_PUTS*100)+0x55


  struct CodeManifest {
    // std::map<const char*, FuncInfo> procs;
  };

  struct VM_MANIFEST_FLAGS {
    bool has_debug: 1 = false;
    byte ch[3];
  }; // must be 4 byte;

  struct CodeDebugInfo {
    uint line;
    // const char* src;
    uint cursor;
  };

  struct FuncInfo {
    uint code_idx;
    const char* name;
    uint calloffset;
  };
  
  struct CodeManifestExtended {
    VM_MANIFEST_FLAGS flags;
    size_t size;
    mew::stack<CodeDebugInfo> debug;
    mew::stack<const char*> libs;
    mew::stack<FuncInfo, 8U> procs;
  };
  
  struct LabelInfo {
    const char* name;
    size_t cursor;
  };

  struct Code {
    size_t capacity;
    Instruction* playground;
    size_t data_size = 0;
    byte* data = nullptr;
    size_t adata_count = 0;
    byte* adata = nullptr;
    size_t labels_size = 0;
    LabelInfo* labels;
    CodeManifestExtended cme;

    size_t find_label(const char* name) {
      for (int i = 0; i < labels_size; i++) {
        if (mew::strcmp(labels[i].name, name)) {
          return labels[i].cursor;
        }
      }
      return -1;
    }
  };

  struct CodeExtended {
    CodeManifest* manifest;
    Code* code;
  };
  
  struct CodeManifestMarker {
    bool has_linked_files: 1;
  };

#pragma region FILE

// stoped development
  void Code_SaveFromFile(const Code& code, const std::filesystem::path& path) {
    std::ofstream file(path, std::ios::out | std::ios::binary);
    MewAssert(file.is_open());
    file.seekp(std::ios::beg);
    /* version */
    VM_MANIFEST_FLAGS mflags = code.cme.flags;
    mew::writeBytes(file, (uint)VIRTUAL_VERSION);
    mew::writeBytes(file, mflags, sizeof(uint));
    mew::writeBytes(file, code.capacity, sizeof(uint));
    mew::writeBytes(file, code.data_size, sizeof(uint));
    mew::writeBytes(file, code.adata_count, sizeof(uint));
    mew::writeBytes(file, code.labels_size, sizeof(uint));
    uint libsSize = static_cast<uint>(code.cme.libs.size());
    mew::writeBytes(file, libsSize, sizeof(uint));
    mew::writeSeqBytes(file, code.playground, code.capacity);
    mew::writeSeqBytes(file, code.data, code.data_size);
    mew::writeSeqBytes(file, code.adata, code.adata_count);
    mew::writeSeqBytes(file, code.labels, code.labels_size);
    mew::writeSeqBytes(file, code.cme.libs.begin(), code.cme.libs.size());
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
    // file.seekg(std::ios::beg);
    file >> std::noskipws;
    /* version */
    int file_version = mew::readInt4Bytes(file);
    if (file_version != VIRTUAL_VERSION) {
      MewWarn("file version not support (%i != %i)", file_version, VIRTUAL_VERSION); 
      return nullptr;
    }
    /** MANIFEST */
    Code* code = new Code();
    code->cme.flags = (VM_MANIFEST_FLAGS)mew::readInt4Bytes(file);
    code->capacity = mew::readInt4Bytes(file);
    code->data_size = mew::readInt4Bytes(file);
    code->adata_count = mew::readInt4Bytes(file);
    code->labels_size = mew::readInt4Bytes(file);
    uint libs_size = mew::readInt4Bytes(file);
    /* code */
    code->playground = new Instruction[code->capacity];
    for (int i = 0; i < code->capacity; i++) {
      file >> ((byte*)code->playground)[i];
    }
    /* data */
    code->data = new byte[code->data_size];
    for (int i = 0; i < code->data_size; i++) {
      file >> ((byte*)code->data)[i];
    }
    if (code->cme.flags.has_debug) {
      code->cme.size = mew::readInt4Bytes(file); 
      for (int i = 0; i < code->cme.size; i++) {
        CodeDebugInfo di; mew::readBytes(file, di);
        code->cme.debug.push(di);
      }
    }

    // adata
    code->adata = new byte[code->adata_count];
    for (int i = 0; i < code->data_size; i++) {
      file >> ((byte*)code->adata)[i];
    }

    // labels
    code->labels = new LabelInfo[code->labels_size];
    for (int i = 0; i < code->labels_size; i++) {
      LabelInfo li; mew::readBytes(file, li);
      code->labels[i] = li;
    }
    for (int i = 0; i < libs_size; i++) {
      const char* lib; mew::readBytes(file, lib);
      code->cme.libs.push(lib);
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
#pragma region VM
  enum VM_Status: byte {
    VM_Status_Panding = 0,
    VM_Status_Execute = 1 << 1,
    VM_Status_Ret     = 1 << 2,
    VM_Status_Error   = 1 << 3,
  };
  
  enum VM_TestStatus: byte {
    VM_TestStatus_Skip = 0,
    VM_TestStatus_Equal = 1 << 1,
    VM_TestStatus_Less  = 1 << 2,
    VM_TestStatus_More  = 1 << 3,
    VM_TestStatus_EqualMore  = VM_TestStatus_Equal | VM_TestStatus_More,
    VM_TestStatus_EqualLess  = VM_TestStatus_Equal | VM_TestStatus_Less,
  };
  

  enum VM_flags {
    None = 0,
    HeapLockExecute = 1 << 1,
  };

  template<size_t size>
  struct VM_Register {
    byte data[size];
  };
  
  enum struct VM_RegType: byte {
    None, R, RX, DX, FX
  };

#pragma pack(push, 4)
  struct VM_DEBUG {
    byte last_head_byte = 0;
    char* last_fn = 0;
  };
  struct VirtualMachine {
    FILE* std_in = stdin;
    FILE* std_out = stdout;
    Code* src;
    VM_DEBUG debug;
    VM_Register<4> _r[5];                       // 4*5(20)
    VM_Register<4> _fx[5];                      // 4*5(20)
    VM_Register<8> _rx[5];                      // 8*5(40)
    VM_Register<8> _dx[5];                      // 8*5(40)
    size_t capacity;                            // 8byte
    FILE *r_stream;                             // 8byte
    byte *memory, *heap,
        *begin, *end;                           // 4x8byte(24byte) 
    struct TestStatus {
      byte skip  : 1 = 0;
      byte equal : 1 = 0;
      byte less  : 1 = 0;
      byte more  : 1 = 0;
    } test;                                     // 1byte
    VM_Status status;                           // 1byte
    struct Flags {
      byte heap_lock_execute: 1 = 1;
      byte use_debug: 1 = 0;
      byte in_neib_ctx: 1 = false;
    } flags;                                    // 1byte
    byte _pad0[1];
    mew::stack<uint, 8U> stack;                 // 24byte
    size_t rdi = 0;
    mew::stack<byte *, 8U> begin_stack;         // 24byte
    mew::stack<mew::_dll_hinstance, 8U> hdlls;  // 24byte
    mew::stack<mew::_dll_farproc, 8U> hprocs;   // 24byte
    mew::stack<FuncInfo, 8U> procs;             // 24byte
    mew::stack<Code*, 8U> libs;                 // 24byte
    size_t process_cycle = 0;

    byte* getRegister(VM_RegType rt, byte idx, size_t* size = nullptr) {
      MewUserAssert(idx < 5, "undefined register idx");
      switch (rt) {
        case VM_RegType::R: 
          if (!size) {*size = 4;}
          return this->_r[idx].data;     
        case VM_RegType::RX: 
          if (!size) {*size = 8;}
          return this->_rx[idx].data;
        case VM_RegType::FX: 
          if (!size) {*size = 4;}
          return this->_fx[idx].data;
        case VM_RegType::DX: 
          if (!size) {*size = 8;}
          return this->_dx[idx].data;
        default: return nullptr;
      }
    }
  };                                            // 368byte 
#pragma pack(pop)

  struct Code_AData {
    size_t size;
  };

  size_t Code_CountAData(Code& code) {
    if (code.adata == nullptr) { return 0; }
    Code_AData* adata = (Code_AData*)code.adata;
    size_t size_couter = 0;
    for (int i = 0; i < code.adata_count; ++i) {
      size_couter += adata[i].size;
    }
    return size_couter;
  }
  
  void a() {
    sizeof(VirtualMachine);
  }

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
    size_t adata_count = Code_CountAData(code);
    size_t size = __VM_ALIGN(code.capacity+code.data_size+adata_count, VM_ALLOC_ALIGN);
    if ((size - code.capacity - code.data_size) <= 0) {
      size += VM_MINHEAP_ALIGN;
    }
    vm.memory = new byte[size];
    memset(vm.memory, Instruction_NONE, size);
    vm.capacity = size;
  }

  uint DeclareProccessor(VirtualMachine& vm, VM_Processor proc) {
    MewNotImpl();
    // vm.procs.push_back(proc);
    // return vm.procs.size()-1;
  }

  void LoadMemory(VirtualMachine& vm, Code& code) {
    vm.memory = (byte*)code.playground;
    // todo load from .nlib file 
    for (int i = 0; i < code.cme.libs.size(); ++i) {
      Code* lib = Code_LoadFromFile(code.cme.libs.at(i));
      vm.libs.push(lib);
    }
  }

  void VM_ManualPush(VirtualMachine& vm, uint x) {
    vm.stack.push(x);
  }

  void VM_Push(VirtualMachine& vm, byte head_byte, uint number) {
    switch (head_byte) {
      case 0:
      case Instruction_FLT:
      case Instruction_NUM: {
        vm.stack.push(number);
      } break;
      case Instruction_MEM: {
        MewUserAssert(vm.heap+number < vm.end, "out of memory");
        byte* pointer = vm.heap+number;
        uint x; memcpy(&x, pointer, sizeof(x));
        vm.stack.push(x, vm.rdi);
      } break;
      case Instruction_REG: {
        MewUserAssert(vm.heap+number < vm.end, "out of memory");
        vm.stack.push(number, vm.rdi);
      } break;
      case Instruction_ST: {
        MewUserAssert(vm.stack.has(number), "out of stack");
        vm.stack.push(vm.stack.at((int)number), vm.rdi);
      } break;
      default: MewNot(); break;
    }
  }

  byte* VM_GetReg(VirtualMachine& vm, size_t* size = nullptr) {
    byte rtype = *vm.begin++;
    byte ridx = *vm.begin++;
    return vm.getRegister((Virtual::VM_RegType)rtype, ridx);
  }

  void VM_Push(VirtualMachine& vm) {
    vm.debug.last_fn = (char*)__func__;
    Instruction head_byte = (Instruction)*vm.begin++;
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
        vm.stack.push(x, vm.rdi);
        vm.begin += sizeof(number);
      } break;
      case Instruction_REG: {
        size_t size;
        byte* reg = VM_GetReg(vm, &size);
        MewUserAssert(reg != nullptr, "invalid register");
        vm.stack.push((uint)*reg, vm.rdi);
        if (size == 8) {
          vm.stack.push((uint)*(reg+sizeof(uint)), vm.rdi);
        }
      } break;
      case Instruction_ST: {
        int number = 0;
        memcpy(&number, vm.begin, sizeof(number));
        MewUserAssert(vm.stack.has(number), "out of stack");
        vm.stack.push(vm.stack.at(number), vm.rdi);
        vm.begin += sizeof(number);
      } break;
      default: MewNot(); break;
    }
  }
  
  void VM_Pop(VirtualMachine& vm) {
    vm.debug.last_fn = (char*)__func__;
    MewAssert(!vm.stack.empty());
    vm.stack.pop();
  }

  void VM_RPop(VirtualMachine& vm) {
    vm.debug.last_fn = (char*)__func__;
    MewAssert(!vm.stack.empty());
    size_t size;
    byte* reg = VM_GetReg(vm, &size);
    if (size == 4) {
      uint value = vm.stack.pop();
      memcpy(reg, &value, sizeof(uint));
    } else
    if (size == 8) {
      long long value = vm.stack.npop<long long>();
      memcpy(reg, &value, sizeof(value));
    }
  }
  
  void VM_StackTop(VirtualMachine& vm, byte type, uint* x, byte** mem = nullptr) {
    switch (type) {
      case 0:
      case Instruction_FLT:
      case Instruction_ST:
      case Instruction_NUM: {
        MewUserAssert(!vm.stack.empty(), "stack is empty");
        uint _top = vm.stack.top(vm.rdi);
        memmove(x, &_top, sizeof(_top));
      } break;
      case Instruction_MEM: {
        MewUserAssert(!vm.stack.empty(), "stack is empty");
        uint _top = vm.stack.top(vm.rdi);
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
  }

  void VM_SwitchContext(VirtualMachine& vm, Code* code) {
    vm.flags.in_neib_ctx = true;
  }

  void VM_ManualCall(VirtualMachine& vm, int libIDX, const char* fname) {
    Code* lib = vm.libs.at(libIDX);
    size_t offset = lib->find_label(fname);
    MewUserAssert(offset != -1, "undefined function");
    vm.begin_stack.push(vm.begin);
    vm.begin = (byte*)lib->playground+offset;
    VM_SwitchContext(vm, lib);
  }

  void VM_Call(VirtualMachine& vm) {
    int lib_idx;
    memcpy(&lib_idx, vm.begin, sizeof(int)); vm.begin += sizeof(int);
    Code* lib = vm.libs.at(lib_idx);
    size_t flen = strlen((const char*)vm.begin);
    char* fname = new char[flen+1];
    memcpy(fname, vm.begin, flen+1); vm.begin += flen+1;
    VM_ManualCall(vm, lib_idx, fname);
  }

  void VM_MathBase(VirtualMachine& vm, uint* x, uint* y, byte** mem = nullptr) {
    byte type_x = *vm.begin++;
    byte type_y = *vm.begin++;
    vm.rdi += sizeof(uint);
    VM_StackTop(vm, type_x, x, mem);
    vm.rdi -= sizeof(uint);
    VM_StackTop(vm, type_y, y);
  }

  int VM_GetOffset(VirtualMachine& vm) {
    int offset;
    memcpy(&offset, vm.begin, sizeof(int)); vm.begin += sizeof(int);
    return offset/4;
  }

#pragma region VM_ARG 
  typedef struct {
    VM_RegType type;
    byte idx;
  } VM_REG_INFO;

  class VM_ARG {
  public:
    VM_ARG() {}
    byte* data;
    byte* data2;

    byte type;
    int& getInt() {
      return (int&)(*this->data);
    }
    lli& getLong() {
      return (lli&)(*this->data);
    }
    float& getFloat() {
      return (float&)(*this->data);
    }
    double& getDouble() {
      return (double&)(*this->data);
    }
    byte getByte() {
      return (byte)(*this->data);
    }

    static void do_math(VM_ARG& a, mew::asgio fn, bool depr_float = false) { 
      switch (a.type) {
        case Instruction_ST: mew::gen_asgio(fn, a.getInt()); break;
        case Instruction_REG: {
          VM_REG_INFO* ri = (VM_REG_INFO*)a.data2;
          switch (ri->type) {
            case VM_RegType::R: mew::gen_asgio(fn, a.getInt()); break;
            case VM_RegType::RX: mew::gen_asgio(fn, a.getLong()); break;
            case VM_RegType::FX: if (!depr_float) mew::gen_asgio(fn, a.getFloat()); break;
            case VM_RegType::DX: if (!depr_float) mew::gen_asgio(fn, a.getDouble()); break;
            default: MewUserAssert(false, "undefined reg type");
          }
          break;
        }
        default: MewUserAssert(false, "undefined arg type");
      } 
    }

    static void do_math(VM_ARG& a, VM_ARG& b, mew::adgio fn, bool depr_float = false) {
      switch (a.type) {
        case Instruction_ST: {
          switch (b.type) {
            case Instruction_ST: mew::gen_adgio(fn, a.getInt(), b.getInt()); break;
            case Instruction_REG: {
              VM_REG_INFO* ri = (VM_REG_INFO*)a.data2;
              switch (ri->type) {
                case VM_RegType::R: mew::gen_adgio(fn, a.getInt(), b.getInt()); break;
                case VM_RegType::RX: mew::gen_adgio(fn, a.getInt(), b.getLong()); break;
                case VM_RegType::FX: if (!depr_float) mew::gen_adgio(fn, a.getInt(), b.getFloat()); break;
                case VM_RegType::DX: if (!depr_float) mew::gen_adgio(fn, a.getInt(), b.getDouble()); break;
                default: MewUserAssert(false, "undefined reg type");
              }
            } break;
            case Instruction_NUM: {
              mew::gen_adgio(fn, a.getInt(), b.getInt());
            } break;
          }
        } break;
        case Instruction_REG: {
          VM_REG_INFO* ri = (VM_REG_INFO*)a.data2;
          switch (ri->type) {
            case VM_RegType::R: { 
              switch (b.type) {
                case Instruction_ST: mew::gen_adgio(fn, a.getInt(), b.getInt()); break;
                case Instruction_REG: {
                  VM_REG_INFO* ri = (VM_REG_INFO*)a.data2;
                  switch (ri->type) {
                    case VM_RegType::R: mew::gen_adgio(fn, a.getInt(), b.getInt()); break;
                    case VM_RegType::RX: mew::gen_adgio(fn, a.getInt(), b.getLong()); break;
                    case VM_RegType::FX: if (!depr_float) mew::gen_adgio(fn, a.getInt(), b.getFloat()); break;
                    case VM_RegType::DX: if (!depr_float) mew::gen_adgio(fn, a.getInt(), b.getDouble()); break;
                    default: MewUserAssert(false, "undefined reg type");
                  }
                } break;
                case Instruction_NUM: {
                  mew::gen_adgio(fn, a.getInt(), b.getInt());
                } break;
              }
            } break;
            case VM_RegType::RX: { 
              switch (b.type) {
                case Instruction_ST: mew::gen_adgio(fn, a.getLong(), b.getInt()); break;
                case Instruction_REG: {
                  VM_REG_INFO* ri = (VM_REG_INFO*)a.data2;
                  switch (ri->type) {
                    case VM_RegType::R: mew::gen_adgio(fn, a.getLong(), b.getInt()); break;
                    case VM_RegType::RX: mew::gen_adgio(fn, a.getLong(), b.getLong()); break;
                    case VM_RegType::FX: if (!depr_float) mew::gen_adgio(fn, a.getLong(), b.getFloat()); break;
                    case VM_RegType::DX: if (!depr_float) mew::gen_adgio(fn, a.getLong(), b.getDouble()); break;
                    default: MewUserAssert(false, "undefined reg type");
                  }
                } break;
                case Instruction_NUM: {
                  mew::gen_adgio(fn, a.getLong(), b.getInt());
                } break;
              }
            } break;
            case VM_RegType::FX: { 
              if (depr_float) break;
              switch (b.type) {
                case Instruction_ST: mew::gen_adgio(fn, a.getFloat(), b.getInt()); break;
                case Instruction_REG: {
                  VM_REG_INFO* ri = (VM_REG_INFO*)a.data2;
                  switch (ri->type) {
                    case VM_RegType::R: mew::gen_adgio(fn, a.getFloat(), b.getInt()); break;
                    case VM_RegType::RX: mew::gen_adgio(fn, a.getFloat(), b.getLong()); break;
                    case VM_RegType::FX: mew::gen_adgio(fn, a.getFloat(), b.getFloat()); break;
                    case VM_RegType::DX: mew::gen_adgio(fn, a.getFloat(), b.getDouble()); break;
                    default: MewUserAssert(false, "undefined reg type");
                  }
                } break;
                case Instruction_NUM: {
                  mew::gen_adgio(fn, a.getFloat(), b.getInt());
                } break;
              }
            } break;
            case VM_RegType::DX: { 
              if (depr_float) break;
              switch (b.type) {
                case Instruction_ST: mew::gen_adgio(fn, a.getDouble(), b.getInt()); break;
                case Instruction_REG: {
                  VM_REG_INFO* ri = (VM_REG_INFO*)a.data2;
                  switch (ri->type) {
                    case VM_RegType::R: mew::gen_adgio(fn, a.getDouble(), b.getInt()); break;
                    case VM_RegType::RX: mew::gen_adgio(fn, a.getDouble(), b.getLong()); break;
                    case VM_RegType::FX: mew::gen_adgio(fn, a.getDouble(), b.getFloat()); break;
                    case VM_RegType::DX: mew::gen_adgio(fn, a.getDouble(), b.getDouble()); break;
                    default: MewUserAssert(false, "undefined reg type");
                  }
                } break;
                case Instruction_NUM: {
                  mew::gen_adgio(fn, a.getDouble(), b.getInt());
                } break;
              }
            } break;
            default: MewUserAssert(false, "undefined reg type");
          }
        } break;
        default: MewUserAssert(false, "undefined arg type");
      } 
    }

    VM_ARG& operator++() {
      do_math(*this, mew::aginc);
      return *this;
    }

    VM_ARG& operator--() {
      do_math(*this, mew::agdec);
      return *this;
    }

    static void mov(VM_ARG& a, VM_ARG& b) {
      do_math(a, b, mew::agmov);
    }
    static void swap(VM_ARG& a, VM_ARG& b) {
      do_math(a, b, mew::agswap);
    }
  };

  VM_ARG& operator+(VM_ARG& a, VM_ARG& b) {
    VM_ARG::do_math(a, b, mew::agadd);
    return a;
  }
  VM_ARG& operator-(VM_ARG& a, VM_ARG& b) {
    VM_ARG::do_math(a, b, mew::agsub);
    return a;
  }
  VM_ARG& operator/(VM_ARG& a, VM_ARG& b) {
    VM_ARG::do_math(a, b, mew::agdiv);
    return a;
  }
  VM_ARG& operator*(VM_ARG& a, VM_ARG& b) {
    VM_ARG::do_math(a, b, mew::agmul);
    return a;
  }
  VM_ARG& operator>>(VM_ARG& a, VM_ARG& b) {
    VM_ARG::do_math(a, b, mew::agrs, true);
    return a;
  }
  VM_ARG& operator<<(VM_ARG& a, VM_ARG& b) {
    VM_ARG::do_math(a, b, mew::agls, true);
    return a;
  }
  VM_ARG& operator^(VM_ARG& a, VM_ARG& b) {
    VM_ARG::do_math(a, b, mew::agxor, true);
    return a;
  }
  VM_ARG& operator~(VM_ARG& a) {
    VM_ARG::do_math(a, mew::agnot, true);
    return a;
  }
  VM_ARG& operator|(VM_ARG& a, VM_ARG& b) {
    VM_ARG::do_math(a, b, mew::agor, true);
    return a;
  }
  VM_ARG& operator&(VM_ARG& a, VM_ARG& b) {
    VM_ARG::do_math(a, b, mew::agand, true);
    return a;
  }

  VM_ARG VM_GetArg(VirtualMachine& vm) {
    byte type = *vm.begin++;
    switch (type) {
      case Instruction_ST: {
        int offset;
        memcpy(&offset, vm.begin, sizeof(int)); vm.begin += sizeof(int);
        VM_ARG arg;
        byte* num = vm.stack.rat(-offset);
        int __num = *(int*)num;
        (void)__num;
        arg.data = num;
        arg.type = type;
        return arg;
      };
      case Instruction_REG: {
        byte rtype = *vm.begin++;
        byte ridx = *vm.begin++;
        size_t size;
        VM_ARG arg;
        arg.data = vm.getRegister((VM_RegType)rtype, ridx, &size);
        VM_REG_INFO* ri = new VM_REG_INFO();
        ri->idx = ridx;
        ri->type = (VM_RegType)rtype;
        arg.data2 = (byte*)ri;
        arg.type = type;
        return arg;
      }
      case Instruction_NUM: {
        int num;
        memcpy(&num, vm.begin, sizeof(int)); vm.begin += sizeof(int);
        VM_ARG arg;
        arg.data = (byte*)num;
        arg.type = type;
        return arg;
      }
    
      default: MewUserAssert(false, "undefined arg type");
    }
  }

#pragma endregion VM_ARG

  void VM_MovRDI(VirtualMachine& vm) {
    int offset = VM_GetOffset(vm);
    vm.rdi = offset;
  }

  void VM_Add(VirtualMachine& vm) {
    vm.debug.last_fn = (char*)__func__;
    auto a = VM_GetArg(vm);
    auto b = VM_GetArg(vm);
    a + b;
  }

  void VM_Sub(VirtualMachine& vm) {
    vm.debug.last_fn = (char*)__func__;
    auto a = VM_GetArg(vm);
    auto b = VM_GetArg(vm);
    a - b;
  }
  
  void VM_Mul(VirtualMachine& vm) {
    vm.debug.last_fn = (char*)__func__;
    auto a = VM_GetArg(vm);
    auto b = VM_GetArg(vm);
    a * b;
  }
  void VM_Div(VirtualMachine& vm) {
    vm.debug.last_fn = (char*)__func__;
    auto a = VM_GetArg(vm);
    auto b = VM_GetArg(vm);
    a / b;
  }
  
  void VM_Inc(VirtualMachine& vm) {
    vm.debug.last_fn = (char*)__func__;
    auto a = VM_GetArg(vm);
    ++a;
  }

  void VM_Dec(VirtualMachine& vm) {
    vm.debug.last_fn = (char*)__func__;
    auto a = VM_GetArg(vm);
    --a;
  }

  void VM_Xor(VirtualMachine& vm) {
    vm.debug.last_fn = (char*)__func__;
    auto a = VM_GetArg(vm);
    auto b = VM_GetArg(vm);
    a ^ b;
  }

  void VM_Or(VirtualMachine& vm) {
    vm.debug.last_fn = (char*)__func__;
    auto a = VM_GetArg(vm);
    auto b = VM_GetArg(vm);
    a | b;
  }

  void VM_Not(VirtualMachine& vm) {
    vm.debug.last_fn = (char*)__func__;
    auto a = VM_GetArg(vm);
    ~a;
  }
  
  void VM_And(VirtualMachine& vm) {
    vm.debug.last_fn = (char*)__func__;
    auto a = VM_GetArg(vm);
    auto b = VM_GetArg(vm);
    a & b;
  }

  void VM_LS(VirtualMachine& vm) {
    vm.debug.last_fn = (char*)__func__;
    auto a = VM_GetArg(vm);
    auto b = VM_GetArg(vm);
    a << b;
  }

  void VM_RS(VirtualMachine& vm) {
    vm.debug.last_fn = (char*)__func__;
    auto a = VM_GetArg(vm);
    auto b = VM_GetArg(vm);
    a >> b;
  }
  
  void VM_ManualJmp(VirtualMachine& vm, int offset) {
    MewUserAssert(MEW_IN_RANGE(vm.memory, vm.end, vm.begin+offset), 
      "out of memory");
    // vm.begin_stack.push(vm.begin);
    vm.begin += offset;
  }

  
  void VM_Jmp(VirtualMachine& vm) {
    vm.debug.last_fn = (char*)__func__;
    int offset;
    memcpy(&offset, vm.begin, sizeof(int)); //vm.begin += sizeof(int);
    MewUserAssert(MEW_IN_RANGE(vm.memory, vm.end, vm.begin+offset), 
      "out of memory");
    // vm.begin_stack.push(vm.begin);
    vm.begin += offset;
  }

  void VM_Ret(VirtualMachine& vm) {
    vm.debug.last_fn = (char*)__func__;
    if (vm.begin_stack.empty()) {
      vm.status = VM_Status_Ret; return;
    }
    byte* begin = vm.begin_stack.top();
    vm.begin = begin;
    vm.begin_stack.pop();
  }

  void VM_Test(VirtualMachine& vm) {
    vm.debug.last_fn = (char*)__func__;
    int x, y;
    vm.test = {0};
    VM_MathBase(vm, (uint*)&x, (uint*)&y);
    int result = memcmp(&x, &y, sizeof(x));
    if (result > 0) {
      vm.test.more = 1;
    } else if (result < 0) {
      vm.test.less = 1;
    } else {
      vm.test.equal = 1;
    }
  }

  void VM_JE(VirtualMachine& vm) {
    vm.debug.last_fn = (char*)__func__;
    int offset; 
    memcpy(&offset, vm.begin, sizeof(int));
    if (vm.test.equal) {
      VM_ManualJmp(vm, offset);
    } else {
      vm.begin += sizeof(int);
    }
  }
  void VM_JEL(VirtualMachine& vm) {
    vm.debug.last_fn = (char*)__func__;
    int offset; 
    memcpy(&offset, vm.begin, sizeof(int));
    if (vm.test.equal || vm.test.less) {
      VM_ManualJmp(vm, offset);
    } else {
      vm.begin += sizeof(int);
    }
  }
  void VM_JEM(VirtualMachine& vm) {
    vm.debug.last_fn = (char*)__func__;
    int offset; 
    memcpy(&offset, vm.begin, sizeof(int));
    if (vm.test.equal || vm.test.more) {
      VM_ManualJmp(vm, offset);
    } else {
      vm.begin += sizeof(int);
    }
  }
  void VM_JL(VirtualMachine& vm) {
    vm.debug.last_fn = (char*)__func__;
    int offset; 
    memcpy(&offset, vm.begin, sizeof(int));
    if (vm.test.less) {
      VM_ManualJmp(vm, offset);
    } else {
      vm.begin += sizeof(int);
    }
  }
  void VM_JM(VirtualMachine& vm) {
    vm.debug.last_fn = (char*)__func__;
    int offset; 
    memcpy(&offset, vm.begin, sizeof(int));
    if (vm.test.more) {
      VM_ManualJmp(vm, offset);
    } else {
      vm.begin += sizeof(int);
    }
  }
  void VM_JNE(VirtualMachine& vm) {
    vm.debug.last_fn = (char*)__func__;
    int offset; 
    memcpy(&offset, vm.begin, sizeof(int));
    if (!vm.test.equal) {
      VM_ManualJmp(vm, offset);
    } else {
      vm.begin += sizeof(int);
    }
  }

  void VM_Mov(VirtualMachine& vm) {
    vm.debug.last_fn = (char*)__func__;
    auto a = VM_GetArg(vm);
    auto b = VM_GetArg(vm);
    VM_ARG::mov(a, b);
  }

  void VM_Swap(VirtualMachine& vm) {
    vm.debug.last_fn = (char*)__func__;
    auto a = VM_GetArg(vm);
    auto b = VM_GetArg(vm);
    VM_ARG::swap(a, b);
  }

  void VM_MSet(VirtualMachine& vm) {
    vm.debug.last_fn = (char*)__func__;
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
    vm.debug.last_fn = (char*)__func__;
    wchar_t long_char;
    memcpy(&long_char, vm.begin, sizeof(wchar_t)); vm.begin+=sizeof(wchar_t);
    fputwc(long_char, vm.std_out);
  }
  
  void VM_Puti(VirtualMachine& vm) {
    vm.debug.last_fn = (char*)__func__;
    auto x = VM_GetArg(vm);
    int xi = x.getInt();
    char str[12] = {0};
    mew::_itoa10(xi, str);
    fputs(str, vm.std_out);
  }

  void VM_Puts(VirtualMachine& vm) {
    vm.debug.last_fn = (char*)__func__;
    uint offset;
    memcpy(&offset, vm.begin, sizeof(uint)); vm.begin+=sizeof(uint);
    uint fls;
    memcpy(&fls, vm.begin, sizeof(uint)); vm.begin+=sizeof(uint);
    byte* heap;
    if (fls == 0) {
      heap = vm.heap;
    } else {
      heap = vm.libs.at((size_t)(fls-1))->data;
    }
    MewUserAssert(vm.heap+offset < vm.end, "out of memory");
    byte* pointer = vm.heap+offset;
    char* begin = (char*)pointer;
    while (*(begin) != 0) {
      fputc(*(begin++), vm.std_out);
    }
  }

  void VM_Getch(VirtualMachine& vm) {
    vm.debug.last_fn = (char*)__func__;
    int& a = VM_GetArg(vm).getInt();
    a = mew::wait_char();
  }
  
  // 
  void VM_LM(VirtualMachine& vm) {
    vm.debug.last_fn = (char*)__func__;
    auto a = VM_GetArg(vm);
    auto b = VM_GetArg(vm);
    a.mov(b);
  }

  void VM_Open(VirtualMachine& vm) {
    vm.debug.last_fn = (char*)__func__;
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
    vm.debug.last_fn = (char*)__func__;
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
    vm.debug.last_fn = (char*)__func__;
    uint offset;
    memcpy(&offset, vm.begin, sizeof(uint)); vm.begin+=sizeof(uint);
    MewUserAssert(vm.heap+offset < vm.end, "out of memory");
    byte* pointer = vm.heap+offset;
    fputs((char*)pointer, vm.r_stream);
  }
  
  void VM_Read(VirtualMachine& vm) {
    vm.debug.last_fn = (char*)__func__;
    uint offset;
    memcpy(&offset, vm.begin, sizeof(uint)); vm.begin+=sizeof(uint);
    MewUserAssert(vm.heap+offset < vm.end, "out of memory");
    byte* pointer = vm.heap+offset;
    short int chunk_size;
    memcpy(&chunk_size, vm.begin, sizeof(chunk_size)); vm.begin+=sizeof(chunk_size);
    MewUserAssert(vm.heap+offset+(chunk_size*2) < vm.end, "out of memory (chunk too big)");
    fgets((char*)pointer, chunk_size, vm.r_stream);
  }

  void RunLine(VirtualMachine& vm) {
    byte head_byte = *vm.begin++;
    vm.debug.last_head_byte = head_byte;
    if (vm.flags.heap_lock_execute) { 
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
      case Instruction_RPOP: {
        VM_RPop(vm);
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
      case Instruction_SWAP: {
        VM_Swap(vm);
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
      case Instruction_GETCH: {
        VM_Getch(vm);
      } break;
      case Instruction_MOVRDI: {
        VM_MovRDI(vm);
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
      case Instruction_LM: {
        VM_LM(vm);
      } break;
      case Instruction_EXIT: {
        vm.status = VM_Status_Ret;
      } break;
      default: MewUserAssert(false, "unsupported instruction");
    }
  }

  int Run(VirtualMachine& vm, Code& code) {
    size_t code_size = __VM_ALIGN(code.capacity, VM_CODE_ALIGN);
    MewAssert(vm.capacity > code_size);
    byte* begin = vm.memory;
    byte* end   = begin+vm.capacity;
    byte* alloc_space = begin+code_size+1;
    vm.flags.use_debug = code.cme.flags.has_debug;
    vm.src = &code;
    vm.heap = alloc_space;
    vm.begin = begin;
    vm.end = end;
    vm.status = VM_Status_Execute;
    if (code.data != nullptr) {
      memcpy(vm.heap, code.data, code.data_size*sizeof(*code.data));
    }
    if (code.adata != nullptr) {

      memcpy(vm.heap+code.data_size, code.adata, code.adata_count*sizeof(*code.adata));
    }
    while (vm.begin < vm.end && vm.status != VM_Status_Ret) {
      ++vm.process_cycle; RunLine(vm);
    }
    vm.status = VM_Status_Panding;
    return vm.stack.top();
  }

  int Execute(VirtualMachine& vm, Code& code) {
    Alloc(vm, code);
    LoadMemory(vm, code);
    return Run(vm, code);
  }
  
  int Execute(Code& code) {
    VirtualMachine vm;
    Alloc(vm, code);
    LoadMemory(vm, code);
    return Run(vm, code);
  }

  int Execute(const char* path) {
    Code* code = Code_LoadFromFile(path);
    return Execute(*code);
  }

  class VM_Async {
  public:
    struct ExecuteInfo {
      enum struct Status {
        Execute, Errored, Done
      } status;
      int result;
    }; 
  private:
    mew::stack<VirtualMachine*> m_vms;
    mew::stack<ExecuteInfo> m_execs;
  public:
    VM_Async() { }

    void hardStop() {
      for (int i = 0; i < m_vms.size(); ++i) {
        delete m_vms[i];
      }
      m_vms.clear();
      m_execs.clear();
    }
    
    int Append(Code& code) {
      VirtualMachine* vm = new VirtualMachine();
      Alloc(*vm, code);
      LoadMemory(*vm, code);
      size_t code_size = __VM_ALIGN(code.capacity, VM_CODE_ALIGN);
      MewAssert(vm->capacity > code_size);
      vm->flags.use_debug = code.cme.flags.has_debug;
      vm->src = &code;
      vm->heap = vm->begin+code_size+1;
      vm->begin = vm->memory;
      vm->end = vm->begin+vm->capacity;
      vm->status = VM_Status_Execute;
      if (code.data != nullptr) {
        memcpy(vm->heap, code.data, code.data_size*sizeof(*code.data));
      }
      m_execs.push((ExecuteInfo){ExecuteInfo::Status::Execute, -1});
      return m_vms.push(vm);
    }

    bool is_ends(int id) {
      return m_vms[id]->status == VM_Status_Ret;
    }

    int get_status_code(int id) {
      return m_execs[id].result;
    }
        
    VirtualMachine* GetById(int id) {
      return m_vms[id];
    }

    void ExecuteStep() {
      for (int i = 0; i < m_vms.size(); ++i) {
        m_execs[i].result = this->Run(*m_vms[i], *m_vms[i]->src);
        if (m_vms[i]->status == VM_Status_Panding) {
          m_execs[i].status = ExecuteInfo::Status::Done;
        }
        if (m_vms[i]->status == VM_Status_Error) {
          m_execs[i].status = ExecuteInfo::Status::Errored;
        }
      }
    }
    
    int Run(VirtualMachine& vm, Code& code) {
      if (!(vm.begin < vm.end && vm.status != VM_Status_Ret)) {
        vm.status = VM_Status_Panding;
        return vm.stack.top();
      }
      ++vm.process_cycle;
      try {
        RunLine(vm);
      } catch(std::exception& e) {
        size_t cursor = vm.capacity - (size_t)(vm.end-vm.begin);
        for (int i = 0; i < code.cme.debug.size(); ++i) {
          if (code.cme.debug[i].cursor >= cursor) {
            fprintf(vm.std_out, "\n[DEBUG_ERROR] at (%i) in (%s)\n", code.cme.debug[i].line, vm.debug.last_fn);
            vm.status = VM_Status_Error;
            break;
          }
        }
      }
      return -1;
    }
  };

  class CodeBuilder {
  public:
    struct untyped_pair {
      byte* data;
      byte size;
    };
    static const size_t alloc_size = 8;
  private:
    size_t capacity, size, _data_size = 0;
    mew::stack<size_t> _adatas;
    byte* code = nullptr, *data = nullptr;
  public:
    CodeBuilder(): capacity(alloc_size), size(0), 
      code((byte*)realloc(NULL, alloc_size)), _data_size(0) { memset(code, 0, alloc_size); }

    size_t code_size() const noexcept {
      return size;
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
        
    void AddData(byte* row, size_t size) {
      size_t __new_size = _data_size+size;
      data = (byte*)realloc(data, __new_size);
      memcpy(data+_data_size, row, size);
      _data_size = __new_size;
    }

    CodeBuilder& operator+=(const char* text) {
      AddData((byte*)text, strlen(text));
      return *this;
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

    friend CodeBuilder& operator>>(CodeBuilder& cb, untyped_pair i) {
      cb.UpsizeIfNeeds(i.size);
      memmove(cb.code+i.size, cb.code, cb.size);
      memcpy(cb.code, &i.data, i.size);
      cb.size += i.size;
      return cb;
    }

    void push_adata(size_t size) {
      _adatas.push(size);
    }

    Code* operator*() {
      Code* c = new Code();
      c->capacity   = size;
      c->playground = (Instruction*)(code);
      c->data_size  = _data_size;
      c->data       = data;
      c->adata_count = _adatas.size();
      c->adata      = (byte*)_adatas.copy_data();
      return c;
    }
    Code operator*(int) {
      Code c;
      c.capacity    = size;
      c.playground  = (Instruction*)code;
      c.data_size   = _data_size;
      c.data        = data;
      c.adata_count = _adatas.size();
      c.adata      = (byte*)_adatas.copy_data();
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
#pragma pack(pop)
}
namespace Tests {
  bool test_Virtual() {
    try {
      using namespace Virtual;
      CodeBuilder builder;
      builder << Instruction_PUTS;
      builder << 0U;
      builder << Instruction_EXIT;
      builder += "hellow word";
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