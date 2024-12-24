#ifndef _NAN_LEXER_IMPL
#define _NAN_LEXER_IMPL

#include <vector>
#include "grammar.hpp"
#include "mewall.h"
#include <string>
#include <iostream>

namespace Lexer {
  struct Lexer {
    const char* source;
    mew::string::StringIterator sit;
    std::vector<Token::Token> tokens;
    typedef std::vector<Token::Token>::iterator Iterator;
  };

  void PrintLexer(const Lexer& lex) {
    std::cout << "{ ";
    for (auto& tk: lex.tokens) {
      std::cout << "[kind: "<< tk.kind << ", data: " << ((tk.data == nullptr)? "-" : tk.data) << "] "; 
    }
    std::cout << "}\n";
  }

#pragma region TOKENIZE

  #define cmp_string(f, a, b) ((strlen(a) == b) && (1 == mew::strcmp(f, a, b)))

  bool CheckKeyWords(Lexer& lexer) {
    size_t before_space =
      mew::string::CountRightBefore(lexer.sit.begin, " \n\r\v\b\t");
    if (cmp_string(lexer.sit.begin, "entry", before_space)) {
      lexer.tokens.push_back({Token::Token_Entry});
    } else 
    if (cmp_string(lexer.sit.begin, "use", before_space)) {
      lexer.tokens.push_back({Token::Token_Use});
    } else 
    if (cmp_string(lexer.sit.begin, "ret", before_space)) {
      lexer.tokens.push_back({Token::Token_Ret});
    } else 
    if (cmp_string(lexer.sit.begin, "class", before_space)) {
      lexer.tokens.push_back({Token::Token_Class});
    } else 
    if (cmp_string(lexer.sit.begin, "for", before_space)) {
      lexer.tokens.push_back({Token::Token_For});
    } else 
    if (cmp_string(lexer.sit.begin, "while", before_space)) {
      lexer.tokens.push_back({Token::Token_While});
    } else 
    if (cmp_string(lexer.sit.begin, "interface", before_space)) {
      lexer.tokens.push_back({Token::Token_Interface});
    } else 
    if (cmp_string(lexer.sit.begin, "struct", before_space)) {
      lexer.tokens.push_back({Token::Token_Struct});
    } else 
    if (cmp_string(lexer.sit.begin, "static", before_space)) {
      lexer.tokens.push_back({Token::Token_Static});
    } else 
    if (cmp_string(lexer.sit.begin, "expand", before_space)) {
      lexer.tokens.push_back({Token::Token_Expand});
    } else 
    if (cmp_string(lexer.sit.begin, "narrow", before_space)) {
      lexer.tokens.push_back({Token::Token_Narrow});
    } else 
    if (cmp_string(lexer.sit.begin, "extern", before_space)) {
      lexer.tokens.push_back({Token::Token_Extern});
    } else 
    // if (cmp_string(lexer.sit.begin, "char", before_space)) {
    //   lexer.tokens.push_back({Token::Token_Char});
    // } else 
    // if (cmp_string(lexer.sit.begin, "float", before_space)) {
    //   lexer.tokens.push_back({Token::Token_Float});
    // } else 
    // if (cmp_string(lexer.sit.begin, "double", before_space)) {
    //   lexer.tokens.push_back({Token::Token_Double});
    // } else 
    // if (cmp_string(lexer.sit.begin, "int", before_space)) {
    //   lexer.tokens.push_back({Token::Token_Integer});
    // } else 
    if (cmp_string(lexer.sit.begin, "unsigned", before_space)) {
      lexer.tokens.push_back({Token::Token_Unsigned});
    } else 
    if (cmp_string(lexer.sit.begin, "short", before_space)) {
      lexer.tokens.push_back({Token::Token_Short});
    } else 
    // if (cmp_string(lexer.sit.begin, "string", before_space)) {
    //   lexer.tokens.push_back({Token::Token_String});
    // } else 
    if (cmp_string(lexer.sit.begin, "let", before_space)) {
      lexer.tokens.push_back({Token::Token_Let});
    } else 
    if (cmp_string(lexer.sit.begin, "const", before_space)) {
      lexer.tokens.push_back({Token::Token_Const});
    } else 
    if (cmp_string(lexer.sit.begin, "void", before_space)) {
      lexer.tokens.push_back({Token::Token_Void});
    } else 
    {return false;}
    lexer.sit += before_space;
    return true;
  }

  bool CheckText(Lexer& lexer) {
    std::string buffer;
    while (!lexer.sit.IsEnd()) {
      char c = *(lexer.sit++);
      if (
        mew::string::CharInString(" \t\r\n\v\f.,*#;:\'\"(){}[]+=-/@#$!%^&*`~|<>?", c)
      ) {
        lexer.sit--;
        char* sb = new char[buffer.size()+1];
        memcpy(sb, buffer.c_str(), buffer.size());
        sb[buffer.size()] = '\0';
        lexer.tokens.push_back({Token::Token_Text, sb});
        break;
      } 
      else {
        buffer += c;
      }
    }
    return true;
  }
  
