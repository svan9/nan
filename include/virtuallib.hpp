#ifndef _NAN_VIRTUAL_LIB_IMPL
#define _NAN_VIRTUAL_LIB_IMPL

#include <concepts>
#include "virtual.hpp"
#include <vector>
#include <map>
#include <string>
#include "mewstack.hpp"

#if 0
namespace Virtual::Visualizer {
  using namespace Virtual;

  const char* VType(byte t) {
    switch(t) {
      case Instruction_MEM:
        return "'MEM'";
      case Instruction_RMEM:
        return "'RMEM'";
      case Instruction_NUM: 
        return "'NUM'";
      default: return "undefined";
    }
  }

  void VLine(std::stringstream& str, byte* line) {
    byte head_byte = line[0];
    switch (head_byte) {
      case Instruction_NONE: break;
      case Instruction_PUSH: {
        int value; memcpy(&value, line+2, sizeof(int));
        str << "push " << VType(line[1]) << " " << value << "\n";
      } break;
      case Instruction_POP: {
        str << "pop\n";
      } break;
      case Instruction_ADD: {
        str << "add " << VType(line[1]) << " " << VType(line[2]) << "\n";
      } break;
      case Instruction_SUB: {
        str << "sub " << VType(line[1]) << " " << VType(line[2]) << "\n";
      } break;
      case Instruction_MUL: {
        str << "mul " << VType(line[1]) << " " << VType(line[2]) << "\n";
      } break;
      case Instruction_DIV: {
        str << "div " << VType(line[1]) << " " << VType(line[2]) << "\n";
      } break;
      case Instruction_XOR: {
        str << "xor " << VType(line[1]) << " " << VType(line[2]) << "\n";
      } break;
      case Instruction_OR: {
        str << "or " << VType(line[1]) << " " << VType(line[2]) << "\n";
      } break;
      case Instruction_NOT: {
        str << "not " << VType(line[1]) << "\n";
      } break;
      case Instruction_LS: {
        str << "ls " << VType(line[1]) << " " << VType(line[2]) << "\n";
      } break;
      case Instruction_RS: {
        str << "rs " << VType(line[1]) << " " << VType(line[2]) << "\n";
      } break;
      case Instruction_JMP: {
        int value; memcpy(&value, line+1, sizeof(int));
        str << "jmp " << (value/8) << "\n";
      } break;
      case Instruction_RET: {
        str << "ret\n";
      } break;
      case Instruction_INC: {
        str << "inc "<< VType(line[1]) <<"\n";
      } break;
      case Instruction_DEC: {
        str << "dec "<< VType(line[1]) <<"\n";
      } break;
      case Instruction_TEST: {
        str << "test\n";
      } break;
      case Instruction_JE: {
        int value; memcpy(&value, line+1, sizeof(int));
        str << "je " << (value/8) << "\n";
      } break;
      case Instruction_JEL: {
        int value; memcpy(&value, line+1, sizeof(int));
        str << "jel " << (value/8) << "\n";
      } break;
      case Instruction_JEM: {
        int value; memcpy(&value, line+1, sizeof(int));
        str << "jem " << (value/8) << "\n";
      } break;
      case Instruction_JL: {
        int value; memcpy(&value, line+1, sizeof(int));
        str << "jl " << (value/8) << "\n";
      } break;
      case Instruction_JM: {
        int value; memcpy(&value, line+1, sizeof(int));
        str << "jm " << (value/8) << "\n";
      } break;
      case Instruction_JNE: {
        int value; memcpy(&value, line+1, sizeof(int));
        str << "jne " << (value/8) << "\n";
      } break;
      case Instruction_MOV: {
        int value; memcpy(&value, line+2, sizeof(int));
        str << "mov " << VType(line[1]) << " " << value << "\n";
      } break;
      case Instruction_MSET: {
        str << "mset\n";
      } break;
      case Instruction_PUTC: {
        str << "putc\n";
      } break;
      case Instruction_PUTI: {
        str << "puti\n";
      } break;
      case Instruction_PUTS: {
        str << "puts\n";
      } break;
      case Instruction_CALL: {
        str << "call -not impl-\n";
      } break;
    }
  }

