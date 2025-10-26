#ifndef LEXER_HPP
#define LEXER_HPP

#define MEWSTACK_USE_STD_VECTOR
#include "Token.hpp"
#include "mewstack.hpp"
#include "mewutils.hpp"

namespace nanler::Lexer {
	using namespace mew::utils;

	class Next;

	struct Lexer {
		typedef mew::stack<Token> token_line_t;
		token_line_t tokens;

		Next next();
	};

	class Next {
	private:
		u64 idx;
		Lexer& lexer;
	public:
		Next(u64 idx, Lexer& lexer): idx(idx), lexer(lexer) {}
		Next(Lexer& lexer): idx(0), lexer(lexer) {}
		
		Token& operator()() {
			return lexer.tokens.count() <= (idx+1)? *lexer.tokens.end(): lexer.tokens[(idx+1)];
		}

		Token& operator*() {
			return lexer.tokens.count() <= (idx+1)? *lexer.tokens.end(): lexer.tokens[(idx+1)];
		}

		Token& operator*(int) {
			return lexer.tokens.count() <= (idx+1)? *lexer.tokens.end(): lexer.tokens[(idx+1)];
		}

		bool isEnd() const noexcept {
			return idx >= lexer.tokens.count();
		}

		void confirm() {
			++idx;
		}

		Next& next() {
			++idx;
			return *this;
		}

		Next& operator++() {
			++idx;
			return *this;
		}

		Next operator++(int) {
			Next tmp(idx, lexer);
			++idx;
			return tmp;
		}

		Next operator+(int n) {
			Next tmp(idx + n, lexer);
			return tmp;
		}

		Next& operator+=(int n) {
			idx += n;
			return *this;
		}

		u64 getId() const noexcept {
			return idx;
		}

		void replace(u64 n) {
			this->idx = n;
		}

	};

	Next Lexer::next() {
		return Next(*this);
	}

	Token* GetTokenFromTable(const char* word) {
		bool is_find = false;
		for (auto it = token_semantic.begin(); it != token_semantic.end(); ++it) {
			if (mew::strcmp(it->first, word)) {
				Token* tk = new Token;
				tk->type = it->second;
				tk->value = nullptr;
				return tk;
			}
		}
		return nullptr;
	}

	void TokenizeLine(Lexer& lexer, const char* line) {
		TokenRow str_row(line);
		str_row.SkipToStart();
		const char* word;
		while ((word = *str_row++) != nullptr && *word != '\0') {
			if (mew::strcmp(word, "bin")) {
				Token tk = {
					.type = TokenType::Bin,
					.value = nullptr
				};
				word = *str_row++;
				if (!mew::strcmp(word, "{")) {
					lexer.tokens.push({
						.type = TokenType::Undefined,
						.value = "Syntax error: expected bin value"
					});
					continue;
				}
				mew::string::StringBuilder sb;
				while ((word = *str_row++) != nullptr && *word != '\0' && *word != '}') {
					sb.Append(word);
					sb.Append(' ');
				}
				tk.value = sb.c_str();
				lexer.tokens.push(tk);
				continue;
			}
			Token* _from_table = GetTokenFromTable(word);
			if (_from_table != nullptr) {
				lexer.tokens.push(_from_table);
				continue;
			}
			Token tk = {
				.type = TokenType::Undefined,
				.value = scopy(word)
			};
			lexer.tokens.push(tk);
		}
	}

	#define NumberToBytes(number) ((char*)(mew::byte*)&(number))
	#define BytesToNumberTypes(type, bytes) *(type*)((mew::byte*)(bytes))

	void WatchUndefinedTokens(Token& tk) {
		auto number = str_to_number(tk.value);
		tk.type = (TokenType)(number_to_tk(number)+(int)TokenType::NumberInt),
		tk.value = number_to_strv(number);

		if (*tk.value == '"' && getLastChar(tk.value) == '"') {
			tk.type = TokenType::String;
			mew::utils::fas(tk.value, (const char*)str_parse(tk.value+1, strlen(tk.value)-2));
			return;
		}
		tk.type = TokenType::Text;
	}

	void DecryptUndefinedTokens(Lexer& lexer) {
		for (int x = 0; x < lexer.tokens.count(); ++x) {
			auto& e = lexer.tokens[x];
			if (e.type == TokenType::Undefined) {
				WatchUndefinedTokens(e);
			}
		}
	}

	void Tokenize(Lexer& lexer, const char* text) {
		TokenizeLine(lexer, text);
		// auto lines = *splitLines(text);
		// for (int i = 0; i < lines.count(); ++i) {
		// }
	}

	void TestLexer() {
		Lexer lexer;
		const char* text = "\n"
			"int a = 1;\n"
			"float b = 2.0;\n"
			"double c = 3.0;\n"
			"char d = \"d\";\n"
			"string e = \"Hello, World!\";\n"
			"if (a == 1) {\n"
			"  b = b + 1;\n"
			"}\n"
			"else {\n"
			"  c = c - 1;\n"
			"}\n";
		Tokenize(lexer, text);
		DecryptUndefinedTokens(lexer);
		printf("[ ");
		for (int i = 0; i < lexer.tokens.count(); ++i) {
			auto& token = lexer.tokens[i];
			if (token.type == TokenType::NumberInt) {
				printf("{\"Type\": \"%s\", \"Value\": %i} ", StringifyTokenType(token.type), BytesToNumberTypes(int, token.value));
			} else 
			if (token.type == TokenType::NumberFloat) {
				printf("{\"Type\": \"%s\", \"Value\": %f} ", StringifyTokenType(token.type), BytesToNumberTypes(float, token.value));
			} else 
			if (token.type == TokenType::NumberDouble) {
				double number =  BytesToNumberTypes(double, token.value);
				printf("{\"Type\": \"%s\", \"Value\": %lf} ", StringifyTokenType(token.type), number);
			} else {
				if (token.value == nullptr) {
					printf("{\"Type\": \"%s\"} ", StringifyTokenType(token.type));
				} else {
					printf("{\"Type\": \"%s\", \"Value\": \"%s\"} ", StringifyTokenType(token.type), token.value);
				} 
			}
			if (i < lexer.tokens.count()-1) {
				printf(",\n");
			}
		}
		printf(" ]\n");
	}

}

#endif