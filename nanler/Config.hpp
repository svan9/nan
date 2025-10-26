#ifndef CONFIG_HPP
#define CONFIG_HPP
#pragma once
#define MEWALL_NO_WIN_ALIASES
#include "mewlib.h"
#include "mewstack.hpp"
#include "mewtypes.h"
#include "mewstring.hpp"
#include "Token.hpp"
#include "Context.hpp"
#include "Defs.hpp"

#pragma pack(push, 1)

namespace nanler {
	u64 ParseTypeSize(TypeContext* type);
	#define MakeContext(name) Context{.type=ContextType::name, .data = (void*)(new name)}
	#define RMakeContext(name, value) Context{.type=ContextType::name, .data = (void*)(value)}

typedef void(*flag_handler_t)(FieldFlag& self, FunctionDeclaration& data);
typedef void(*type_handler_t)(TypeHandler& self);



	struct Context {
		ContextType type;
		void* data;

		Context() {}
		Context(ContextType type,
		void* data): type(type), data(data) {}

		template<typename T>
		static Context* wrap(ContextType type, T* data) {
			return new Context(type, data);
		}

		template<typename T>
		static Context* wrap(T* data) {
			if (!data) return nullptr;
			auto ctx = new Context();
			ctx->data = data;
			ctx->type = ContextTypeFromType<T>();
			return ctx;
		}

		template<typename T>
		T* get() const {
			return static_cast<T*>(data);
		}
	};

	struct NameContext {
		const char* name;
		mew::stack<const char*>* path;

		const char* fullName() const {
			if (!path || path->count() == 0) return name;
			mew::string::StringBuilder sb;
			sb.Append(name);
			for (const char* p : *path) {
				sb.Append("2");
				sb.Append(p);
			}
			return sb.c_str();
		}
	};

	NameContext* MakeNameContext(const char* name, mew::stack<const char*>* path = nullptr) {
		NameContext* ctx = new NameContext;
		ctx->name = name;
		ctx->path = path;
		return ctx;
	}


	struct NativeHandler {
		void* handler;
	};

	struct InCodeHandler { // in dev
		FunctionDeclaration* handler;
	};

	struct FieldFlag {
		NameContext* name;
		bool is_native;
		union {
			NativeHandler native_handler;
			InCodeHandler* in_code_handler;
		};
	};

	std::unordered_map<const char*, FieldFlag*> in_code_flags_map = {
		{"gen", new FieldFlag{MakeNameContext("gen"), true, {nullptr}}},
		{"copy", new FieldFlag{MakeNameContext("copy"), true, {nullptr}}},
		{"safe", new FieldFlag{MakeNameContext("safe"), true, {nullptr}}},
		{"nonpath", new FieldFlag{MakeNameContext("nonpath"), true, {nullptr}}},
		{"autogen", new FieldFlag{MakeNameContext("autogen"), true, {nullptr}}},
		{"right", new FieldFlag{MakeNameContext("right"), true, {nullptr}}},
		{"left", new FieldFlag{MakeNameContext("left"), true, {nullptr}}},
		{"native", new FieldFlag{MakeNameContext("native"), true, {nullptr}}},
		{"operator", new FieldFlag{MakeNameContext("operator"), true, {nullptr}}},
		{"move", new FieldFlag{MakeNameContext("move"), true, {nullptr}}}
	};

struct EntryContext {
	mew::stack<LineContext> lines;
};

struct BlockContext {
	mew::stack<LineContext> lines;
	bool is_closed = false;
};



struct ExtraContextField {
	NameContext* name;
	NameContext* value;
};

struct ExtraContext {
	NameContext* name;
	mew::stack<ExtraContextField> fields;
};

struct TypeHandler {
	NameContext* name;
	bool is_native;
	union {
		NativeHandler native_handler;
		InCodeHandler in_code_handler;
	};
};


struct LineContext {
	Context* expression;
};

struct SquareArray {
	enum Type {Square, Cubic, Triangle} type;
	mew::stack<Context*> args;
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
	ContextType refType;
	u64 size = 0;
	mew::stack<Context*> limiters;
	StructContext* ref_struct = nullptr;
	
	TypeContext() {}
	
	TypeContext(const char* name): name(Context::wrap(ContextType::Text, name)) {
		if (mew::strcmp(name, "int")) {
			size = 4;
			refType = ContextType::Int;
		}
		else if (mew::strcmp(name, "float")) {
			size = 4;
			refType = ContextType::Float;
		}
		else if (mew::strcmp(name, "double")) {
			refType = ContextType::Double;
			size = 8;
		}
		else if (mew::strcmp(name, "char")) {
			refType = ContextType::Char;
			size = 1;
		}
		else if (mew::strcmp(name, "bool")) {
			refType = ContextType::Char;
			size = 1;
		}
	}
};

TypeContext MakeTypeContext(const char* name, bool is_pointer = false, bool is_reference = false, bool is_const = false, bool is_constexpr = false, bool is_void = false) {
	TypeContext ctx;
	ctx.name = new Context{ContextType::Text, (void*)name};
	ctx.clear_name = ctx.name;
	ctx.is_pointer = is_pointer;
	ctx.is_reference = is_reference;
	ctx.is_const = is_const;
	ctx.is_constexpr = is_constexpr;
	ctx.is_void = is_void;
	return ctx;
}

struct GenericContext {
	mew::stack<TypeContext*> types;

