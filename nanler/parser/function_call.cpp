#include "parser_declaratins.hpp"
#pragma once

namespace nanler::Parser {

CallFunction::CallFunction(ParserContainer &con): con(con) { }

bool CallFunction::parse() {
	con.record();
	auto name = Expression::parse(con);
	if (!name) return con.undo();
	auto args = ArrayInRound::parse(con);
	if (!args) return con.undo();
	ctx = new FunctionCall();
	ctx->name = Context::wrap(name);
	ctx->args = *args;
	con.discard();
	return true;
}

FunctionCall* CallFunction::parse(ParserContainer &con) {
	CallFunction e(con);
	return !e.parse() ? nullptr : e.ctx;
}

}