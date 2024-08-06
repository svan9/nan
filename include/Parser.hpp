#ifndef __PARSER__NAN__
#define __PARSER__NAN__

#include <vector>
#include <Token.hpp>
#include <Lexer.hpp>
#include <AST.hpp>

class Parser {
private:
	AST _M_ast;
	Lexer::iterator it;
	Lexer::iterator end;
public:
	////////////////////////////////////////////////////////////
	Parser() {}

	////////////////////////////////////////////////////////////
	AST& ast() noexcept {
		return _M_ast;
	}

	////////////////////////////////////////////////////////////
	Token& next() {
		return *(it++);
	}

	////////////////////////////////////////////////////////////
	void skip(int step = 1) {
		it += step;
	}

	////////////////////////////////////////////////////////////
	Token& see_next(int step = 1) {
		return *(it+step);
	}
	
	////////////////////////////////////////////////////////////
	void preproccessing() {

	}

	////////////////////////////////////////////////////////////
	void catch_number(Token& tk) {
		AST::Element_t __e_ast;
		__e_ast.add_option("type", "number");
		Token number = tk;
		std::string value;
		value += tk.value();
		// see fract's types
		if (see_next().is(".", false)) {
			if (see_next(2).is(Lexer::NUMBER, false)) {
				value += ".";	
				value += see_next(2).value();	
				skip(); // skip after '.'
			}
			skip(); // skip '.'
			__e_ast.add_option("mod", "float"); skip();
		}

		// see number modificators
		if (see_next().is_nocase("f", false)) {
			__e_ast.add_option("mod", "float"); skip();
		}
		if (see_next().is_nocase("d", false)) {
			__e_ast.add_option("mod", "double"); skip();
		} 
		if (see_next().is_nocase("i", false)) {
			__e_ast.add_option("mod", "integer"); skip();
		}
		if (see_next().is_nocase("u", false)) {
			__e_ast.add_option("mod", "unsigned"); skip();
		}
		else {
			__e_ast.add_option("mod", "integer");
		}
		__e_ast.add_option("value", value);
		_M_ast.append(__e_ast);
	}

	////////////////////////////////////////////////////////////
	void catch_16x_number(Token& tk) {
		Token number = tk;
		Token mod = see_next();
		// if (mod.is(Lexer::TEXT))
	}
	
	////////////////////////////////////////////////////////////
	void catch_expressions(Token& tk) {
		if (tk.is(Lexer::NUMBER)) {
			if (
				tk.is("0") &&
				see_next(1).is("x") &&
				see_next(2).is(Lexer::NUMBER)
			) {
				catch_16x_number(tk);
			} else {
				catch_number(tk);
			}
		}	
	}


	////////////////////////////////////////////////////////////
	void parse(Lexer& lexer) {
		it = lexer.begin();
		end = lexer.end();
		while (it != end) {
			Token tk = next();
			catch_expressions(tk);
		}
	}
};

#endif