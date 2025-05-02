#ifndef NANLER_HPP
#define NANLER_HPP

#define MEWALL_NO_WIN_ALIASES
#include "mewlib.h"
#include "mewstack.hpp"
#include "asm.hpp"
#include "asmlib.hpp"
#include "shell.hpp"
#include "binarypack.hpp"
#include "mewcod.hpp"

#pragma pack(push, 1)

namespace compiler::nan {
	enum struct TokenType {
		// simple type
		Undefined,
		None, String, Number, Text,	Colon, Dot, Comma, Semicolon, DoubleColon,
		Float, Double, Int, Char, ETC,
		Use, Extern, Expand, Narrow, Class, Struct, Entry,
		If, Else, Ret, Flag,
		RoundArray, SquareArray, TriangleArray, Block,
		// operators
		Minus, Plus, Equal, Multiply, Divide,
		// commands
		Add, Sub, Mul, Div, Inc, Dec, Xor, Or, 
		Not, And, Ls, Rs,

		LogicOr, LogicAnd, 

		RoundOpenBracket, RoundCloseBracket,
		SquareOpenBracket, SquareCloseBracket,
		TriangleOpenBracket, TriangleCloseBracket,
		FigureOpenBracket, FigureCloseBracket,
		For, While,
	};

	static std::unordered_map<const char *, TokenType> tokens = {
		{":", TokenType::Colon},
		{";", TokenType::Semicolon},
		{"::", TokenType::DoubleColon},
		{"-", TokenType::Minus},
		{"+", TokenType::Plus},
		{"++", TokenType::Inc},
		{"--", TokenType::Dec},
		{"=", TokenType::Equal},
		{"*", TokenType::Multiply},
		{"/", TokenType::Divide},
		{"!", TokenType::Not},
		{"|", TokenType::Or},
		{"^", TokenType::Xor},
		{"&", TokenType::And},
		{">>", TokenType::Rs},
		{"<<", TokenType::Ls},
		{"||", TokenType::LogicOr},
		{"&&", TokenType::LogicAnd},
		{"(", TokenType::RoundOpenBracket},
		{")", TokenType::RoundCloseBracket},
		{"[", TokenType::SquareOpenBracket},
		{"]", TokenType::SquareCloseBracket},
		{"<", TokenType::TriangleOpenBracket},
		{">", TokenType::TriangleCloseBracket},
		{"{", TokenType::FigureOpenBracket},
		{"}", TokenType::FigureCloseBracket},
		{"if", TokenType::If},
		{"else", TokenType::Else},
		{"ret", TokenType::Ret},
		{"use", TokenType::Use},
		{"extern", TokenType::Extern},
		{"expand", TokenType::Expand},
		{"narrow", TokenType::Narrow},
		{"class", TokenType::Class},
		{"struct", TokenType::Struct},
		{"entry", TokenType::Entry},
		{"...", TokenType::ETC},
		{"float", TokenType::Float},
		{"double", TokenType::Double},
		{"int", TokenType::Int},
		{"char", TokenType::Char},
		{"string", TokenType::String},
		{"for", TokenType::For},
		{"while", TokenType::While},
	};

	struct FunctionDeclaration;
	struct Context;
	struct TypeContext;
	struct FieldFlag;
	struct TypeHandler;

	typedef void(*flag_handler_t)(FieldFlag& self, FunctionDeclaration& data);
	typedef void(*type_handler_t)(TypeHandler& self);

	struct NameContext {
		const char* name;
		mew::stack<const char*>* path;
	};

	struct NativeHandler {
		void* handler;
	};

	struct InCodeHandler { // in dev
		FunctionDeclaration* handler;
	};

	struct TypeHandler {
		NameContext* name;
		bool is_native;
		union {
			NativeHandler native_handler;
			InCodeHandler in_code_handler;
		};
	};

	struct FieldFlag {
		NameContext* name;
		bool is_native;
		union {
			NativeHandler native_handler;
			InCodeHandler* in_code_handler;
		};
	};

	struct Line {
		mew::stack<Context> row;
	};

	struct SquareArray {
		mew::stack<Context> args;
	};
	
	struct FunctionDeclaration {
		NameContext* name;
		SquareArray args;
		TypeContext* return_type;
		mew::stack<FieldFlag*> flags;
		mew::stack<Line> content;
	};

