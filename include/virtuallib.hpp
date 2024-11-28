#ifndef _NAN_VIRTUAL_LIB_IMPL
#define _NAN_VIRTUAL_LIB_IMPL

#include <concepts>
#include "virtual.hpp"
#include <vector>
#include <map>
#include <string>

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
        ++(*this);
        return r;
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

    size_t size() const noexcept {
      return global_range.start - global_range.end;
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
        } i++;
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
      for (int i = global_range.start; i < global_range.end; i++) {
        if (rgx < global_range && Exist(rgx)) {
          uses.push_back(rgx);
          return uses.back();
        }
        ++rgx;
      }
      MewUserAssert(false, "cannot allocate");
    }
    
    ////////////////////////////////////////////////////////////
    Range Alloc_s(size_t size) {
      Range rgx{0, size};
      for (int i = global_range.start; i < global_range.end; i++) {
        if (rgx < global_range && Exist(rgx)) {
          uses.push_back(rgx);
          return uses.back();
        }
        ++rgx;
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
    void EndFunction() {
      ++((*this) << Instruction_RET);
    }

    ////////////////////////////////////////////////////////////
    void Jump(size_t line) {
      int real_idx = Cursor() - line;
      ++((*this) << Instruction_JMP << real_idx);
    }

    ////////////////////////////////////////////////////////////
    void CallExternFunction(size_t idx) {
      ++((*this) << Instruction_CALL << (uint)idx);
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
    uint Assign(std::string name, size_t size, bool clear_memory = false) {
      MewUserAssert(_vars.find(name) == _vars.end(), "already assign");
      auto range = _arena.Alloc_s(size);
      _vars.insert({name, range});
      if (clear_memory) {
        ++((*this) << Instruction_PUSH << (uint)range.start);
        ++((*this) << Instruction_PUSH << (uint)(range.end-range.start));
        ++((*this) << Instruction_PUSH << 0U);
        ++((*this) << Instruction_MSET);
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
    Builder& operator++(int) { 
      (*actual_builder)++;
      return *this;
    }
    
    ////////////////////////////////////////////////////////////
    Builder& operator++() {
      (*actual_builder)++;
      return *this; 
    }

    ////////////////////////////////////////////////////////////
    friend Builder& operator<<(Builder& b, CodeBuilder& gf) {
      *b.actual_builder << gf;
      return b;
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
    friend Builder& operator<<(Builder& b, CodeBuilder::untyped_pair gf) {
      *b.actual_builder << gf;
      return b;
    }
    
    ////////////////////////////////////////////////////////////
    Builder& operator+=(const wchar_t* text) {
      (*actual_builder) += text;
      return *this;
    }
    
    ////////////////////////////////////////////////////////////
    Builder& operator+=(const char* text) {
      size_t length = strlen(text)+1;
      wchar_t* buffer = new wchar_t[length];
      for (int i = 0; i < length; i++) {
        buffer[i] = text[i];
      }
      (*actual_builder) += buffer;
      return *this;
    }

    ////////////////////////////////////////////////////////////
    friend Builder& operator<<(Builder& b, generator_t gf) {
      gf(b);
      return b;
    }
  };
 
}

namespace Tests {
  bool test_Virtual_Lib_Construct() {
    try {

    } catch (std::exception e) {
      MewPrintError(e);
      return false;
    }
    return true;
  }
}

namespace Virtual::Math {
  using Builder = Virtual::Lib::Builder;
  enum struct OperatorToken: byte {
    None,
    Plus, Minus, Divide, Multiply,
    Con/*and*/,Dis/*or*/,Inv/*not*/, Xor
  };

  void _MathOp(Builder& b, OperatorToken op) {
    switch (op) {
      case OperatorToken::Plus:     b << Instruction_ADD; break;
      case OperatorToken::Minus:    b << Instruction_SUB; break;
      case OperatorToken::Multiply: b << Instruction_MUL; break;
      case OperatorToken::Divide:   b << Instruction_DIV; break;
      case OperatorToken::Con:      b << Instruction_AND; break;
      case OperatorToken::Dis:      b << Instruction_OR;  break;
      case OperatorToken::Xor:      b << Instruction_XOR; break;
      case OperatorToken::Inv:      b << Instruction_NOT; break;
    }
  }

  void base(Builder& b, OperatorToken op, int x) {
    ++(b << Instruction_PUSH << Instruction_NUM << x);
    _MathOp(b, op);
    ++(b << Instruction_NUM << Instruction_NUM);
  }

  void base(Builder& b, OperatorToken op, int x, int y) {
    ++(b << Instruction_PUSH << Instruction_NUM << x);
    ++(b << Instruction_PUSH << Instruction_NUM << y);
    _MathOp(b, op);
    ++(b << Instruction_NUM << Instruction_NUM);
  }

  void base(Builder& b, OperatorToken op, int* x, int* y) {
    if (y == nullptr) {
      base(b, op, *x);
    } else {
      base(b, op, *x, *y);
    }
  }

  void doMath(Builder& b, char* begin, char* end) {
    int* x = nullptr;
    int* y = nullptr;
    OperatorToken op;
    while (begin != end) {
      char c = *(begin++);
      if (c == ' ') {continue;}
      if (isdigit(c)) {
        char* num_beg = &c;
        char* num_end = &c;
        while (begin != end && isdigit(*(begin++))) {
          num_end++;
        }
        if (x != nullptr) {
          x = new int(0);
          *x = strtol(num_beg, &num_end, 10);
        } else {
          y = new int(0);
          *y = strtol(num_beg, &num_end, 10);
        }

        if (op != OperatorToken::None) { 
          base(b, op, x, y);
          x = nullptr;
          y = nullptr;
          op = OperatorToken::None;
        }
      } else {
        switch (c) {
          case '+': op = OperatorToken::Plus; break;
          case '-': op = OperatorToken::Minus; break;
          case '*': op = OperatorToken::Multiply; break;
          case '/': op = OperatorToken::Divide; break;
          case '&': op = OperatorToken::Con; break;
          case '|': op = OperatorToken::Dis; break;
          case '^': op = OperatorToken::Xor; break;
          case '~': op = OperatorToken::Inv; break;
        }
      }
    }
  }

  void doMath(Builder& b, const char* text) {
    size_t size = strlen(text);
    char* begin = (char*)text;
    char* end = begin+size;
  }

};

#endif