  std::string Visualize(Code* code) {
    std::stringstream builder;
    for (int i = 0; i < code->capacity; i += 8) {
      byte* line = (byte*)code->playground + i; 
      VLine(builder, line);
    }
    return builder.str();
  }

  void VisualizeToFile(Code* code, std::filesystem::path& path) {
    std::ofstream file(path, std::ios::out | std::ios::binary | std::ios::ate);
    MewAssert(file.is_open());
    file << Visualize(code);
    file.close();
  }

  void VisualizeToFile(Code* code, const char* path) {
    std::filesystem::path __path(path);
    if (!__path.is_absolute()) {
      __path = std::filesystem::absolute(__path.lexically_normal());
    }
    VisualizeToFile(code, __path);
  }

  void VisualizeToFile(Code* code) {
    VisualizeToFile(code, "./temp.s");
  }

};

#endif

namespace Virtual::Lib {
  class Builder;
  typedef void(*generator_t)(Builder&);

  class Arena {
  public:
    struct Range {
      size_t start = 0, end = 0;

      Range& operator++() {
        start+=1;
        end+=1;
        return *this;
      }

      Range operator++(int) {
        Range r(*this);
        (*this);
        return r;
      }

      constexpr uint size() const noexcept {
        return end - start;
      }
    };

    friend bool operator==(const Range& l, const Range& r) {
      return (l.start == r.start) && (l.end == r.end); 
    }

    friend bool operator<(const Range& l, const Range& r) {
      return l.start > r.start && l.end < r.end && ((l.end - r.start) < (l.end - r.start)); 
    }

    friend bool operator>(const Range& l, const Range& r) {
      return l.start < r.start && l.end > r.end && ((l.end - r.start) > (l.end - r.start)); 
    }

    friend Range operator+(const Range& l, int i) {
      return Range{(l.start + i), (l.end + i)}; 
    }

    friend Range& operator+=(Range& l, int i) {
      l.start += i;
      l.end += i;
      return l; 
    }

  private:
    Range global_range;
    std::vector<Range> uses;
  public:
    ////////////////////////////////////////////////////////////
    Arena() {}

    ////////////////////////////////////////////////////////////
    Arena(size_t size) {
      global_range = {0, size};
    }
  
    ////////////////////////////////////////////////////////////
    constexpr size_t size() const noexcept {
      return global_range.end - global_range.start;
    }

    ////////////////////////////////////////////////////////////
    void Free(size_t idx) {
      MewUserAssert(idx < uses.size(), "out of range");
      uses.erase(uses.begin()+idx);
    }

    ////////////////////////////////////////////////////////////
    void Free(const Range& range) {
      int i = 0;
      for (Range& r: uses) {
        if (r == range) { 
          Free(i);
          return;
        } i;
      }
    }
    
    ////////////////////////////////////////////////////////////
    bool Exist(const Range& range) {
      for (Range& r: uses) {
        if (r == range) { 
          return true;
        }
      }
      return false;
    }

    ////////////////////////////////////////////////////////////
    Range Alloc(size_t size) {
      Range rgx{0, size};
      for (int i = global_range.start; i < global_range.end; i) {
        if (rgx < global_range && Exist(rgx)) {
          uses.push_back(rgx);
          return uses.back();
        }
        rgx;
      }
      MewUserAssert(false, "cannot allocate");
    }
    
    ////////////////////////////////////////////////////////////
    Range Alloc_s(size_t size) {
      if (this->size() == 0) {
        global_range.end = size;
        return Range{0, size};
      }
      Range rgx{0, size};
      for (int i = global_range.start; i < global_range.end; i) {
        if (rgx < global_range && Exist(rgx)) {
          uses.push_back(rgx);
          return uses.back();
        }
        rgx;
      }
      rgx.start = global_range.end;
      global_range.end += size;
      rgx.end = global_range.end;
      return rgx;
    }
  };

