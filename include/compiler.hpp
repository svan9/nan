#ifndef _NAN_COMPILER_IMPL
#define _NAN_COMPILER_IMPL

#include "mewall.h"
#include "nlohmann/json.hpp"
#include "virtuallib.hpp"

using json = nlohmann::json;
using Builder = Virtual::Lib::Builder;
using Range = Virtual::Lib::Arena::Range;

struct native_type_size {
	static const size_t _s__int 			= 4U;
	static const size_t _s__uint 			= 4U;
	static const size_t _s__long 			= 4U;
	static const size_t _s__longlong	= 8U;
	static const size_t _s__char	 		= 1U;
	static const size_t _s__bool	 		= 1U;
};

constexpr size_t _native_getTypeSize(const char* name) {
	if (name == "int") {
		return native_type_size::_s__int;
	} else if (name == "uint") {
		return native_type_size::_s__uint;
	} else if (name == "long") {
		return native_type_size::_s__long;
	} else if (name == "longlong") {
		return native_type_size::_s__longlong;
	} else if (name == "char") {
		return native_type_size::_s__char;
	} else if (name == "bool") {
		return native_type_size::_s__bool;
	}
	return 0;
} 

namespace CompilerStruct {
// 	struct NamedFunction {
// 		std::string name;
// 		std::string  rettype;
// 		std::string  flags;
// 		std::vector<std::string> args;
// 		std::vector<std::string> body;
// 	};
	struct BodyContext {
		std::unordered_map<std::string, Range> used_vars;
	};
}

class Compiler {
private:
	const char* rel_cache = ".nan/cache/temp.json";
	const char* cache = mew::utils::getUserHome(rel_cache);
	mew::stack<char*, 8U> used_function;
	std::unordered_map<std::string, json> named_functions;
	Builder main_builder;
	size_t entry;
	std::string current_function;
	CompilerStruct::BodyContext body_context;
public:
	Compiler() {}

	std::string generateFunctionName(std::string name, json& args) {
		if (args["array_type"] == "empty") {
			return name;
		}
		std::string out = "_";
		for (auto& arg: args["content"]) {
			out += arg["typename"].get<std::string>()[0];
		}
		out += '_';
		out += name;
		return out;
	}
	
	size_t apply_named_function(std::string name, json& content) {
		auto args = content["args"];
		auto rettype = content["rettype"];
		auto flags = content["flags"];
		auto body = content["body"];
		auto idx = main_builder.Cursor();
		main_builder.BeginFunction(name);
		body_context.used_vars.clear();
		for (auto& arg: body["content"]["content"]) {
			do_body(arg["content"]);
		}
		main_builder.EndFunction();
		return idx;
	}
	
	void do_named_function(json& content) {
		auto name = content["name"];
		auto args = content["args"];
		auto sname = name.get<std::string>();
		auto real_name = generateFunctionName(sname, args);
		current_function = real_name;
		named_functions[real_name] = content;
		size_t idx = apply_named_function(real_name, content);
	}


	void do_function_call(json& content) {
		auto real_name = generateFunctionName(content["name"], content["args"]);
		MewUserAssert(named_functions.find(real_name) != named_functions.end(), "undefined function");
		main_builder.CallFunction(real_name);		
	}

	void do_rvalue(json& content) {
		if (content["type"] == "function_call") {
			do_function_call(content);
		} else 
		if (content["type"] == "typename") {
			main_builder.Push(content["typename"].get<std::string>());
		}
	}

	void do_return(json& content) {
		if (current_function != "entry") {
			auto cur = named_functions[current_function];
			if (cur["rettype"]["typename"] != "void") {
				if (content["type"] == "rvalue") {
					do_rvalue(content["content"]);
				}
			}
		}
		main_builder.Ret();
	}

	void do_expr(json& content) {
		if (content["type"] == "rvalue") {
			do_rvalue(content["content"]);
		} else
		if (content["type"] == "return") {
			do_return(content["content"]);
		}
	}

	void do_body(json& content) {
		if (content["type"] == "expression") {
			do_expr(content["content"]);
		}
	}

	void do_entry(json& content) {
		body_context.used_vars.clear();
		current_function = "entry";
		for (auto& line: content["content"]) {
			do_body(line["content"]);
		}
	}

	void do_line(json& content) {
		auto content_type = content["type"];
		if (content_type == "named_function") {
			do_named_function(content);
		} else
		if (content_type == "entry") {
			do_entry(content);
		} 
	}

	void compile(json& data) {
		for (auto& line: data) {
			do_line(line["content"]);
		}
	}

	Builder& compile() {
		auto f = mew::getIfStream(cache);
		json data = json::parse(f);
		compile(data);
		main_builder.to_entry(entry);
		return main_builder;
	}

	Builder& compile(const char* path_to_src) {
		auto f = mew::getIfStream(path_to_src);
		json data = json::parse(f);
		compile(data);
		return main_builder;
	}
};

#endif