	struct FunctionCall {
		NameContext* name;
		SquareArray args;
		FunctionDeclaration* fn;
	};

	enum struct ContextType {
		/*(token types)*/
		Undefined,
		None, String, Number, Text,	Colon, Dot, Comma, Semicolon, DoubleColon,
		Float, Double, Int, Char, ETC,
		Use, Extern, Expand, Narrow, Class, Struct, Entry,
		If, Else, Ret, Flag,
		RoundArray, SquareArray, TriangleArray, Block,
		// operators
		Minus, Plus, Equal, Multiply, Divide,
		// commands
		Add, Sub, Mul, Div, Inc, Dec, Xor, Or, 
		Not, And, Ls, Rs,

		LogicOr, LogicAnd, 
		
		RoundOpenBracket, RoundCloseBracket,
		SquareOpenBracket, SquareCloseBracket,
		TriangleOpenBracket, TriangleCloseBracket,
		FigureOpenBracket, FigureCloseBracket,
		For, While,
		/*(additional types)*/
		FunctionCall,
		FunctionDeclaration,
		DeclareContext,
		InitContext,
		AssignContext,
		IfContext,
		ForContext,
		WhileContext,
		LROperatorContext,
		RIncContext, LIncContext, LDecContext, RDecContext, 
		LStarContext, RStarContext, LAmperContext, RAmperContext,
		LTildeContext, RTildeContext,
		MacrosContext, ReturnContext,
		EtcContext,
		Line,
		OperatorContext,
		MathContext,
		SizeofContext,
		RangeContext,
		SizeofContext2,
		CallContext,
		StructContext,
		EnumContext,
		TypeLimitterContext,
		TypeContext,
		GenericContext,
		ClassContext,
		ExpressionContext,
		NameContext,
		UsingContext,
		ResultContext,
	};
	
	struct Context {
		ContextType type;
		void* data;
	};

	struct ForContext {
		Context* init;
		Context* condition;
		Context* step;
		Context* body;
	};

	struct WhileContext {
		Context* condition;
		Context* body;
	};
	
	struct IfContext {
		Context* condition;
		Context* body;
		Context* else_body;
	};

	struct DeclareContext {
		Context* type;
		Context* name;
	};
	
	struct InitContext {
		Context* type;
		Context* name;
		Context* value;
	};
	
	struct AssignContext {
		Context* name;
		Context* value;
	};

	struct OperatorContext {
		Context* left;
		ContextType operator_type;
		Context* right;
	};

	struct MathContext {
		mew::stack<Context*> row;
	};

	struct SizeofContext {
		const char* type_name;
	};

	struct RangeContext {
		size_t start;
		size_t end;
	};
	
	struct SizeofContext2 {
		const char* type_name;
		RangeContext* memory_range;
	};

	struct CallContext {
		Context* name;
		SquareArray args;
	};

	struct StructContext {
		Context* name;
		mew::stack<Context*> fields;
	};

	struct EnumContext {
		Context* name;
		mew::stack<Context*> fields;
	};

	struct TypeLimitterContext {
		Context* name;
		bool is_inheritance = false;
		mew::stack<Context*> same_types;
	};

	struct TypeContext {
		Context* name;
		Context* clear_name;
		bool has_limiter: 1 = false;
		bool is_pointer: 1 = false;
		bool is_reference: 1 = false;
		bool is_template: 1 = false;
		bool is_const: 1 = false;
		bool is_constexpr: 1 = false;
		bool is_void: 1 = false;
		mew::stack<Context*> limiters;
	};

	struct GenericContext {
		mew::stack<TypeContext*> types;
	};

	struct ClassContext {
		Context* name;
		bool is_static = true;
		mew::stack<Context*> fields;
		mew::stack<Context*> methods;
		GenericContext* generic;
	};

	/**
	 * 
	 */
	struct EtcContext {
		Context* name;
		mew::stack<Context*> args;
	};

	/*
		Macros is function when preprocessing;
		Can't use global variable if it not constexpr (global preprocess constant)
		syntax:
			macros sum(numeric arg1, numeric arg2) {
				return arg1 + arg2;
			}

			int a = 1;
			int b = 10;
			int c = sum(a, b);
		
	*/

