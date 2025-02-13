#ifndef _NAN_PARSER_IMPL
#define _NAN_PARSER_IMPL

#include <vector>
#include "mewall.h"
#include "astlib.hpp"
#include "grammar.hpp"
#include "lexer.hpp"
#include "virtual.hpp"
#include "virtuallib.hpp"

#pragma pack(push, 1)

namespace Parser {
  using namespace Virtual;
  typedef Lexer::Lexer::Iterator Iterator;
  enum struct DataType {
    NONE,
    DB, // byte sequence
    DW, // word sequence
    DD, // dword sequence
    DQ, // qword sequence
    DT, // tbyte sequence
    DPB, // packed byte sequence
  };

  #define isKindOf(_it, Kind) ((*(_it)).kind == Kind)

  bool IfTrueNext(bool cond, Iterator& it) {
    if (cond) {
      it++;
    }
    return cond;
  }

  #define isKindOfN(_it, Kind) (IfTrueNext(isKindOf(_it, Kind), it))

  struct Parser {
    Lexer::Lexer* lexer;
    // AST* global_ast;
    // AST* ast;
    Lib::Builder builder;		
    const char* entry_label = "main";
    // std::stack<Token::Token> storage;
    // uint entry_pos;
  };

  typedef bool(*ParserFunc)(Parser&, Iterator&);

#pragma region UTILS

  bool NullOrMore(Parser& parser, Iterator& it, ParserFunc func) {
    while (func(parser, it)) { }
    return true;
  }

  bool NullOrMore_v(Parser& parser, Iterator& it, ParserFunc func) {
    bool has_touches = false;
    while (func(parser, it)) {
      has_touches = true;
    }
    return has_touches;
  }

  bool OneOrMore(Parser& parser, Iterator& it, ParserFunc func) {
    Iterator stored_it(it); 
    bool has_touches = false;
    while (func(parser, it)) {
      has_touches = true;
    }
    if (!has_touches) {
      it = stored_it;
    }
    return has_touches;
  }

  bool OneOrMore(Parser& parser, Iterator& it, Token::Kind kind) {
    Iterator stored_it(it); 
    bool has_touches = false;
    while (isKindOf(it++, kind)) {
      has_touches = true;
    }
    if (!has_touches) {
      it = stored_it;
    }
    return has_touches;
  }


#pragma endregion UTILS


  bool EntryMark(Parser& parser, Iterator& it) {
    Iterator stored_it(it);
    bool has_touches = isKindOfN(it, Token::Token_Entry);
    if (!has_touches) {
      it = stored_it;
      return false;
    }
    MewAssert(it->data != nullptr);
    parser.entry_label = it->data;
    return has_touches;
  }

  bool Label(Parser& parser, Iterator& it) {
    Iterator stored_it(it);
    bool has_touches = 
      isKindOfN(it, Token::Token_Text) &&
      isKindOfN(it, Token::Token_Colon);
    if (!has_touches) {
      it = stored_it;
      return false;
    }
    parser.builder.BeginFunction(stored_it->data);
    return has_touches;
  }

  bool Data(Parser& parser, Iterator& it) {
    // [text]"data" [text]"data_type" [text]"name" [text]"value"
    Iterator stored_it(it);
    bool has_touches = // [text]"data" 
      isKindOf(it, Token::Token_Text) && 
      mew::string::SameStr(it->data, "data");

    if (!has_touches) {
      it = stored_it;
      return false;
    }

    DataType data_type = DataType::NONE;

    const char* flag = (++it)->data; // data flag
    if (mew::string::SameStr(flag, "db")) {
      data_type = DataType::DB;
    } else
    if (mew::string::SameStr(flag, "dw")) {
      data_type = DataType::DW;
    } else
    if (mew::string::SameStr(flag, "dd")) {
      data_type = DataType::DD;
    } else
    if (mew::string::SameStr(flag, "dq")) {
      data_type = DataType::DQ;
    } else
    if (mew::string::SameStr(flag, "dt")) {
      data_type = DataType::DT;
    }
    switch (data_type) {
      case DataType::DB: {
        const char* name = (++it)->data; 
        if (isKindOfN(it, Token::Token_String)) {
          parser.builder.AddData(name, it->data);
        }
      } break;
      default: MewUserAssert(false, "unsupported data type");
    }
    return has_touches;
  }

  bool Line(Parser& parser, Iterator& it) {
    Iterator stored_it(it);
    Token::Kind tk = (it++)->kind;
    switch(tk) {
      case Token::Token_PUTS: {
        const char* name = it->data;
        parser.builder.Puts(name);
      } break;
      case Token::Token_PUTI: {
        int value = -*(int*)it->data;
        parser.builder.Puti(value);
      } break;
      case Token::Token_INC: {
        int value = -*(int*)it->data;
        parser.builder.Inc(-value);
      } break;
      case Token::Token_DEC: {
        int value = -*(int*)it->data;
        parser.builder.Dec(-value);
      } break;
      case Token::Token_TEST: {
        int value = -*(int*)it->data;
        parser.builder.Puti(value);
      } break;
      case Token::Token_JEL: {
        const char* value = it->data;
        uint address = parser.builder.GetAddressFunction(value);
        parser.builder << Instruction_JEL << address;
      } break;
      case Token::Token_JEM: {
        const char* value = it->data;
        uint address = parser.builder.GetAddressFunction(value);
        parser.builder << Instruction_JEM << address;
      } break;
      case Token::Token_JE: {
        const char* value = it->data;
        uint address = parser.builder.GetAddressFunction(value);
        parser.builder << Instruction_JE << address;
      } break;
      case Token::Token_JM: {
        const char* value = it->data;
        uint address = parser.builder.GetAddressFunction(value);
        parser.builder << Instruction_JM << address;
      } break;
      case Token::Token_JL: {
        const char* value = it->data;
        uint address = parser.builder.GetAddressFunction(value);
        parser.builder << Instruction_JL << address;
      } break;
      case Token::Token_JNE: {
        const char* value = it->data;
        uint address = parser.builder.GetAddressFunction(value);
        parser.builder << Instruction_JNE << address;
      } break;
      case Token::Token_PUSH: {
        Token::Kind tk2 = it->kind;
        switch(tk2) {
          case Token::Token_Number: {
            parser.builder.Push(Instruction_NUM, *(uint*)it->data);
          } break;
          default: MewUserAssert(false, "unsupported push type");
        }
      } break;
      case Token::Token_Ret: {
        parser.builder.Ret();
      } break;
      default: 
        it = stored_it;
        return false;
    }
    return true;
  }

  void Parse(Parser& parser, Lexer::Lexer& lexer) {
    parser.lexer = &lexer;
    Iterator it = lexer.tokens.begin();
    while (
      EntryMark(parser, it) || 
      Label(parser, it) || 
      Data(parser, it) || 
      Line(parser, it)
    ) { }
  }
  
}

#pragma pack(pop)

#endif