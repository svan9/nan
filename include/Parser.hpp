#ifndef _NAN_PARSER_IMPL
#define _NAN_PARSER_IMPL

#include <vector>
#include "config.h"
#include "astlib.hpp"
#include "grammar.hpp"
#include "lexer.hpp"

namespace Parser {
	struct Parser {
		Lexer::Lexer* lexer;
		AST* ast;
	};
	
	void Parse(Parser& parser, Lexer::Lexer& lexer) {
		parser.lexer = &lexer;
		
	}
	
}

#endif