  class Builder {
  private:
    CodeBuilder* actual_builder;
    std::map<std::string, size_t> _functions;
    std::map<std::string, VM_Processor> _externs_functions;
    std::map<std::string, Arena::Range> _vars;
    mew::stack<uint> _deferred_calc;
    mew::stack<int> _stored_points;
    Arena _arena;
  public:
    ////////////////////////////////////////////////////////////
    Builder(): actual_builder(new CodeBuilder()) {}

    ////////////////////////////////////////////////////////////
    void ExternFunction(std::string name, VM_Processor proc) {
      _externs_functions.insert({name, proc});
    }

    ////////////////////////////////////////////////////////////
    void BeginFunction(std::string name) {
      _functions.insert({name, Cursor()});
    }

    ////////////////////////////////////////////////////////////
    uint AddressFunction(std::string name) {
      MewUserAssert(_functions.find(name) != _functions.end(), "undefined");
      size_t s = _functions.at(name);
      return (uint)s;
    }

    ////////////////////////////////////////////////////////////
    void ClearFunction(std::string name) {
      MewUserAssert(_functions.find(name) != _functions.end(), "undefined");
      _functions.erase(name);
    }

    ////////////////////////////////////////////////////////////
    void EndFunction() {
      ((*this) << Instruction_RET);
    }

    ////////////////////////////////////////////////////////////
    void Jump(size_t line) {
      int real_idx = Cursor() - line;
      ((*this) << Instruction_JMP << real_idx);
    }

    ////////////////////////////////////////////////////////////
    void to_entry(size_t line) {
      int real_idx = Cursor() - line;
      CodeBuilder::untyped_pair pair;
      pair.size = 5;
      pair.data = new byte[5];
      pair.data[0] = Instruction_JMP;
      memcpy(pair.data+1, &real_idx, sizeof(real_idx));
      ((*this) >> pair);
    }

    ////////////////////////////////////////////////////////////
    void CallExternFunction(size_t idx) {
      ((*this) << Instruction_CALL << (uint)idx);
    }

    ////////////////////////////////////////////////////////////
    void CallFunction(std::string name) {
      auto _func = _functions.find(name);
      if (_func == _functions.end()) {
        auto _e_func = _externs_functions.find(name);
        MewUserAssert(_e_func != _externs_functions.end(), "invalid extern function");
        uint idx = std::distance(_externs_functions.begin(), _e_func);
        CallExternFunction(idx);
        return;
      }
      Jump(_func->second);
    }

    ////////////////////////////////////////////////////////////
    uint GetAddressFunction(std::string name) {
      auto _func = _functions.find(name);
      MewUserAssert(_func == _functions.end(), "undefined");
      return _func->second;
    }

    ////////////////////////////////////////////////////////////
    void Add(std::string name, uint num) {
      MewUserAssert(_vars.find(name) != _vars.end(), "undefined");
      auto range = _vars.at(name);
      ((*this) << Instruction_PUSH << Instruction_NUM << num);
      ((*this) << Instruction_PUSH << Instruction_RMEM << (uint)range.start);
      ((*this) << Instruction_ADD  << Instruction_MEM << Instruction_NUM);
    }

    ////////////////////////////////////////////////////////////
    void Puti(int offset) {
      ((*this) << Instruction_PUTI << (uint)offset);
    }

    ////////////////////////////////////////////////////////////
    void Puts(std::string name) {
      MewUserAssert(_vars.find(name) != _vars.end(), "undefined");
      auto range = _vars.at(name);
      ((*this) << Instruction_PUTS << (uint)range.start);
    }

    ////////////////////////////////////////////////////////////
    void MovRDI(int offset) {
      ((*this) << Instruction_PUSH << offset);
    }

    ////////////////////////////////////////////////////////////
    void Sub(std::string name, uint num) {
      MewUserAssert(_vars.find(name) != _vars.end(), "undefined");
      auto range = _vars.at(name);
      ((*this) << Instruction_PUSH << Instruction_RMEM << (uint)range.start);
      ((*this) << Instruction_PUSH << Instruction_NUM << num);
      ((*this) << Instruction_SUB  << Instruction_RMEM << Instruction_NUM);
    }

