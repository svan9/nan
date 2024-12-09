#ifndef _NAN_ASM_IMPL
#define _NAN_ASM_IMPL

#include "mewall.h"
#include "virtual.hpp"
#include "virtuallib.hpp"
#include <iostream>
#include <map>

namespace Virtual::Asm {
		static const char* spaces = " \n\r\v\b\t";
		using StringIterator = mew::string::StringIterator;

		#define cmp_string(f, a, b) (strlen(a) == b && memcmp(f, a, b))
		#define SKIP_SINGLE_TOKEN(cr) case cr: break;
		#define SKIP_WORD() sit += before_space; \
				sit += mew::string::CountRightFor(sit.begin, spaces);

		void JumpToLabel(StringIterator& sit, Virtual::Lib::Builder& builder) {
			size_t before_space =
				mew::string::CountRightBefore(sit.begin, spaces);
			char buffer[before_space+1];
			memcpy(buffer, sit.begin, before_space);				
			buffer[before_space] = '\0';
			builder << builder.AddressFunction(buffer);
			sit += before_space;
		}
		
		void GetNextType(StringIterator& sit, Virtual::Lib::Builder& builder) {
			if (cmp_string(sit.begin, "mem", 3)) {
				sit += 3;
				builder << Instruction_MEM;
			} 
			else if (cmp_string(sit.begin, "rmem", 4)) {
				sit += 4;
				builder << Instruction_RMEM;
			}
			else if (cmp_string(sit.begin, "num", 3)) {
				sit += 3;
				builder << Instruction_NUM;
			}
		}

		void GetNextNumber(StringIterator& sit, Virtual::Lib::Builder& builder) {
			size_t before_space =
				mew::string::CountRightBefore(sit.begin, spaces);
			char buffer[before_space+1];
			memcpy(buffer, sit.begin, before_space);				
			buffer[before_space] = '\0';
			char* p;
			uint num = (uint)strtol(buffer, &p, 10);
			MewAssert(*p == 0);
			builder << num;
			sit += before_space;
		}

		void GetNumberNextType(StringIterator& sit, Virtual::Lib::Builder& builder) {
			GetNextType(sit, builder);
			size_t before_space =
				mew::string::CountRightBefore(sit.begin, spaces);
			int num = 1;
			if (*sit.begin == '-') {
				num = -1;
				before_space--;
				sit++;
			}
			char buffer[before_space+1];
			memcpy(buffer, sit.begin, before_space);				
			buffer[before_space] = '\0';
			char* p;
			num *= (int)strtol(buffer, &p, 10);
			MewAssert(*p == 0);
			builder << num;
			sit += before_space;
		}
		
