#ifndef _NAN_VIRTUAL_LIB_IMPL
#define _NAN_VIRTUAL_LIB_IMPL

#include <concepts>
#include "virtual.hpp"

namespace Virtual::Lib {
  class Builder;
  typedef void(*generator_t)(Builder&);

  class Builder {
  private:
    CodeBuilder* actual_builder;
  public:
    ////////////////////////////////////////////////////////////
    Builder(): actual_builder(new CodeBuilder()) {}

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

  namespace Generators {
    struct Arg {
      byte type_size;
      const char* name;
    };
    
    struct Function {
      Arg* args;
      byte arg_count;
      CodeBuilder inner;
      bool has_return = false;
      /* generate before writing */
      size_t actual_pos = -1;
      
      void PushArg(Builder& b, const Arg& arg_info, byte* data) {
        MewUserAssert(arg_info.type_size != 0, "cannot be 0");
        MewUserAssert(arg_info.type_size <= 4, "not supported big struct data, use pointer");
        b << CodeBuilder::untyped_pair{data, arg_info.type_size};
      }

      bool PushArgs(Builder& b, byte arg_size, Arg* arg_info, byte* data) {
        if (arg_size != arg_count) {
          return false;
        }
        for (int i = 0; i < arg_size; i++) {
          const Arg& arg = arg_info[i];
          PushArg(b, arg, data);
          data += arg.type_size;
        }
        return true;
      }

      void Call(Builder& b) {        
        MewUserAssert(actual_pos != -1, "function is not generate");
        ++(b << Instruction_JMP << (int)(actual_pos - b.Cursor()));
      }

      void generate(Builder& b) {
        actual_pos = b.Cursor();
        b << inner;
        ++(b << Instruction_RET);
      }
    };
  }
  
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