#ifndef _NAN_ASM_IMPL
#define _NAN_ASM_IMPL

#include "mewall.h"
#include "virtual.hpp"
#include <iostream>
#include <unordered_map>
#include <initializer_list>
#include "virtuallib.hpp"

namespace Virtual::Asm {
	using namespace mew::utils;

	enum struct TokenType: int {
		// simple type
		Undefined,
		None, String, Number, Text,	Colon,  Label,
		Data, DB, DA, Entry,
		// operators
		Minus, Plus, Equal, Multiply, Divide,
		// Brackets
		RoundOpenBracket, RoundCloseBracket,
		SquareOpenBracket, SquareCloseBracket,
		// registers
		fx1, fx2, fx3, fx4, fx5, dx1, 
		dx2, dx3, dx4, dx5, r1,
		r2, r3, r4, r5, rx1,
		rx2, rx3, rx4, rx5,
		Rdi,
		// commands
		Call, Push, Pop, Rpop, Add, Sub, Mul, Div, Inc, Dec, Xor, Or, 
		Not, And, Ls, Rs, Jmp, Ret, Exit, Test, Je, Jel, Jem, Jne, Jl,
		Jm, Mov, Swap, Mset, Swst, Write, Read, Open, Putc, Puti, Puts, 
		Getch, Movrdi,
		RdiOffset, DataSize,
	};

	const char* stringify_tokentype(TokenType type) {
		switch (type) {
			case TokenType::Undefined: return "Undefined";
			case TokenType::None: return "None";
			case TokenType::String: return "String";
			case TokenType::Number: return "Number";
			case TokenType::Text: return "Text";
			case TokenType::Colon: return "Colon";
			case TokenType::Label: return "Label";
			case TokenType::RdiOffset: return "RdiOffset";
			case TokenType::Data: return "Data";
			case TokenType::DB: return "DB";
			case TokenType::DA: return "DA";
			case TokenType::Entry: return "Entry";
			case TokenType::Minus: return "Minus";
			case TokenType::Plus: return "Plus";
			case TokenType::Equal: return "Equal";
			case TokenType::Multiply: return "Multiply";
			case TokenType::Divide: return "Divide";
			case TokenType::RoundOpenBracket: return "RoundOpenBracket";
			case TokenType::RoundCloseBracket: return "RoundCloseBracket";
			case TokenType::SquareOpenBracket: return "SquareOpenBracket";
			case TokenType::SquareCloseBracket: return "SquareCloseBracket";
			case TokenType::fx1: return "fx1";
			case TokenType::fx2: return "fx2";
			case TokenType::fx3: return "fx3";
			case TokenType::fx4: return "fx4";
			case TokenType::fx5: return "fx5";
			case TokenType::dx1: return "dx1";
			case TokenType::dx2: return "dx2";
			case TokenType::dx3: return "dx3";
			case TokenType::dx4: return "dx4";
			case TokenType::dx5: return "dx5";
			case TokenType::r1: return "r1";
			case TokenType::r2: return "r2";
			case TokenType::r3: return "r3";
			case TokenType::r4: return "r4";
			case TokenType::r5: return "r5";
			case TokenType::rx1: return "rx1";
			case TokenType::rx2: return "rx2";
			case TokenType::rx3: return "rx3";
			case TokenType::rx4: return "rx4";
			case TokenType::rx5: return "rx5";
			case TokenType::Call: return "Call";
			case TokenType::Push: return "Push";
			case TokenType::Pop: return "Pop";
			case TokenType::Rpop: return "Rpop";
			case TokenType::Add: return "Add";
			case TokenType::Sub: return "Sub";
			case TokenType::Mul: return "Mul";
			case TokenType::Div: return "Div";
			case TokenType::Inc: return "Inc";
			case TokenType::Dec: return "Dec";
			case TokenType::Xor: return "Xor";
			case TokenType::Or: return "Or";
			case TokenType::Not: return "Not";
			case TokenType::And: return "And";
			case TokenType::Ls: return "Ls";
			case TokenType::Rs: return "Rs";
			case TokenType::Jmp: return "Jmp";
			case TokenType::Ret: return "Ret";
			case TokenType::Exit: return "Exit";
			case TokenType::Test: return "Test";
			case TokenType::Je: return "Je";
			case TokenType::Jel: return "Jel";
			case TokenType::Jem: return "Jem";
			case TokenType::Jne: return "Jne";
			case TokenType::Jl: return "Jl";
			case TokenType::Jm: return "Jm";
			case TokenType::Mov: return "Mov";
			case TokenType::Swap: return "Swap";
			case TokenType::Mset: return "Mset";
			case TokenType::Swst: return "Swst";
			case TokenType::Write: return "Write";
			case TokenType::Read: return "Read";
			case TokenType::Open: return "Open";
			case TokenType::Putc: return "Putc";
			case TokenType::Puti: return "Puti";
			case TokenType::Puts: return "Puts";
			case TokenType::Getch: return "Getch";
			case TokenType::Movrdi: return "Movrdi";
			case TokenType::DataSize: return "DataSize";
			default: return nullptr;
		}
	}