    ////////////////////////////////////////////////////////////
    uint Assign(std::string name, size_t size, bool clear_memory = false, const int value = 0) {
      MewUserAssert(_vars.find(name) == _vars.end(), "already assign");
      auto range = _arena.Alloc_s(size);
      _vars.insert({name, range});
      if (clear_memory) {
        Mset(range.start, range.size(), value);
      }
      return range.start;
    }

    ////////////////////////////////////////////////////////////
    void Destroy(std::string name) {
      auto _v = _vars.find(name);
      MewUserAssert(_v != _vars.end(), "cannot destroy (undefined)");
      _arena.Free(_v->second);
      _vars.erase(name);
    }

    ////////////////////////////////////////////////////////////
    void BeginDefer() {
      _deferred_calc.push(Cursor()-sizeof(uint));
    }

    ////////////////////////////////////////////////////////////
    inline void __EndDefer(byte* row, uint cursor) {
      int offset = Cursor() - cursor - sizeof(uint);
      if (offset < 0) {
        offset += sizeof(uint)/2;
      }
      memcpy(row, &offset, sizeof(offset));
    }
    ////////////////////////////////////////////////////////////
    void EndDefer() {
      MewUserAssert(!_deferred_calc.empty(), "undefined");
      uint cursor = _deferred_calc.pop();
      byte* row = actual_builder->at(cursor);
      __EndDefer(row, cursor);
    }

    ////////////////////////////////////////////////////////////
    void EndDefer(int idx, uint s_cursor) {
      MewUserAssert(_deferred_calc.has(idx), "undefined");
      uint cursor = _deferred_calc.at(idx);
      byte* row = actual_builder->at(cursor);
      _deferred_calc.erase(idx);
      int offset = s_cursor - cursor - sizeof(uint);
      if (offset < 0) {
        offset += sizeof(uint)/2;
      }
      memcpy(row, &offset, sizeof(offset));
    }
    ////////////////////////////////////////////////////////////
    void EndDefer(int idx) {
      MewUserAssert(_deferred_calc.has(idx), "undefined");
      uint cursor = _deferred_calc.at(idx);
      byte* row = actual_builder->at(cursor);
      _deferred_calc.erase(idx);
      __EndDefer(row, cursor);
    }

    ////////////////////////////////////////////////////////////
    void BeginBackJump() {
      _stored_points.push(Cursor());
    }

    ////////////////////////////////////////////////////////////
    void EndBackJump() {
      MewAssert(!_stored_points.empty());
      uint dest = _stored_points.top();
      _stored_points.pop();
      int offset = dest - (uint)Cursor() - (sizeof(uint)+1);
      ((*this) << Instruction_JMP << offset);
    }

    ////////////////////////////////////////////////////////////
    void BeginJump() {
      ((*this) << Instruction_JMP << 0U);
      BeginDefer();
    }

    ////////////////////////////////////////////////////////////
    void EndJump(int idx) {
      EndDefer(idx);
    }

    ////////////////////////////////////////////////////////////
    void EndJump() {
      EndDefer();
    }

    ////////////////////////////////////////////////////////////
    void Test(std::string name, int value) {
      MewUserAssert(_vars.find(name) != _vars.end(), "undefined");
      auto range = _vars.at(name);
      Push(Instruction_NUM, value); /* y */
      Push(Instruction_MEM, (uint)range.start); /* x */
      Test(Instruction_MEM, Instruction_NUM);
    }

    ////////////////////////////////////////////////////////////
    void BeginForI(std::string i_name, int i_init_val, int count_of_iter) {
      /* 'int i = 0' */
      /* reserve variable 'i' */
      Assign(i_name, sizeof(int), true, i_init_val);
      /* mark back jump dest */
      BeginBackJump();
      /* 'i < x' */
      Test(i_name, count_of_iter-1);
      ((*this) << Instruction_JM << 0U);
      BeginDefer();
      /* 'i' */
      Inc(i_name);
    }

