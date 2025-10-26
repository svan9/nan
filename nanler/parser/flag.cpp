#include "parser_declaratins.hpp"
#pragma once

namespace nanler::Parser {

Flag::Flag(ParserContainer &con): con(con) { }

bool Flag::parse() {
	con.record();
	auto tk = *con.next()++;
	if (tk.type != TokenType::Flag) { return con.undo(); }
	auto name = Name::parse(con);
	if (!ctx->name) return con.undo();
	auto __native = in_code_flags_map.find(name->name) ;
	if (__native != in_code_flags_map.end()) {
		con.discard();
		return __native->second;
	}
	ctx = new FieldFlag();
	ctx->name = name;
	ctx->is_native = false;
	// todo custom handler
	con.discard();
	return true;
}

FieldFlag* Flag::parse(ParserContainer &con) {
	Flag e(con);
	return !e.parse() ? nullptr : e.ctx;
}

}