	static std::unordered_map<const char *, TokenType> tokens = {
			{":", TokenType::Colon},
			{"-", TokenType::Minus},
			{"+", TokenType::Plus},
			{"=", TokenType::Equal},
			{"*", TokenType::Multiply},
			{"/", TokenType::Divide},
			{"(", TokenType::RoundOpenBracket},
			{")", TokenType::RoundCloseBracket},
			{"[", TokenType::SquareOpenBracket},
			{"]", TokenType::SquareCloseBracket},
			{ "fx1", TokenType::fx1},
			{ "fx2", TokenType::fx2},
			{ "fx3", TokenType::fx3},
			{ "fx4", TokenType::fx4},
			{ "fx5", TokenType::fx5},
			{ "dx1", TokenType::dx1},
			{ "dx2", TokenType::dx2},
			{ "dx3", TokenType::dx3},
			{ "dx4", TokenType::dx4},
			{ "dx5", TokenType::dx5},
			{ "r1", TokenType::r1},
			{ "r2", TokenType::r2},
			{ "r3", TokenType::r3},
			{ "r4", TokenType::r4},
			{ "r5", TokenType::r5},
			{ "rx1", TokenType::rx1},
			{ "rx2", TokenType::rx2},
			{ "rx3", TokenType::rx3},
			{ "rx4", TokenType::rx4},
			{ "rx5", TokenType::rx5},
			{ "data", TokenType::Data},
			{ "da", TokenType::DA},
			{ "db", TokenType::DB},
			{ "entry", TokenType::Entry},
			{ "call", TokenType::Call},
			{ "push", TokenType::Push},
			{ "pop", TokenType::Pop},
			{ "rpop", TokenType::Rpop},
			{ "add", TokenType::Add},
			{ "sub", TokenType::Sub},
			{ "mul", TokenType::Mul},
			{ "div", TokenType::Div},
			{ "inc", TokenType::Inc},
			{ "dec", TokenType::Dec},
			{ "xor", TokenType::Xor},
			{ "or", TokenType::Or},
			{ "not", TokenType::Not},
			{ "and", TokenType::And},
			{ "ls", TokenType::Ls},
			{ "rs", TokenType::Rs},
			{ "jmp", TokenType::Jmp},
			{ "ret", TokenType::Ret},
			{ "exit", TokenType::Exit},
			{ "test", TokenType::Test},
			{ "je", TokenType::Je},
			{ "jel", TokenType::Jel},
			{ "jem", TokenType::Jem},
			{ "jne", TokenType::Jne},
			{ "jl", TokenType::Jl},
			{ "jm", TokenType::Jm},
			{ "mov", TokenType::Mov},
			{ "swap", TokenType::Swap},
			{ "mset", TokenType::Mset},
			{ "swst", TokenType::Swst},
			{ "write", TokenType::Write},
			{ "read", TokenType::Read},
			{ "open", TokenType::Open},
			{ "putc", TokenType::Putc},
			{ "puti", TokenType::Puti},
			{ "puts", TokenType::Puts},
			{ "getch", TokenType::Getch},
			{ "movrdi", TokenType::Movrdi},
			// { "rdi", TokenType::Rdi},
	};

	struct Token {
		TokenType type;
		const char* value = nullptr;

		void print() {
			const char* str = stringify_tokentype(type);
			if (str == nullptr) {
				printf("{BREAKEN TYPE}");
			} else 
			if (type == TokenType::Number || type == TokenType::RdiOffset || type == TokenType::DataSize) {
				printf("{%s, %i} -- ", str, (int)value);
			} else
			if (value != nullptr) printf("{%s, '%s'} -- ", str, value);
			else printf("{%s} -- ", str);
		}
	};
	
	struct Lexer {
		mew::stack<mew::stack<Token>> token_row;
		mew::stack<const char*> lines;