  bool CheckString(Lexer& lexer) {
    if (*(lexer.sit) == '"') {
      std::string buffer;
      size_t it = 0;
      while (!lexer.sit.IsEnd()) {
        char c = *(++lexer.sit);
        if (c == '"' && buffer[it] != '\\') {
          lexer.tokens.push_back({Token::Token_String, (char*)buffer.c_str()});
          return true;
          break;
        } 
        else if (buffer[it] != '\\' && c == 'n') {
          buffer[it] = '\n';		
        } 
        else if (buffer[it] != '\\' && c == 't') {
          buffer[it] = '\t';		
        } 
        else if (buffer[it] != '\\' && c == 'r') {
          buffer[it] = '\r';		
        } 
        else if (buffer[it] != '\\' && c == '0') {
          buffer[it] = '\0';		
        } 
        else {
          buffer[it++] = c;
        }
      }
    }
    return false;
  }

  #define PUSH_SINGLE_TOKEN(cr, _token) case cr: lexer.tokens.push_back({_token}); break;
  #define SKIP_SINGLE_TOKEN(cr) case cr: break;

  void Tokenize(Lexer& lexer, const char* source) {
    lexer.source = source;
    lexer.sit = mew::string::StringIterator(source);
    while (!lexer.sit.IsEnd()) {
      char symbol = *(lexer.sit++);
      switch (symbol) {
        PUSH_SINGLE_TOKEN('0', Token::Token_Zero);
        PUSH_SINGLE_TOKEN('1', Token::Token_One);
        PUSH_SINGLE_TOKEN('2', Token::Token_Two);
        PUSH_SINGLE_TOKEN('3', Token::Token_Three);
        PUSH_SINGLE_TOKEN('4', Token::Token_Four);
        PUSH_SINGLE_TOKEN('5', Token::Token_Five);
        PUSH_SINGLE_TOKEN('6', Token::Token_Six);
        PUSH_SINGLE_TOKEN('7', Token::Token_Seven);
        PUSH_SINGLE_TOKEN('8', Token::Token_Eight);
        PUSH_SINGLE_TOKEN('9', Token::Token_Nine);
        PUSH_SINGLE_TOKEN('.', Token::Token_Dot);
        PUSH_SINGLE_TOKEN(',', Token::Token_Comma);
        PUSH_SINGLE_TOKEN('*', Token::Token_Star);
        PUSH_SINGLE_TOKEN('#', Token::Token_Sharp);
        PUSH_SINGLE_TOKEN(';', Token::Token_Semicolon);
        PUSH_SINGLE_TOKEN(':', Token::Token_Colon);
        PUSH_SINGLE_TOKEN('\'', Token::Token_SingleQuote);
        // PUSH_SINGLE_TOKEN('\"', Token::Token_DoubleQuote);
        PUSH_SINGLE_TOKEN('`', Token::Token_ApostropheQuote);
        PUSH_SINGLE_TOKEN('=', Token::Token_Equal);
        PUSH_SINGLE_TOKEN('-', Token::Token_Minus);
        PUSH_SINGLE_TOKEN('/', Token::Token_Slash);
        PUSH_SINGLE_TOKEN('\\', Token::Token_BackSlash);
        PUSH_SINGLE_TOKEN('|', Token::Token_Split);
        PUSH_SINGLE_TOKEN('_', Token::Token_Underscore);
        PUSH_SINGLE_TOKEN('&', Token::Token_Ampersand);
        PUSH_SINGLE_TOKEN('$', Token::Token_Dollar);
        PUSH_SINGLE_TOKEN('%', Token::Token_Percent);
        PUSH_SINGLE_TOKEN('@', Token::Token_At);
        PUSH_SINGLE_TOKEN('!', Token::Token_Exclamate);
        PUSH_SINGLE_TOKEN('?', Token::Token_Question);
        PUSH_SINGLE_TOKEN('~', Token::Token_Tilda);
        PUSH_SINGLE_TOKEN('^', Token::Token_ArrowUp);
        PUSH_SINGLE_TOKEN('<', Token::Token_ArrowOpen);
        PUSH_SINGLE_TOKEN('>', Token::Token_ArrowClose);
        PUSH_SINGLE_TOKEN('(', Token::Token_RoundOpen);
        PUSH_SINGLE_TOKEN(')', Token::Token_RoundClose);
        PUSH_SINGLE_TOKEN('[', Token::Token_SquareOpen);
        PUSH_SINGLE_TOKEN(']', Token::Token_SquareClose);
        PUSH_SINGLE_TOKEN('{', Token::Token_FigureOpen);
        PUSH_SINGLE_TOKEN('}', Token::Token_FigureClose);
        SKIP_SINGLE_TOKEN(' ');
        SKIP_SINGLE_TOKEN('\t');
        SKIP_SINGLE_TOKEN('\r');
        SKIP_SINGLE_TOKEN('\b');
        SKIP_SINGLE_TOKEN('\n');
        default:
          lexer.sit--;
          if (CheckString(lexer)) { }
          else if (!CheckKeyWords(lexer)) {
            CheckText(lexer);
            // lexer.tokens.push_back({Token::Token_KeyWord}); 
          }
        break;
      }
    }
  }
#pragma endregion TOKENIZE
  
  
}

#endif