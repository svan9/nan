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
    
    const size_t Cursor() const noexcept {
      return (*actual_builder).code_size();
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
      /* generate before writing */
      size_t actual_pos = -1;
      
      // /* @brief
      // 	@param b builder
      // 	@param arg_size argument size, -1 value is infinity ak (...) | No limit, max +255
      //  */
      bool PushArgs(Builder& b, int arg_size) {
        actual_pos = b.Cursor();
        if (arg_size == -1) {
          MewNoImpl();
        }
        if (arg_size != arg_count) {
          return false;
        }
      }

      void GenerateBegin(Builder& b) {
        actual_pos = b.Cursor();
      }

      void Call(Builder& b) {
        if (actual_pos == -1) {
          ++(b << Instruction_JMP << (int)(actual_pos - b.Cursor()));
        }
      }

      void generate(Builder& b) {
        b << inner;
        (b << Instruction_RET)++;
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

#endif