		void _fill_simple() {
			for (int i = 0; i < lines.size(); ++i) {
				mew::stack<Token> line_tk;
				const char* line = lines[i];
				TokenRow tr(line);
				const char* word;
				while ((word = *tr++) != nullptr && *word != '\0') {
					Token tk;
					bool is_find = false;
					for (auto it = tokens.begin(); it != tokens.end(); ++it) {
						if (mew::strcmp(it->first, word)) {
							tk.type = it->second;
							line_tk.push(tk);
							is_find = true;
							break;
						}
					}
					if (!is_find) {
						tk.type = TokenType::Undefined;
						tk.value = word;
						line_tk.push(tk);
					}
				}
				token_row.push(line_tk.copy());
			}
		}

		void _watch_token(Token& tk) {
			if (getLastChar(tk.value) == ':') {
				tk.type = TokenType::Label;
				tk.value = strtrim(tk.value, strlen(tk.value)-1);
				return;
			} 
			// line.insert(tk, idx);
			bool is_number;
			int i = str_to_int(tk.value, is_number);
			if (is_number) {
				tk.type = TokenType::Number,
				tk.value = (char*)i;
				return;
			}
			if (*tk.value == '"' && getLastChar(tk.value) == '"') {
				tk.type = TokenType::String;
				tk.value = scopy(tk.value+1, strlen(tk.value)-2);
				return;
			}
			/* 
				todo parse & separate grammars in Token.value 
				& insert in place of current
			*/
			
			tk.type = TokenType::Text;
		}

		void _decrypt_undefined() {
			for (int x = 0; x < token_row.size(); ++x) {
				auto& line = token_row[x];
				for (int y = 0; y < line.size(); ++y) {
					auto& e = line[y];
					if (e.type == TokenType::Undefined) {
						_watch_token(e);
					}
				}
			}
		}

		Lexer(const char* str) {
			lines = *splitLines(str);
			_fill_simple();
			// print();
			_decrypt_undefined();
		}

		void print() {
			for (int x = 0; x < token_row.size(); ++x) {
				auto& line = token_row[x];
				printf("[ ");
				for (int y = 0; y < line.size(); ++y) {
					line[y].print();
				}
				printf(" ]\n");
				
			}
		}
	};

	struct Parser {
		Lexer& lexer;

		Parser(Lexer& lexer): lexer(lexer) {parse();}

		bool same_type_sequence(mew::stack<Token>& row, size_t start, std::initializer_list<TokenType> types) {
			if (row.size()-start > types.size()) return false;
			auto begin = types.begin();
			for (int i = 0; i < types.size(); ++i) {
				auto tkt = begin[i];
				if (row[start+i].type != tkt) return false; 
			}
			return true;
		}

		void parse() {
			for (int x = 0; x < lexer.token_row.size(); ++x) {
				auto& line = lexer.token_row[x];
				// printf("[ ");
				for (int y = 0; y < line.size(); ++y) {
					auto& tk = line[y];
					bool is_rdioffset = same_type_sequence(line, y, {
						TokenType::RoundOpenBracket, TokenType::Text, TokenType::Minus, TokenType::Number, TokenType::RoundCloseBracket
					}) && mew::strcmp(line[y+1].value, "rdi");
					bool is_datasize = same_type_sequence(line, y, {
						TokenType::SquareOpenBracket, TokenType::Number, TokenType::SquareCloseBracket
					});
					if (is_rdioffset) {
						tk.type = TokenType::RdiOffset;
						tk.value = line[y+3].value;
						line.erase(y+1, 4);
					} else if (is_datasize) {
						tk.type = TokenType::DataSize;
						tk.value = line[y+1].value;
						line.erase(y+1, 2);
					}
					// line[y].print();
				}
				// printf(" ]\n");
				
			}
		}
	};

	using namespace ::Virtual::Lib;
	struct Compiler {
		/*
			todo for Compiler
			[ ] store labels in code for nexts calling 
			[ ] others
			[ ] (::Virtual) save Code to file
		*/
		Lexer& lexer;
		std::unordered_map<const char*, size_t> labels;
		size_t entry = 0;
		Builder builder;

		Compiler(Lexer& lexer): lexer(lexer) {
			compile();
		}

		void compile() {
			// builder.MarkLabel();
		}
	};


	namespace Test {
		void test_lexer(){
			const char* str = 
			"entry __start\n"
			"\n"
			"data db hellow \"Hellow, world\\n\\0\"\n"
			"data da space[1000]\n"
			"\n"
			"__start:\n"
			"	puts hellow\n"
			"	push 0\n"
			"	push 10\n"
			"L1:\n"
			"	test \n"
			"	jem LE1\n"
			"	puti (rdi-4)\n"
			"	inc (rdi-4)\n"
			"	jmp L1\n"
			"LE1:\n"
			"	push 0\n"
			"	ret\n";
			Lexer lex(str);
			Parser par(lex);
			lex.print();
		}
	};
}

#endif