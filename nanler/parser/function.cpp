#include "parser_declaratins.hpp"
#pragma once

namespace nanler::Parser {

Function::Function(ParserContainer &con): con(con) { }

bool Function::parse() {
	con.record();
	auto type = Type::parse(con);
	if (!type) return con.undo();
	auto name = Name::parse(con);
	if (!name) return con.undo();
	auto args = ArrayInRound::parse(con);
	if (!args) return con.undo();
	ctx = new FunctionDeclaration();
	auto flags = Flag::parse(con);
	while (flags) {
		ctx->flags.push(flags);
		flags = Flag::parse(con);
	}			
	auto block = Block::parse(con);
	if (!block) { return con.undo(); }
	ctx->name = name;
	ctx->return_type = type;
	ctx->args = *args;
	ctx->content = *block;
	con.discard();
	con.declFunction(*ctx);
	return true;
}

FunctionDeclaration* Function::parse(ParserContainer &con) {
	Function e(con);
	return !e.parse() ? nullptr : e.ctx;
}

}