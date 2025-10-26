#ifndef NANLER_PARSER_DECL
#define NANLER_PARSER_DECL
#pragma once
#define MEWSTACK_USE_STD_VECTOR
#include "Config.hpp"
#include "mewstack.hpp"
#include "Lexer.hpp"
#include <unordered_map>
// #include "asmlib.hpp"

namespace nanler::Parser {

#pragma region header
	typedef Lexer::Lexer::token_line_t token_row_t;

	struct OperatorHandler
	{
		enum struct OperatorType
		{
			Left,
			Right,
			Both
		} type;
		float order;

		FunctionDeclaration *handler;
	};

	typedef std::unordered_map<TokenType, OperatorHandler> operator_map_t;
	typedef std::unordered_map<const char*, FunctionDeclaration> function_map_t;
	typedef std::unordered_map<const char *, nanler::TypeContext> variable_map_t;
	typedef std::unordered_map<const char *, nanler::TypeContext*> types_map_t;

	struct ErrorStatus {
		bool has_error = false;
		size_t line = 0;
		size_t column = 0;
		const char *error_message = nullptr;

		operator bool() const noexcept
		{
			return has_error;
		}
	};

#define GetLastContextFrom(_src, type) ((type *)(_src).top().data)
#define RGetLastContextFrom(_src, type) ((type *)(_src).top())
#define GetLastContext(type) ((type *)parser.contexts.top().data)
#define LastBlockNotDone() parser.contexts.top().type == ContextType::BlockContext && !GetLastContext(BlockContext)->is_closed
#define GetLastLineInBlock() (GetLastContext(BlockContext)->lines.top())
#define LastLineInBlockNotDone() (LastBlockNotDone() && !GetLastLineInBlock().is_done)
#define SmartContextPush(ptr_ctx, type)                     \
	if (LastLineInBlockNotDone())                             \
	{                                                         \
		GetLastLineInBlock().push(RMakeContext(type, ptr_ctx)); \
	}                                                         \
	else                                                      \
	{                                                         \
		parser.contexts.push(RMakeContext(type, ptr_ctx));      \
	}
#define RSmartContextPush(type)                       \
	if (LastLineInBlockNotDone())                       \
	{                                                   \
		GetLastLineInBlock().row.push(MakeContext(type)); \
	}                                                   \
	else                                                \
	{                                                   \
		parser.contexts.push(MakeContext(type));          \
	}

	struct Parser {
		size_t token_cursor = 0;
		mew::stack<Context> contexts;

		ErrorStatus error_status;

		function_map_t function_map;
		operator_map_t operator_map;
		variable_map_t variable_map;
		types_map_t types_map;

		bool var_isExist(const char *name) const noexcept {
			return variable_map.find(name) != variable_map.end();
		}

		TypeContext *var_getType(const char *name) {
			auto it = variable_map.find(name);
			if (it != variable_map.end()) {
				return &it->second;
			}
			return nullptr;
		}
	};

	class ParserContainer {
	private:
		Parser &parser;
		mew::stack<u64> lasts;
		Lexer::Next it;
		mew::stack<NameContext*> path;
		GenericContext *template_ctx = nullptr;
	public:
		ParserContainer(Parser &parser, Lexer::Next &it): parser(parser), it(it) { }
		ParserContainer(Parser &parser, Lexer::Lexer &lexer): parser(parser), it(lexer) { }

		void expand(NameContext* name, GenericContext *ctx = nullptr) {
			path.push(name);
			this->template_ctx = ctx;
		}

		mew::stack<const char*>* getPath() {
			mew::stack<const char*> result;
			for (auto &name : path) {
				result.push(name->name);
			}
			return result.copy();
		}

		void narrow(NameContext* name = nullptr) {
			if (name == nullptr) {
				path.pop();
				return;
			}
			for (int i = 0; i < path.count(); ++i) {
				if (mew::strcmp(path[i]->name, name->name)) {
					path.pop();
					return;
				}
				path.pop();
			}
		}

		void record() {
			lasts.push(it.getId());
		}

		bool undo() {
			auto last = lasts.pop();
			it.replace(last);
			return false;
		}

		void discard() {
			lasts.erase();
		}
		
		Lexer::Next& next() {
			return it;
		}

		TypeContext* getType(const char* name) {
			auto it = parser.types_map.find(name);
			if (it != parser.types_map.end()) {
				return it->second;
			}
			return nullptr;
		}

		void putType(const char* name, TypeContext* ctx) {
			parser.types_map[name] = ctx;
		}

		u64 _calcSize(const char* type_name) {
			u64 size = 0;
			auto it = parser.types_map.find(type_name);
			if (it == parser.types_map.end()) {
				return -1;
			}
			TypeContext* type_ctx = it->second;
			if (type_ctx->is_void) {
				return 0;
			}
			if (type_ctx->is_pointer || type_ctx->is_reference) {
				return sizeof(void*);
			}
			if (type_ctx->size != 0) {
				return type_ctx->size;
			}
			if (type_ctx->ref_struct) {
				for (auto& field : type_ctx->ref_struct->fields) {
					if (!field || !field->type) continue;
					size += _calcSize(field->type->name->get<NameContext>()->fullName());
				}
				return size;
			}
			return size;
		}

