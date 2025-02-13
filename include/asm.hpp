#ifndef _NAN_ASM_IMPL
#define _NAN_ASM_IMPL

#include "mewall.h"
#include "virtual.hpp"
#include "virtuallib.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include <iostream>
#include <map>

namespace Virtual::Asm {
	Virtual::Code* ProccessCode(const char* source) {
		Virtual::Lib::Builder builder;
		Lexer::Lexer lex;
		Lexer::Tokenize(lex, source);
		Parser::Parser parser;
		Parser::Parse(parser, lex);
		return parser.builder.Build();
	}
}

#endif