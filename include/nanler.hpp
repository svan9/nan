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
		LTildeContext, RTildeContext
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
	};

	struct TypeContext {
		Context* name;
		Context* clear_name;
		bool has_limiter: 1 = false;
		bool is_pointer: 1 = false;
		bool is_reference: 1 = false;
		bool is_template: 1 = false;
		bool is_const: 1 = false;
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

	struct ReturnContext {
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

	bool TokenWatcher(Token& tk) {
		
	}
	
	void Compile(const char* text, const char* file_name = "local") {
		mew::cad::Compiler<TokenType> compiler(tokens);
		auto* lexer = compiler.tokenize(text, TokenWatcher, file_name, true);
	}
}
#pragma pack(pop)


#endif