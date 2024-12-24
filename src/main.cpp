#include <iostream>
#include "virtual.hpp"
#include "virtuallib.hpp"
#include "lexer.hpp"
#include "parser.hpp"

int main() {
	std::string finner = mew::ReadFile("E:/so2u/GITHUB/cuba/nan/nan/variable.nan");
	Lexer::Lexer lex;
	Lexer::Tokenize(lex, finner.c_str());
	Lexer::PrintLexer(lex);
	Parser::Parser par;
	Parser::Parse(par, lex);
	par.builder.Save("./var_tmp.nb");
	// Lexer::PrintLexer(lex);
	// printf("test -- virtual -- \n");
	// Tests::test_Virtual();
	// printf("\ntest -- virtual::lib --\n");
	// Tests::test_Virtual_Lib();
}

