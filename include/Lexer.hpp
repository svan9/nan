#ifndef __LEXER__NAN__
#define __LEXER__NAN__

#include <Token.hpp>
#include <Config.hpp>
#include <string>
#include <vector>

class Lexer {
public:
	enum TokenTypes:
		short {
			SEMICOLON, COLON, NUMBER, STRING, TEXT, 
			OPEN_SQ, /*[*/ CLOSE_SQ, /*]*/
			OPEN_RN, /*(*/ CLOSE_RN, /*)*/
			OPEN_TR, /*<*/ CLOSE_TR, /*>*/
			OPEN_FG, /*{*/ CLOSE_FG, /*}*/
			DOT, COMMA, GRID, PERCENT, UP,
			ATSIGN, EM, QM, EQUAL, PLUS,
			MINUS, AND, OR, SLASH, BSLASH,
			STAR, DL, AP, SQUOTE,
	};
typedef std::vector<Token>::iterator iterator;
private:
	std::vector<Token> tokens;
	std::string::const_iterator it;
	std::string::const_iterator end;
	bool after_space = false;
public:
	////////////////////////////////////////////////////////////
	Lexer() { }

	////////////////////////////////////////////////////////////
	void append(short type, std::string& value) {
		Token tk(type, value);
		tk.after_space(after_space);
		tokens.push_back(tk);
	}

	////////////////////////////////////////////////////////////
	void append(TokenTypes type, std::string& value) {
		Token tk(static_cast<short>(type), value);
		tk.after_space(after_space);
		tokens.push_back(tk);
	}

	////////////////////////////////////////////////////////////
	void append(TokenTypes type, char value) {
		std::string str;
		str+=value;
		Token tk(static_cast<short>(type), str);
		tk.after_space(after_space);
		tokens.push_back(tk);
	}

	////////////////////////////////////////////////////////////
	void append(TokenTypes type) {
		Token tk(static_cast<short>(type));
		tk.after_space(after_space);
		tokens.push_back(tk);
	}

	////////////////////////////////////////////////////////////
	void lex_space() {
		while (it != end && is_lex_type(SPACE, *it)) {
			it++; // just skip
		}
		after_space = true;
	}

	////////////////////////////////////////////////////////////
	constexpr iterator begin() noexcept {
		return tokens.begin();
	}

	////////////////////////////////////////////////////////////
	constexpr iterator end() noexcept {
		return tokens.end();
	}
	
	////////////////////////////////////////////////////////////
	void lex_string() {
		std::string str;
		while (it != end && 
			!is_lex_type(STRING, *it) &&
			*(it-1) != '\\'
		) {
			if (*(it) == '\\') { it++; }
			else { str += *(it++); }
		}
		append(STRING, str);
		after_space = false;
	}

	////////////////////////////////////////////////////////////
	void lex_text() {
		std::string str;
		while (it != end && 
			!is_lex_type(SPECIAL, *it) &&
			!is_lex_type(SPACE, *it)
		) {
			str += *(it++);
		}
		append(TEXT, str);
		after_space = false;
	}


	////////////////////////////////////////////////////////////
	void lex(const std::string& string) {
		it = string.begin();
		end = string.end();
		while (it != end) {
			char c = *(it++);
			if (is_lex_type(SPACE, c))
				lex_space();
			else
			if (is_lex_type(STRING, c)) 		// "(~(")*)"
				lex_string();
			else lexer_ifis(SEMICOLON, c) 	// ;
			else lexer_ifis(COLON, c) 			// :
			else lexer_ifis(OPEN_SQ, c)			// [
			else lexer_ifis(OPEN_RN, c)			// (
			else lexer_ifis(OPEN_TR, c)			// <
			else lexer_ifis(OPEN_FG, c)			// {
			else lexer_ifis(CLOSE_SQ, c)		// ]
			else lexer_ifis(CLOSE_RN, c)		// )
			else lexer_ifis(CLOSE_TR, c)		// >
			else lexer_ifis(CLOSE_FG, c)		// }
			else lexer_ifis(DOT, c)					// .
			else lexer_ifis(COMMA, c)				// ,
			else lexer_ifis(GRID, c)				// #
			else lexer_ifis(PERCENT, c)			// %
			else lexer_ifis(UP, c)					// ^
			else lexer_ifis(ATSIGN, c)			// @
			else lexer_ifis(EM, c)					// !
			else lexer_ifis(QM, c)					// ?
			else lexer_ifis(EQUAL, c)				// =
			else lexer_ifis(PLUS, c)				// +
			else lexer_ifis(MINUS, c)				// -
			else lexer_ifis(AND, c)					// &
			else lexer_ifis(OR, c)					// |
			else lexer_ifis(SLASH, c)				// "\"
			else lexer_ifis(BSLASH, c)			// /
			else lexer_ifis(STAR, c)				// *
			else lexer_ifis(DL, c)					// $
			else lexer_ifis(AP, c)					// `
			else lexer_ifis(SQUOTE, c)			// '
			else lex_text();
		}
	}

};

#endif