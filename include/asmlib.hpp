#ifndef ASMLIB_HPP
#define ASMLIB_HPP

#include "mewlib.h"
#include "mewstack.hpp"
#include "asm.hpp"
#include "virtual.hpp"

namespace Virtual::Asm {

	template<size_t stack_max_size>
	class StackListener {
	private:
		struct Chunk {
			byte data[]; // 10001
		};
		byte* chunks;
	public:
		StackListener(): chunks(new byte[stack_max_size]) {
			memset(chunks, 0, sizeof(byte)*stack_max_size);
		}

		size_t get_chunk_size(byte* b, int offset) {
			if (b[0] == 0) return 0;
			size_t size = 1;
			for (int i = 1; i < stack_max_size-offset; ++i) {
				if (b[i] == 1) break;
				++size;
			}
			return size;
		}

		size_t get_chunk_free_size(byte* b, int offset) {
			size_t size = 0;
			for (int i = 0; i < stack_max_size-offset; ++i) {
				if (b[i] == 1) break;
				++size;
			}
			return size;
		}

		size_t assign(size_t size = 4) {
			for (int i = 0; i < GetMaxSize(); ++i) {
				auto c = &chunks[i];
				size_t ss = get_chunk_free_size(c, i);
				if (ss >= size) {
					memset(c, 1, size);
					return i;
				}
			}
			return -1;
		}

		void free(size_t idx, size_t size = 4) {
			auto c = &chunks[idx];
			memset(c, 0, size);
		}

		constexpr size_t GetMaxSize() const noexcept {
			return stack_max_size;
		}
	};

	template<typename T>
	concept argTypedLValue = std::same_as<T, TokenType> || std::same_as<T, size_t>;
	template<typename T>
	concept argTypedRegValue = std::same_as<T, TokenType>;
	template<typename T>
	concept argTypedRValue = std::same_as<T, TokenType> || std::same_as<T, size_t> || std::same_as<T, int>;

	class AsmBuilder {
	private:
		struct Variable {
			size_t start;
			size_t size;
		};

		Lexer::token_row_t tk;
		std::unordered_map<const char*, Variable> vars;
		StackListener<512U> stl;
	public:
		AsmBuilder() {}
		
		void declareVariable(const char* name, size_t size = 4) {
			size_t start = stl.assign(size);
			MewUserAssert(start != -1, "stack overflow");
			Variable var {
				.start = start,
				.size = size
			};
			vars.insert({name, var});
		}

		void assignVariable(const char* name, int value) {
			auto var_ = vars.find(name);
			MewUserAssert(var_ != vars.end(), "undefined variable");
			Move(var_->second.start, value);
		}

		void freeVariable(const char* name) {
			auto var_ = vars.find(name);
			MewUserAssert(var_ != vars.end(), "undefined variable");
			stl.free(var_->second.start, var_->second.size);
			vars.erase(var_);
		}

		void PushArg(Lexer::tokens_t& tkr, TokenType reg) {
			tkr.push({reg});
		}
		void PushArg(Lexer::tokens_t& tkr, size_t rdi_offset) {
			tkr.push({TokenType::RdiOffset, (char*)rdi_offset});
		}
		void PushArg(Lexer::tokens_t& tkr, int number) {
			tkr.push({TokenType::Number, (char*)number});
		}
		
		template<argTypedLValue T, argTypedRValue K>
		void Operation(TokenType tkt, T a, K b) {
			Lexer::tokens_t tkr;
			tkr.push({tkt});
			PushArg(tkr, a);
			PushArg(tkr, b);
			tk.push(tkr);
		}

		template<argTypedLValue T>
		void Operation(TokenType tkt, T a) {
			Lexer::tokens_t tkr;
			tkr.push({tkt});
			PushArg(tkr, a);
			tk.push(tkr);
		}

		void Operation(TokenType tkt) {
			Lexer::tokens_t tkr;
			tkr.push({tkt});
			tk.push(tkr);
		}
		
		template<argTypedLValue T, argTypedRValue K>
		void Push(T a, K b) { Operation(TokenType::Push, a, b); }
		
		void Pop() { Operation(TokenType::Pop); }

		template<argTypedLValue T>
		void Rpop(T a) { Operation(TokenType::Rpop, a); }

		template<argTypedLValue T, argTypedRValue K>
		void Add(T a, K b) { Operation(TokenType::Add, a, b); }

		template<argTypedLValue T, argTypedRValue K>
		void Sub(T a, K b) { Operation(TokenType::Sub, a, b); }

		template<argTypedLValue T, argTypedRValue K>
		void Mul(T a, K b) { Operation(TokenType::Mul, a, b); }

		template<argTypedLValue T, argTypedRValue K>
		void Div(T a, K b) { Operation(TokenType::Div, a, b); }

		template<argTypedLValue T, argTypedRValue K>
		void Inc(T a) { Operation(TokenType::Inc, a); }

		template<argTypedLValue T, argTypedRValue K>
		void Dec(T a) { Operation(TokenType::Dec, a); }

		template<argTypedLValue T, argTypedRValue K> 
		void Move(T a, K b) { Operation(TokenType::Mov, a, b); }

		
		Code* build(const char* filename = "local") {
			constexpr bool has_normal_err = true;
			Lexer lex(tk, filename, has_normal_err);
			Parser par(lex);
			Compiler comp(lex);
			Code* code = comp.gen_code();
			return code;
		}
	};
	
};


#endif