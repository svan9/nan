#ifndef _NAN_ASM_IMPL
#define _NAN_ASM_IMPL

#include "config.h"
#include "mewlib.h"
#include "virtual.hpp"
#include "grammar.hpp"
#include <filesystem>

namespace Virtual {
	namespace Lexer {
		#define PUSH_SINGLE_TOKEN(cr, _token) case cr: lexer.tokens.push_back({_token}); break;
		#define SKIP_SINGLE_TOKEN(cr) case cr: break;

		struct Token {
			Instruction kind;
			const char* data;	
		};

		struct Lexer {
			StringIterator sit;
			std::vector<Token> tokens;
			typedef std::vector<Token>::iterator Iterator;
		};

		#define cmp_string(f, a, b) (strlen(a) == b && memcmp(f, a, b))

		bool CheckKeyWords(Lexer& lexer) {
			size_t before_space =
				CountRightBefore(lexer.sit.begin, " \n\r\v\b\t");
			if (cmp_string(lexer.sit.begin, "push", before_space)) {
				lexer.tokens.push_back({Instruction_PUSH});
			} else 
			if (cmp_string(lexer.sit.begin, "pop", before_space)) {
				lexer.tokens.push_back({Instruction_POP});
			} else 
			if (cmp_string(lexer.sit.begin, "add", before_space)) {
				lexer.tokens.push_back({Instruction_ADD});
			} else 
			if (cmp_string(lexer.sit.begin, "sub", before_space)) {
				lexer.tokens.push_back({Instruction_SUB});
			} else 
			if (cmp_string(lexer.sit.begin, "mul", before_space)) {
				lexer.tokens.push_back({Instruction_MUL});
			} else 
			if (cmp_string(lexer.sit.begin, "div", before_space)) {
				lexer.tokens.push_back({Instruction_DIV});
			} else 
			if (cmp_string(lexer.sit.begin, "xor", before_space)) {
				lexer.tokens.push_back({Instruction_XOR});
			} else 
			if (cmp_string(lexer.sit.begin, "or", before_space)) {
				lexer.tokens.push_back({Instruction_OR});
			} else 
			if (cmp_string(lexer.sit.begin, "not", before_space)) {
				lexer.tokens.push_back({Instruction_NOT});
			} else 
			if (cmp_string(lexer.sit.begin, "and", before_space)) {
				lexer.tokens.push_back({Instruction_AND});
			} else 
			if (cmp_string(lexer.sit.begin, "ls", before_space)) {
				lexer.tokens.push_back({Instruction_LS});
			} else 
			if (cmp_string(lexer.sit.begin, "rs", before_space)) {
				lexer.tokens.push_back({Instruction_RS});
			} else 
			if (cmp_string(lexer.sit.begin, "jmp", before_space)) {
				lexer.tokens.push_back({Instruction_JMP});
			} else 
			if (cmp_string(lexer.sit.begin, "ret", before_space)) {
				lexer.tokens.push_back({Instruction_RET});
			} else 
			if (cmp_string(lexer.sit.begin, "test", before_space)) {
				lexer.tokens.push_back({Instruction_TEST});
			} else 
			if (cmp_string(lexer.sit.begin, "je", before_space)) {
				lexer.tokens.push_back({Instruction_JE});
			} else 
			if (cmp_string(lexer.sit.begin, "jl", before_space)) {
				lexer.tokens.push_back({Instruction_JL});
			} else 
			if (cmp_string(lexer.sit.begin, "jm", before_space)) {
				lexer.tokens.push_back({Instruction_JM});
			} else 
			if (cmp_string(lexer.sit.begin, "jel", before_space)) {
				lexer.tokens.push_back({Instruction_JEL});
			} else 
			if (cmp_string(lexer.sit.begin, "jem", before_space)) {
				lexer.tokens.push_back({Instruction_JEM});
			} else 
			if (cmp_string(lexer.sit.begin, "mov", before_space)) {
				lexer.tokens.push_back({Instruction_MOV});
			} else 
			if (cmp_string(lexer.sit.begin, "putc", before_space)) {
				lexer.tokens.push_back({Instruction_PUTC});
			} else 
			if (cmp_string(lexer.sit.begin, "puti", before_space)) {
				lexer.tokens.push_back({Instruction_PUTI});
			} else 
			if (cmp_string(lexer.sit.begin, "puts", before_space)) {
				lexer.tokens.push_back({Instruction_PUTS});
			} else 
			{return false;}
			return true;
		}

		bool CheckString(Lexer& lexer) {
			if (*(lexer.sit) == '"') {
				std::string buffer;
				size_t it = 0;
				while (!lexer.sit.IsEnd()) {
					char c = *(++lexer.sit);
					if (c == '"' && buffer[it] != '\\') {
						lexer.tokens.push_back({Instruction_NONE, (char*)buffer.c_str()});
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
		}


		void Tokenize(Lexer& lexer, const char* source) {
			StringIterator sit(source);
			lexer.sit = sit;
			while (!lexer.sit.IsEnd()) {
				char symbol = *(lexer.sit++);
				switch (symbol) {
					SKIP_SINGLE_TOKEN(' ');
					SKIP_SINGLE_TOKEN('\t');
					SKIP_SINGLE_TOKEN('\r');
					SKIP_SINGLE_TOKEN('\b');
					SKIP_SINGLE_TOKEN('\n');
					default:
						if (CheckString(lexer)) { }
						else if (!CheckKeyWords(lexer)) {
							lexer.tokens.push_back({Instruction_NONE}); 
						}
					break;
				}
			}
		}
	}
	
	Code* Compile(const char* source) {
		CodeBuilder cb;

		return *cb;
	}

	namespace fs = std::filesystem;
	void Compile(const fs::path& path, const fs::path& end_path) {
    std::ifstream file(path, std::ios::in | std::ios::binary);
		file >> std::noskipws;
		// file.seekg()

		// Code* code = Compile()
	}

	void Compile(const char* path, const char* end_path) {
    fs::path __path(path);
    if (!__path.is_absolute()) {
      __path = fs::absolute(__path.lexically_normal());
    }
    fs::path __end_path(end_path);
    if (!__end_path.is_absolute()) {
      __end_path = fs::absolute(__end_path.lexically_normal());
    }
		Compile(__path, __end_path);
	}

}

#endif