    ////////////////////////////////////////////////////////////
    void EndForI(std::string i_name) {
      /* repeat 'for' */
      EndBackJump();
      /* confirm last defer */
      EndDefer();
      /* free 'i' */
      Destroy(i_name);
    }

    ////////////////////////////////////////////////////////////
    void Inc(int offset) {
      ((*this) << Instruction_INC  << offset);
    }
    ////////////////////////////////////////////////////////////
    void Dec(int offset) {
      ((*this) << Instruction_DEC  << offset);
    }
    
    ////////////////////////////////////////////////////////////
    void Dec(std::string name) {
      MewUserAssert(_vars.find(name) != _vars.end(), "undefined");
      auto range = _vars.at(name);
      ((*this) << Instruction_PUSH << Instruction_RMEM << (uint)range.start);
      ((*this) << Instruction_DEC  << Instruction_MEM);
    }

    ////////////////////////////////////////////////////////////
    void Pop() {
      ((*this) << Instruction_POP);
    }

    ////////////////////////////////////////////////////////////
    void Pop(int count) {
      for (int i = 0; i < count; i) {
        ((*this) << Instruction_POP);
      }
    }

    ////////////////////////////////////////////////////////////
    void Test(byte t1, byte t2) {
      ((*this) << Instruction_TEST << t1 << t2);
    }

    ////////////////////////////////////////////////////////////
    void Push(std::string varname) {
      MewUserAssert(_vars.find(varname) != _vars.end(), "undefined");
      auto range = _vars.at(varname);
      ((*this) << Instruction_PUSH << Instruction_RMEM << (uint)range.start);
    }

    ////////////////////////////////////////////////////////////
    void Push(byte type, int value) {
      ((*this) << Instruction_PUSH << type << value);
    }

    ////////////////////////////////////////////////////////////
    void Push(byte type, uint value) {
      ((*this) << Instruction_PUSH << type << value);
    }

    void Mset(uint size, uint start, uint value) {
      ((*this) << Instruction_MSET << size << start << value);
    }

    void Mset() {
      ((*this) << Instruction_MSET);
    }

    void Ret() {
      ((*this) << Instruction_RET);
    }

    void Exit() {
      ((*this) << Instruction_EXIT);
    }

#pragma region conditional jumps

    ////////////////////////////////////////////////////////////
    void JumpIfLess(std::string name) {
      uint address = GetAddressFunction(name);
      int real_idx = Cursor() - address;
      ((*this) << Instruction_JL << real_idx);
    }

    ////////////////////////////////////////////////////////////
    void JumpIfMore(std::string name) {
      uint address = GetAddressFunction(name);
      int real_idx = Cursor() - address;
      ((*this) << Instruction_JM << real_idx);
    }

    ////////////////////////////////////////////////////////////
    void JumpIfEqual(std::string name) {
      uint address = GetAddressFunction(name);
      int real_idx = Cursor() - address;
      ((*this) << Instruction_JE << real_idx);
    }

    ////////////////////////////////////////////////////////////
    void JumpIfEqualLess(std::string name) {
      uint address = GetAddressFunction(name);
      int real_idx = Cursor() - address;
      ((*this) << Instruction_JEL << real_idx);
    }

    ////////////////////////////////////////////////////////////
    void JumpIfEqualMore(std::string name) {
      uint address = GetAddressFunction(name);
      int real_idx = Cursor() - address;
      ((*this) << Instruction_JEM << real_idx);
    }

    ////////////////////////////////////////////////////////////
    void JumpIfNotEqual(std::string name) {
      uint address = GetAddressFunction(name);
      int real_idx = Cursor() - address;
      ((*this) << Instruction_JNE << real_idx);
    }

#pragma endregion

    ////////////////////////////////////////////////////////////
    const CodeBuilder& ActualBulder() noexcept {
      return *actual_builder;
    }

    ////////////////////////////////////////////////////////////
    const Code& Release() {
      return **(*actual_builder);
    }

    ////////////////////////////////////////////////////////////
    const size_t Cursor() const noexcept {
      return (*actual_builder).code_size();
    }

