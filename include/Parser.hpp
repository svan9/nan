#ifndef _NAN_PARSER_IMPL
#define _NAN_PARSER_IMPL

#include <vector>
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
    AST* ast;
    Lib::Builder builder;		
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
      while (isKindOfN(it, Token::Kind::Token_Underscore)) { }
      //$ todo
      // if (isKindOfN(it, Token::Kind::Token_Dot)) {
      //   is_float = true;
      //   i_float = i_num;
      // }
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
    parser.builder += (*it).data;
    uint address = parser.builder.DataCursor();
    ++(parser.builder << Instruction_PUSH << Instruction_NUM << address);
    return true;
  }
  
  bool Expression(Parser& parser, Iterator& it) {
    Iterator stored_it(it); 
    bool has_touches = 
      Block(parser, it) ||
      String(parser, it)
      ;
      // isKindOfN(it, Token::Kind::Token_String) ||
      // isKindOfN(it, Token::Kind::Token_Number);
      // NullOrMore(parser, it, Line) &&
      // isKindOf(it++, Token::Kind::Token_FigureClose);
  }

  bool ExpressionEOL(Parser& parser, Iterator& it) {
    Iterator stored_it(it); 
    bool has_touches = Expression(parser, it) 
      && (isKindOf(it++, Token::Kind::Token_Semicolon));
    if (!has_touches) {
      it = stored_it;
      return false;
    }
    
    return true;
  }

  bool Statement(Parser& parser, Iterator& it) {

  }
  
  bool Line(Parser& parser, Iterator& it) {
    while (ExpressionEOL(parser, it) | Statement(parser, it)) { }
  }

  void Parse(Parser& parser, Lexer::Lexer& lexer) {
    parser.lexer = &lexer;
    Iterator it = lexer.tokens.begin();
    while (Line(parser, it)) {  }
  }
  
}

#endif