	static const char* nameParseArgs(GenericContext* ctx) {
		if (!ctx || ctx->types.count() == 0) return "";
		mew::string::StringBuilder sb;
		for (auto& type : ctx->types) {
			sb.Append((const char*)type->name->data);
			sb.Append("1");
		}
		return sb.c_str();
	}
};

struct FunctionDeclaration {
	NameContext* name;
	GenericContext* template_ctx;
	SquareArray args;
	TypeContext* return_type;
	mew::stack<FieldFlag*> flags;
	BlockContext content;

	static const char* parseName(FunctionDeclaration* ctx) {
		if (!ctx->name) return nullptr;
		if (!ctx->name->path) { return ctx->name->name; }
		mew::string::StringBuilder sb;
		sb.Append(ctx->name->name);
		for (const char* path : *ctx->name->path) {
			sb.Append("2");
			sb.Append(path);
		}
		if (ctx->template_ctx) {
			sb.Append("1");
			sb.Append(GenericContext::nameParseArgs(ctx->template_ctx));
		}
		return sb.c_str();
	}
	const char* parseName() {
		parseName(this);
	}
};

struct FunctionCall {
	Context* name;
	SquareArray args;
	FunctionDeclaration* fn;
	GenericContext* generic;
};

struct OperatorDeclaration {
	Context* name;
	u8 operator_type; // 1 - left, 2 - right, 3 - both
	u8 r_important = 0;
	u8 l_important = 0;
	FunctionDeclaration* handler;
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
	SquareArray* condition;
	BlockContext* if_body;
	mew::stack<IfContext*> if_else_body;
	BlockContext* else_body;
	BlockContext* final_body;
};

struct BinContext {
	SquareArray* args;
	const char* value;
};

struct DeclareContext {
	Context* type;
	Context* name;
};

struct InitContext {
	TypeContext* type;
	NameContext* name;
	Context* value;
};

struct AssignContext {
	TypeContext* type;
	NameContext* name;
	Context* value;
	
	AssignContext(TypeContext* type, NameContext* name): name(name), type(type) {}
	AssignContext(TypeContext* type, NameContext* name, Context* value): name(name), type(type), value(value) {}
	AssignContext() {}

	static const char* parseName(AssignContext* ctx) {
		if (!ctx->name) return nullptr;
		if (!ctx->name->path) { return ctx->name->name; }
		mew::string::StringBuilder sb;
		sb.Append(ctx->name->name);
		for (const char* path : *ctx->name->path) {
			sb.Append("2");
			sb.Append(path);
		}
		return sb.c_str();
	}
	const char* parseName() {
		parseName(this);
	}
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
	mew::stack<AssignContext*> fields;
	GenericContext* generic;
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
	enum struct Status: mew::byte {
		OK, Error
	} status;
	const char* message = nullptr;
};

struct MacrosContext {
	Context* name;
	SquareArray args;
	mew::stack<LineContext*> body;
};

struct ReturnContext {
	Context* value;
	bool is_void: 1 = false;
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
	Context* row;
	
	void push(Context* ctx) {
		row = ctx;
	}

	
};

struct IncapsulateContext {
	ExpressionContext* left;
	ExpressionContext* right;
	enum struct Type {
		NONE, Pointer,
		Dynamic, Static,
	} type;
};

struct TraitContext {
	GenericContext* generic;
	NameContext* name;
	mew::stack<Context*> types;
};

struct UsingContext {
	bool is_default: 1 = false;
	ExpressionContext* expression;
};

u64 ParseTypeSize(TypeContext* type) {
	static std::unordered_map<const char*, u8> calculated;
	if (!type->size && type->ref_struct) {
		// todo add generic
		auto fields = type->ref_struct->fields;
		for (int i = 0; i < fields.count(); ++i) {
			auto field = fields[i];
			auto fnd = calculated.find(field->type->name->get<NameContext>()->fullName());
			if (fnd != calculated.end()) {
				type->size += fnd->second;
			} else {
				type->size += ParseTypeSize(field->type);
			}
		}
		const char* type_name = type->name->get<NameContext>()->fullName();
		calculated.insert({type_name, type->size});
	}
	return type->size;
}

}


#pragma pack(pop)
#endif