		void putStruct(StructContext* ctx) {
			//! ignore double declaration , will redeclare struct
			// if (getType(ctx->name->get<NameContext>()->fullName())) {
			// 	parser.error_status.has_error = true;
			// 	parser.error_status.error_message = "Struct already declared";
			// 	return;
			// }
			TypeContext* type_ctx = new TypeContext();
			type_ctx->name = ctx->name;
			type_ctx->clear_name = ctx->name;
			type_ctx->is_template = ctx->generic != nullptr;
			type_ctx->is_void = false;
			type_ctx->size = 0;
			for (int i = 0; i < ctx->fields.count(); ++i) {
				auto field = ctx->fields[i];
				if (!field) continue;
				if (field->type->size != 0) {
					type_ctx->size += field->type->size;
				} else {
					auto field_size = _calcSize(field->type->name->get<NameContext>()->fullName());
					if (field_size == -1) {continue;}
					type_ctx->size += field_size;
				}
				// type_ctx->limiters.push(field);
			}
			type_ctx->ref_struct = ctx;
			const char* name = ctx->name->get<NameContext>()->fullName();
			parser.types_map[name] = type_ctx;
		}

		void declFunction(FunctionDeclaration &decl) {
			const char *name = FunctionDeclaration::parseName(&decl);
			if (parser.function_map.find(name) != parser.function_map.end()) {
				parser.error_status.has_error = true;
				parser.error_status.error_message = "Function already declared";
				return;
			}
			parser.function_map[name] = decl;
		}

		FunctionDeclaration* findFunction(const char *name) {
			auto it = parser.function_map.find(name);
			if (it != parser.function_map.end()) {
				return &it->second;
			}
			parser.error_status.has_error = true;
			parser.error_status.error_message = "Function not found";
			return nullptr;
		}

		bool validFunctionArgs(const char *name, FunctionCall* call) {
			FunctionDeclaration* decl = findFunction(name);
			if (!decl) {
				parser.error_status.has_error = true;
				parser.error_status.error_message = "Function not found";
				return false;
			}
			if (decl->args.args.count() != call->args.args.count()) {
				parser.error_status.has_error = true;
				parser.error_status.error_message = "Function argument count mismatch";
				return false;
			}
			if (call->generic && decl->template_ctx) {
				if (call->generic->types.count() != decl->template_ctx->types.count()) {
					parser.error_status.has_error = true;
					parser.error_status.error_message = "Function template argument count mismatch";
					return false;
				}
			} else if (call->generic || decl->template_ctx) {
				parser.error_status.has_error = true;
				parser.error_status.error_message = "Function template argument mismatch";
				return false;
			}
			for (size_t i = 0; i < decl->args.args.count(); ++i) {
				auto decl_arg = decl->args.args[i];
				auto call_arg = call->args.args[i];
				if (decl_arg.type != call_arg.type) {
					parser.error_status.has_error = true;
					parser.error_status.error_message = "Function argument type mismatch";
					return false;
				}
			}			
		}
		
		Lexer::Next next(int n) {
			return it+n;
		}
		
		void put(Context ctx) {
			parser.contexts.push(ctx);
		}

		void error(const char* message) {
			parser.error_status.error_message = message;
			parser.error_status.has_error = true;
		}
	};

#pragma endregion header

	// end of line
	inline bool EOL(ParserContainer &con) {
		auto tk = *con.next();
		if (tk.type == TokenType::Semicolon || con.next().isEnd()) {
			++con.next();
			return true;
		}
		return false;
	}

	inline bool EOB(ParserContainer &con) {
		auto tk = *con.next();
		if (tk.type == TokenType::FigureCloseBracket || con.next().isEnd()) {
			++con.next();
			return true;
		}
		return false;
	}

	class Name {
	private:
		NameContext* ctx;
		ParserContainer &con;
	public:
		Name(ParserContainer &con);
		bool parse();
		static NameContext* parse(ParserContainer &con);
	};

	class Type {
	private:
		TypeContext* ctx;
		ParserContainer &con;
	public:
		Type(ParserContainer &con);
		bool parse();
		static TypeContext* parse(ParserContainer &con);
	};

	class Assign {
	private:
		AssignContext* ctx;
		ParserContainer &con;
	public:
		Assign(ParserContainer &con);
		bool parse();
		static AssignContext* parse(ParserContainer &con);
	};

	class Block {
	private:
		BlockContext* ctx;
		ParserContainer &con;
	public:
		Block(ParserContainer &con);
		bool parse();
		static BlockContext* parse(ParserContainer &con);
	};