	struct ResultContext {
		enum struct Status: byte {
			OK, Error
		} status;
		const char* message = nullptr;
	};
	
	struct MacrosContext {
		Context* name;
		SquareArray args;
		mew::stack<Line*> body;
	};

	struct ReturnContext {
		ContextType type;
		Context* value;
	};

	struct LROperatorContext {
		Context* name;
	};

	struct LROperatorNamedContext {
		Context* name;
		Context* value;
	};

	typedef LROperatorContext 
			RIncContext, LIncContext,
			LDecContext, RDecContext, 
			LStarContext, RStarContext,
			LAmperContext, RAmperContext,
			LTildeContext, RTildeContext;

	struct GenericExpression {
		NameContext* name;
		mew::stack<TypeContext*> types;
	};
	
	struct ExpressionContext {
		enum struct ExpressionType {
			Generic,
		} type;
		
		union {
			GenericExpression* generic_expression;
		};
	};

	struct UsingContext {
		bool is_default: 1 = false;
		ExpressionContext* expression;
	};

	typedef mew::cad::Compiler<TokenType>::Token Token;
	typedef mew::cad::Compiler<compiler::nan::TokenType>::Lexer Lexer;

	bool TokenWatcher(Token& tk) {
		
	}
	
	void Compile(const char* text, const char* file_name = "local") {
		mew::cad::Compiler<TokenType> compiler(tokens);
		auto* lexer = compiler.tokenize(compiler, text, TokenWatcher, file_name, true);
	}

	#define New(type, name) type* name = new type

	class Parser {
	private:
		Lexer& lexer;
		mew::stack<Context*> contexts;
		mew::stack<Context*> row;
		typedef mew::cad::Compiler<TokenType>::tokens_t TokenRow;
		mew::stack<const char*>* current_path;
		int current_line = 0;
		int current_column = 0;
	public:
	
		void ScreamError(const char* msg) {
			MewUserAssert(false, msg);
		}

		Parser(Lexer& lexer): lexer(lexer) {}

		Token& nextToken() {
			if (current_column >= lexer.token_row[current_line].count()) {
				current_column = 0;
				++current_line;
			}
			if (current_line >= lexer.token_row.count()) {
				ScreamError("End of file reached");
			}
			return lexer.token_row[current_line][current_column++];
		}

		Token& curToken() {
			return lexer.token_row[current_line][current_column];
		}

		void PastToken() {
			if (current_column == 0) {
				ScreamError("No token to past");
			}
			--current_column;
			if (current_column < 0) {
				current_column = 0;
				--current_line;
			}
			if (current_line < 0) {
				ScreamError("No token to past");
			}
		}

		void PastToken(size_t times) {
			for (size_t i = 0; i < times; ++i) {
				PastToken();
			}
		}

		bool SkipKeywords(std::initializer_list<TokenType> keywords) {
			int counter = 0;
			for (auto& kw : keywords) {
				++counter;
				auto& word = nextToken();
				if (word.type != kw) {
					PastToken(counter); 
					return false;
				}
			}
			return true;
		}

		bool Expand() {
			if (!SkipKeywords({TokenType::Expand, TokenType::Class, TokenType::Text})) {
				return false;
			}
			auto& word = curToken();
			current_path->push(word.value);
			return true;
		}
		
		bool Narrow() {
			if (!SkipKeywords({TokenType::Narrow, TokenType::Text})) {
				return false;
			}
			auto& word = curToken();
			current_path->push(word.value);
			return true;
		}
		
		bool Name() {
			auto& current = nextToken();
			if (current.type != TokenType::Text) {return false;}
			New(NameContext, name_ctx);
			name_ctx->name = current.value;
			name_ctx->path = current_path->copy();
			New(Context, ctx);
			ctx->type = ContextType::NameContext;
			ctx->data = name_ctx;
			row.push(ctx);
			return true;
		}

		void Expression() {

		}
		
		void fillLines() {
			// for (int i = 0; i < lexer.token_row.count(); ++i) {
			// 	auto& line = lexer.token_row[i];
			// 	Expression(line);
			// }
		}

		
		void parse() { fillLines(); }

		
	};

	
}
#pragma pack(pop)


#endif