		Virtual::Code* ProccessCode(const char* source) {
			Virtual::Lib::Builder builder;
			StringIterator sit(source);
			while (!sit.IsEnd()) {
				char symbol = *(sit++);
				switch (symbol) {
					SKIP_SINGLE_TOKEN(' ');
					SKIP_SINGLE_TOKEN('\t');
					SKIP_SINGLE_TOKEN('\r');
					SKIP_SINGLE_TOKEN('\b');
					SKIP_SINGLE_TOKEN('\n');
					default:
						size_t before_space =
							mew::string::CountRightBefore(sit.begin, spaces);
						if (cmp_string(sit.begin, "push", before_space)) {
							SKIP_WORD();
							builder << Instruction_PUSH;
							GetNumberNextType(sit, builder);
						} else 
						if (cmp_string(sit.begin, "pop", before_space)) {
							SKIP_WORD();
							builder << Instruction_POP;
						} else 
						if (cmp_string(sit.begin, "inc", before_space)) {
							SKIP_WORD();
							builder << Instruction_INC;
							GetNextType(sit, builder); /* a */
						} else 
						if (cmp_string(sit.begin, "dec", before_space)) {
							SKIP_WORD();
							builder << Instruction_DEC;
							GetNextType(sit, builder); /* a */
						} else 
						if (cmp_string(sit.begin, "add", before_space)) {
							SKIP_WORD();
							builder << Instruction_ADD;
							GetNextType(sit, builder); /* a */
							GetNextType(sit, builder); /* b */
						} else 
						if (cmp_string(sit.begin, "sub", before_space)) {
							SKIP_WORD();
							builder << Instruction_SUB;
							GetNextType(sit, builder); /* a */
							GetNextType(sit, builder); /* b */
						} else 
						if (cmp_string(sit.begin, "mul", before_space)) {
							SKIP_WORD();
							builder << Instruction_MUL;
							GetNextType(sit, builder); /* a */
							GetNextType(sit, builder); /* b */
						} else 
						if (cmp_string(sit.begin, "div", before_space)) {
							SKIP_WORD();
							builder << Instruction_DIV;
							GetNextType(sit, builder); /* a */
							GetNextType(sit, builder); /* b */
						} else 
						if (cmp_string(sit.begin, "xor", before_space)) {
							SKIP_WORD();
							builder << Instruction_XOR;
							GetNextType(sit, builder); /* a */
							GetNextType(sit, builder); /* b */
						} else 
						if (cmp_string(sit.begin, "or", before_space)) {
							SKIP_WORD();
							builder << Instruction_OR;
							GetNextType(sit, builder); /* a */
							GetNextType(sit, builder); /* b */
						} else 
						if (cmp_string(sit.begin, "not", before_space)) {
							SKIP_WORD();
							builder << Instruction_NOT;
							GetNextType(sit, builder); /* a */
						} else 
						if (cmp_string(sit.begin, "and", before_space)) {
							SKIP_WORD();
							builder << Instruction_AND;
							GetNextType(sit, builder); /* a */
							GetNextType(sit, builder); /* b */
						} else 
						if (cmp_string(sit.begin, "ls", before_space)) {
							SKIP_WORD();
							builder << Instruction_LS;
							GetNextType(sit, builder); /* a */
							GetNextType(sit, builder); /* b */
						} else 
						if (cmp_string(sit.begin, "rs", before_space)) {
							SKIP_WORD();
							builder << Instruction_RS;
							GetNextType(sit, builder); /* a */
							GetNextType(sit, builder); /* b */
						} else 
						if (cmp_string(sit.begin, "jmp", before_space)) {
							SKIP_WORD();
							builder << Instruction_JMP;
							JumpToLabel(sit, builder);
						} else 
						if (cmp_string(sit.begin, "ret", before_space)) {
							SKIP_WORD();
							builder << Instruction_RET;
						} else 
						if (cmp_string(sit.begin, "test", before_space)) {
							SKIP_WORD();
							builder << Instruction_TEST;
							GetNextType(sit, builder); /* a */
							GetNextType(sit, builder); /* b */
						} else 
						if (cmp_string(sit.begin, "je", before_space)) {
							SKIP_WORD();
							builder << Instruction_JE;
							JumpToLabel(sit, builder);
						} else 
						if (cmp_string(sit.begin, "jl", before_space)) {
							SKIP_WORD();
							builder << Instruction_JL;
							JumpToLabel(sit, builder);
						} else 
						if (cmp_string(sit.begin, "jm", before_space)) {
							SKIP_WORD();
							builder << Instruction_JM;
							JumpToLabel(sit, builder);
						} else 
						if (cmp_string(sit.begin, "jel", before_space)) {
							SKIP_WORD();
							builder << Instruction_JEL;
							JumpToLabel(sit, builder);
						} else 
						if (cmp_string(sit.begin, "jem", before_space)) {
							SKIP_WORD();
							builder << Instruction_JEM;
							JumpToLabel(sit, builder);
						} else 
						if (cmp_string(sit.begin, "jne", before_space)) {
							SKIP_WORD();
							builder << Instruction_JNE;
							JumpToLabel(sit, builder);
						} else 
						if (cmp_string(sit.begin, "mov", before_space)) {
							SKIP_WORD();
							builder << Instruction_MOV;
							GetNextType(sit, builder); /* a */
							GetNextNumber(sit, builder);
						} else 
						if (cmp_string(sit.begin, "putc", before_space)) {
							SKIP_WORD();
							builder << Instruction_PUTC;
							MewNotImpl();
						} else 
						if (cmp_string(sit.begin, "puti", before_space)) {
							SKIP_WORD();
							builder << Instruction_PUTI;
						} else 
						if (cmp_string(sit.begin, "puts", before_space)) {
							SKIP_WORD();
							builder << Instruction_PUTS;
							GetNextNumber(sit, builder);
						} else
						if (cmp_string(sit.begin, "data", before_space)) {
							SKIP_WORD();
							char buffer[512];
							MewAssert(*sit.begin == '\'');
							sit++;
							int length = 0;
							for (; *sit.begin != '\''; sit++) {
								buffer[length++] = *sit.begin;
							}
							buffer[length] = '\0';
							builder += buffer;
						} else {
							if (mew::string::EndWith(sit.begin, ':')) {
								char buffer[before_space];
								memcpy(buffer, sit.begin, before_space-1);
								buffer[before_space] = '\0';
								builder.BeginFunction(buffer);
							}
							SKIP_WORD();
						}
					break;
				}
			}
			return builder.Build();
		}
}

#endif