	class Operator {
	private:
		OperatorContext* ctx;
		ParserContainer &con;
	public:
		Operator(ParserContainer &con);
		bool parse();
		static OperatorContext* parse(ParserContainer &con);
	};

	class ArrayInRound {
	private:
		SquareArray* ctx;
		ParserContainer &con;
	public:
		ArrayInRound(ParserContainer &con);
		bool parse();
		static SquareArray* parse(ParserContainer &con);
	};

	class CallFunction {
	private:
		FunctionCall* ctx;
		ParserContainer &con;
	public:
		CallFunction(ParserContainer &con);
		bool parse();
		static FunctionCall* parse(ParserContainer &con);
	};

	class Return {
	private:
		ReturnContext* ctx;
		ParserContainer &con;
	public:
		Return(ParserContainer &con);
		bool parse();
		static ReturnContext* parse(ParserContainer &con);
	};

	class If_Else_Final {
	private:
		IfContext* ctx;
		ParserContainer &con;
	public:
		If_Else_Final(ParserContainer &con);
		bool parse();
		static IfContext* parse(ParserContainer &con);
	};

	class BinWutil {
	private:
		BinContext* ctx;
		ParserContainer &con;
	public:
		BinWutil(ParserContainer &con);
		bool parse();
		static BinContext* parse(ParserContainer &con);
	};

	class Template {
	private:
		GenericContext* ctx;
		ParserContainer &con;
	public:
		Template(ParserContainer &con);
		bool parse();
		static GenericContext* parse(ParserContainer &con);
	};

	class Flag {
	private:
		FieldFlag* ctx;
		ParserContainer &con;
	public:
		Flag(ParserContainer &con);
		bool parse();
		static FieldFlag* parse(ParserContainer &con);
	};

	class Function {
	private:
		FunctionDeclaration* ctx;
		ParserContainer &con;
	public:
		Function(ParserContainer &con);
		bool parse();
		static FunctionDeclaration* parse(ParserContainer &con);
	};

	class Incapsulate {
	private:
		IncapsulateContext* ctx;
		ParserContainer &con;
	public:
		Incapsulate(ParserContainer &con);
		bool parse();
		static IncapsulateContext* parse(ParserContainer &con);
	};

	class Trait {
	private:
		TraitContext* ctx;
		ParserContainer &con;
	public:
		Trait(ParserContainer &con);
		bool parse();
		static TraitContext* parse(ParserContainer &con);
	};

	class Typedef {
	private:
		TypeContext* ctx;
		ParserContainer &con;
	public:
		Typedef(ParserContainer &con);
		bool parse();
		static TypeContext* parse(ParserContainer &con);
	};

	class Expression {
	private:
		ExpressionContext* ctx;
		ParserContainer &con;
	public:
		Expression(ParserContainer &con);
		bool parse();
		static ExpressionContext* parse(ParserContainer &con);
	};

	class Namespace_expand {
	private:
		ParserContainer &con;
	public:
		Namespace_expand(ParserContainer &con);
		bool parse();
		static bool parse(ParserContainer &con);
	};

	class Namespace_narrow {
	private:
		ParserContainer &con;
	public:
		Namespace_narrow(ParserContainer &con);
		bool parse();
		static bool parse(ParserContainer &con);
	};

	class Namespace {
	private:
		ParserContainer &con;
	public:
		Namespace(ParserContainer &con);
		bool parse();
		static bool parse(ParserContainer &con);
	};

	class Structure {
	private:
		StructContext* ctx;
		ParserContainer &con;
	public:
		Structure(ParserContainer &con);
		bool parse();
		static StructContext* parse(ParserContainer &con);
	};

	class IternalName {
	private:
		NameContext* ctx;
		ParserContainer &con;
	public:
		IternalName(ParserContainer &con);
		bool parse();
		static NameContext* parse(ParserContainer &con);
	};

	class Extra {
	private:
		ExtraContext* ctx;
		ParserContainer &con;
	public:
		Extra(ParserContainer &con);
		bool parse();
		static ExtraContext* parse(ParserContainer &con);
	};

	class Line {
	private:
		LineContext* ctx;
		ParserContainer &con;
	public:
		Line(ParserContainer &con);
		bool parse();
		static LineContext* parse(ParserContainer &con);
	};

	class Program {
	private:
		mew::stack<LineContext*> m_lines;
		Parser &parser;
		Lexer::Lexer &lexer;
	public:
		Program(Parser &parser, Lexer::Lexer &lexer): parser(parser), lexer(lexer) 
			{ nexts(); }
	
		void nexts() {
			LineContext* l;
			ParserContainer con(parser, lexer);
			while ((l = Line::parse(con)) != nullptr) {
				m_lines.push(l);
			}
		}

		


	};

	
	inline void Parse(Parser &parser, Lexer::Lexer &lexer) {
		auto prog = Program(parser, lexer);
		
		// if (parser.error_status) {
		// 	printf("Error: `%s`", parser.error_status.error_message);
		// }
	}


}

#endif