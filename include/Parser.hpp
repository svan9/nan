#ifndef _NAN_PARSER_IMPL
#define _NAN_PARSER_IMPL

#include <vector>
#include "mewall.h"
#include "config.h"
#include "astlib.hpp"
#include "grammar.hpp"
#include "lexer.hpp"
#include "virtual.hpp"
#include "virtuallib.hpp"

namespace Parser {
  using namespace Virtual;
  typedef Lexer::Lexer::Iterator Iterator;

  #define isKindOf(_it, Kind) ((*(_it)).kind == Kind)
  #define isKindOfDigit(_it) (\
    isKindOf(_it, Token::Kind::Token_Zero) || \
    isKindOf(_it, Token::Kind::Token_One) || \
    isKindOf(_it, Token::Kind::Token_Two) || \
    isKindOf(_it, Token::Kind::Token_Three) || \
    isKindOf(_it, Token::Kind::Token_Four) || \
    isKindOf(_it, Token::Kind::Token_Five) || \
    isKindOf(_it, Token::Kind::Token_Six) || \
    isKindOf(_it, Token::Kind::Token_Seven) || \
    isKindOf(_it, Token::Kind::Token_Eight) || \
    isKindOf(_it, Token::Kind::Token_Nine))

  bool IfTrueNext(bool cond, Iterator& it) {
    if (cond) {
      it = it++;
    }
    return cond;
  }

  #define isKindOfN(_it, Kind) (IfTrueNext(isKindOf(_it, Kind), it))

  struct Parser {
    Lexer::Lexer* lexer;
    AST* global_ast;
    AST* ast;
    Lib::Builder builder;		
    std::stack<Token::Token> storage;
  };

  typedef bool(*ParserFunc)(Parser&, Iterator&);

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

  bool Line(Parser& parser, Iterator& it);
  bool Expression(Parser& parser, Iterator& it);
  
  bool Block(Parser& parser, Iterator& it) {
    Iterator stored_it(it); 
    bool has_touches = 
      isKindOf(it++, Token::Kind::Token_FigureOpen) &&
      NullOrMore(parser, it, Line) &&
      isKindOf(it++, Token::Kind::Token_FigureClose);
    if (!has_touches) {
      it = stored_it;
      return false;
    }
    return true;
  }

  bool Variable(Parser& parser, Iterator& it) {
    Iterator stored_it(it); 
    bool has_touches = isKindOf(it, Token::Kind::Token_Text);
    if (!has_touches) {
      it = stored_it;
      return false;
    }
    const char* name = (*it).data;
    if (parser.ast->has_option(name)) {
      int idx = parser.ast->get_option_v<int>(name);
      AST* opt = parser.ast->at(idx);
      if (opt->has_option("type", "typename")) {
        it = stored_it;
        return false;
      }
      else if (opt->has_option("type", "variable")) {
        if (opt->has_option("const")) {
          if (opt->has_option("const_type", "number")) {
            int value = opt->get_option_v<int>("const_value");
            ++(parser.builder << Instruction_PUSH << Instruction_NUM << value);
          }
          else if (opt->has_option("const_type", "string")) {
            parser.builder += opt->get_option("const_value").data();
            uint address = parser.builder.DataCursor();
            ++(parser.builder << Instruction_PUSH << Instruction_NUM << address);
          }
        }
      }
    }
    return true;
  }
  
  bool Number(Parser& parser, Iterator& it) {
    Iterator stored_it(it);
    bool has_negative = isKindOfN(it, Token::Kind::Token_Minus);
    bool is_float = false;
    int i_num = -1;
    float i_float = -1;
    double i_double = -1;
    while (isKindOfDigit(it)) {
      byte c;
      switch((*it++).kind) {
        case Token::Kind::Token_One: 		c = 1; break;
        case Token::Kind::Token_Two: 		c = 2; break;
        case Token::Kind::Token_Three: 	c = 3; break;
        case Token::Kind::Token_Four: 	c = 4; break;
        case Token::Kind::Token_Five: 	c = 5; break;
        case Token::Kind::Token_Six:	 	c = 6; break;
        case Token::Kind::Token_Seven: 	c = 7; break;
        case Token::Kind::Token_Eight: 	c = 8; break;
        case Token::Kind::Token_Nine: 	c = 9; break;
        case Token::Kind::Token_Zero: 	c = 0; break;
      }
      i_num = (i_num*10) + c;
      /* skip underscore | number support kind of 1_000_000 */
      while (isKindOfN(it, Token::Kind::Token_Underscore)) { }
    }
    if (i_num == -1) {
      it = stored_it;
      return false;
    }
    if (has_negative) {
      i_num = -i_num;
    }
    ++(parser.builder << Instruction_PUSH << Instruction_NUM << i_num);
    return true;
  }

  bool String(Parser& parser, Iterator& it) {
    Iterator stored_it(it); 
    bool has_touches = isKindOf(it, Token::Kind::Token_String);
    if (!has_touches) {
      it = stored_it;
      return false;
    }
    uint address = parser.builder.DataCursor();
    parser.builder += (*it++).data;
    ++(parser.builder << Instruction_PUSH << Instruction_NUM << address);
    return true;
  }

  bool TypeExt(Parser& parser, Iterator& it) {
    bool has_touches = isKindOf(it, Token::Kind::Token_Star) | isKindOf(it, Token::Kind::Token_Ampersand);
    if (has_touches) {
      parser.storage.push(*it++);
    }
    return has_touches;
  }
  
  bool ArrayBase(Parser& parser, Iterator& it) {
    bool has_touches = 
      Expression(parser, it);
    while (isKindOfN(it, Token::Kind::Token_Comma) && Expression(parser, it)) {}
    return has_touches;
  }

  bool WordListBase(Parser& parser, Iterator& it) {
    bool has_touches = 
      Expression(parser, it);
    while (isKindOfN(it, Token::Kind::Token_Comma) && 
      isKindOf(it, Token::Kind::Token_Text)) {
        auto tk = *it++;
        parser.storage.push(tk);
      }
    return has_touches;
  }

  bool TemplateBase(Parser& parser, Iterator& it) {
    Iterator stored_it(it); 
    bool has_touches = 
      isKindOfN(it, Token::Kind::Token_ArrowOpen) &&
      MEW_ONE_OR_NONE(WordListBase(parser, it)) &&
      isKindOfN(it, Token::Kind::Token_ArrowClose);
    if (!has_touches) {
      it = stored_it;
      return false;
    }
    AST nast;
    nast.add_option("type", "template_base");
    int size = parser.storage.size();
    nast.add_option_v<int>("count", size);
    for (int i = 0; i < size; i++) {
      nast.add_option_v<int>(i, parser.storage.top().data);
      parser.storage.pop();
    }
    parser.ast->append(nast);
    return true;
  }

  bool TemplateBaseHelper(Parser& parser, Iterator& it) {
    MewAssert(parser.global_ast != nullptr);
    parser.global_ast->add_option("generic");
    bool has_error = parser.ast->is_empty();
    if (has_error) { return false; }
    auto templ_ = parser.ast->top(); //! can errored
    has_error &= !templ_->has_option("type", "template_base");
    if (has_error) { return false; }
    parser.global_ast->append(templ_);
    parser.ast->pop();
    return true;
  }
  
  bool Typename(Parser& parser, Iterator& it) {
    Iterator stored_it(it); 
    AST nast;
    // 'const'?
    bool has_touches = isKindOfN(it, Token::Kind::Token_Const);
    if (has_touches) {
      nast.add_option("const");
    }
    // WORD
    has_touches &= isKindOf(it, Token::Kind::Token_Text);
    if (!has_touches) {
      it = stored_it;
      return false;
    }
    auto tk = *it++;
    nast.add_option("name", tk.data);
    // TYPEMOD?
    has_touches &= OneOrMore(parser, it, TypeExt);
    if (has_touches) {
      size_t size = parser.storage.size();
      char* buffer = new char[size];
      for (int i = 0; i < size; i++) {
        buffer[i] = parser.storage.top().kind; parser.storage.pop();
      }
      nast.add_option("type_ext", buffer);
    }
    // template_base?
    has_touches &= TemplateBase(parser, it);
    if (has_touches) {
      parser.global_ast = &nast;
      if (TemplateBaseHelper(parser, it)) {
        nast.add_option("generic");
      }
      parser.global_ast = nullptr;
    }
    parser.ast->append(nast);
    return true;
  }

  bool Asignment(Parser& parser, Iterator& it) {
    Iterator stored_it(it); 
    AST nast;
    // 'let'?
    bool has_touches = isKindOfN(it, Token::Kind::Token_Const);
    if (has_touches) {
      nast.add_option("let");
    }
    // typename | +stack
    has_touches &= Typename(parser, it) && !parser.ast->is_empty();
    if (!has_touches) {
      it = stored_it;
      return false;
    }
    auto _typename = parser.ast->top();
    int idx = parser.ast->get_option_v<int>(_typename->get_option("name"));
    auto typeref = parser.ast->at(idx);
    int typesize = typeref->get_option_v<int>("size");

    if (_typename->has_option("type_ext")) {
      auto exts =_typename->get_option("type_ext");
      char last = exts.back();
      if (last == '*') {
        typesize = sizeof(uint);
      }
    }
    nast.add_option_v<int>("typesize", typesize);
    nast.append(_typename);
    parser.ast->pop();
    // WORD (name)
    has_touches &= isKindOf(it, Token::Kind::Token_Text);
    if (!has_touches) {
      it = stored_it;
      return false;
    }
    auto tk = *it++;
    nast.add_option("name", tk.data);
    // TYPEMOD?
    has_touches &= OneOrMore(parser, it, TypeExt);
    if (has_touches) {
      size_t size = parser.storage.size();
      char* buffer = new char[size];
      for (int i = 0; i < size; i++) {
        buffer[i] = parser.storage.top().kind; parser.storage.pop();
      }
      nast.add_option("type_ext", buffer);
    }
    // template_base?
    has_touches &= TemplateBase(parser, it);
    if (has_touches) {
      nast.add_option("generic");
      parser.global_ast = &nast;
      if (TemplateBaseHelper(parser, it)) {

      }
    }
    return true;
  }

  bool Expression(Parser& parser, Iterator& it) {
    bool has_touches = 
      Block(parser, it)       ||
      String(parser, it)      ||
      Number(parser, it)      ||
      Variable(parser, it)    ||
      Asignment(parser, it)   ||
      false;
    return has_touches;
  }

  bool ExpressionEOL(Parser& parser, Iterator& it) {
    bool has_touches = Expression(parser, it) 
      && (isKindOf(++it, Token::Kind::Token_Semicolon));
    return has_touches;
  }

  bool NamedFunction(Parser& parser, Iterator& it) {
    Iterator stored_it(it); 
    bool has_touches = isKindOf(it, Token::Kind::Token_String);
    if (!has_touches) {
      it = stored_it;
      return false;
    }
    return true;
  }

  bool AnonimusFunction(Parser& parser, Iterator& it) {
    Iterator stored_it(it); 
    bool has_touches = isKindOf(it, Token::Kind::Token_String);
    if (!has_touches) {
      it = stored_it;
      return false;
    }
    return true;
  }

  bool Function(Parser& parser, Iterator& it) {
    bool has_touches = NamedFunction(parser, it) || AnonimusFunction(parser, it);
    return has_touches;
  }

  bool Statement(Parser& parser, Iterator& it) {
  }
  
  bool Line(Parser& parser, Iterator& it) {
    bool has_touches = false;
    while (ExpressionEOL(parser, it) | Statement(parser, it) | Function(parser, it)) { has_touches = true; }
    return has_touches;
  }

  void Parse(Parser& parser, Lexer::Lexer& lexer) {
    parser.lexer = &lexer;
    Iterator it = lexer.tokens.begin();
    while (Line(parser, it)) {  }
  }
  
}

#endif