    ////////////////////////////////////////////////////////////
    const size_t DataCursor() const noexcept {
      return (*actual_builder).data_size();
    }

    ////////////////////////////////////////////////////////////
    const Code& operator*(int) { return Release(); }
    
    ////////////////////////////////////////////////////////////
    const Code& operator*() { return Release(); }

    ////////////////////////////////////////////////////////////
    friend Builder& operator<<(Builder& b, CodeBuilder& gf) {
      *b.actual_builder << gf;
      return b;
    }

    ////////////////////////////////////////////////////////////
    Builder& concat(Builder& gf) {
      *actual_builder << *gf.actual_builder;
      return *this;
    }

    ////////////////////////////////////////////////////////////
    friend Builder& operator<<(Builder& b, uint gf) {
      *b.actual_builder << gf;
      return b;
    }

    ////////////////////////////////////////////////////////////
    friend Builder& operator<<(Builder& b, int gf) {
      *b.actual_builder << gf;
      return b;
    }

    ////////////////////////////////////////////////////////////
    friend Builder& operator<<(Builder& b, byte gf) {
      *b.actual_builder << gf;
      return b;
    }

    ////////////////////////////////////////////////////////////
    friend Builder& operator<<(Builder& b, Instruction gf) {
      *b.actual_builder << gf;
      return b;
    }

    ////////////////////////////////////////////////////////////
    friend Builder& operator>>(Builder& b, CodeBuilder::untyped_pair gf) {
      *b.actual_builder >> gf;
      return b;
    }

    ////////////////////////////////////////////////////////////
    std::string GetIdConst(const wchar_t* text) const {
      return std::string((char*)mew::get_cstr_hash(text));
    }

    ////////////////////////////////////////////////////////////
    std::string GetIdConst(const char* text) const {
      return std::string((char*)mew::get_cstr_hash(text));
    }
    
    ////////////////////////////////////////////////////////////
    Builder& operator+=(const wchar_t* text) {
      size_t __size = wcslen(text);
      Assign(GetIdConst(text), __size);
      (*actual_builder) += text;
      return *this;
    }
    
    ////////////////////////////////////////////////////////////
    Builder& operator+=(const char* text) {
      size_t length = strlen(text)+1;
      wchar_t* buffer = new wchar_t[length];
      for (int i = 0; i < length; i) {
        buffer[i] = text[i];
      }
      Assign(GetIdConst(buffer), length);
      (*actual_builder) += buffer;
      return *this;
    }

    ////////////////////////////////////////////////////////////
    Builder& AddData(std::string name, const char* text) {
      size_t length = strlen(text)+1;
      wchar_t* buffer = new wchar_t[length];
      for (int i = 0; i < length; i) {
        buffer[i] = text[i];
      }
      Assign(name, length);
      (*actual_builder) += buffer;
      return *this;
    }

    ////////////////////////////////////////////////////////////
    friend Builder& operator<<(Builder& b, generator_t gf) {
      gf(b);
      return b;
    }

    ////////////////////////////////////////////////////////////
    Code* Build() {
      MewUserAssert(_deferred_calc.empty(), "close defered calcs");
      Exit();
      actual_builder->force_data(_arena.size());
      Code* c = *(*actual_builder);
      return c;
    }
  
    ////////////////////////////////////////////////////////////
    void Run() {
      Code* c = Build();
      // Virtual::Visualizer::VisualizeToFile(c);
      Virtual::Execute(*c);
    }

    ////////////////////////////////////////////////////////////
    void Save(const char* path) {
      Code* c = Build();
      Code_SaveFromFile(*c, path);
    }

    ////////////////////////////////////////////////////////////
    Code* Load(const char* path) {
      return Code_LoadFromFile(path);
    }
  };
}

namespace Tests {
  bool test_Virtual_Lib() {
    try {
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
      b.Save("./vlib-for-10.nb");
      b.Run();
    } catch (std::exception e) {
      MewPrintError(e);
      return false;
    }
    return true;
  }
}
#endif