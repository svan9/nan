#include "parser_declaratins.hpp"
#pragma once

namespace nanler::Parser {

Return::Return(ParserContainer &con): con(con) { }

bool Return::parse() {
	con.record();
	if ((*con.next()++).type != TokenType::Ret) {
		return con.undo();
	}
	ctx = new ReturnContext();
	auto expr = Expression::parse(con);
	if (!expr) { return (ctx->is_void = true); }
	ctx->value = Context::wrap(expr);
	con.discard();
	return true;
}

ReturnContext* Return::parse(ParserContainer &con) {
	Return e(con);
	return !e.parse() ? nullptr : e.ctx;
}

}