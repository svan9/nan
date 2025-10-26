#include "parser_declaratins.hpp"
#pragma once

namespace nanler::Parser {

ArrayInRound::ArrayInRound(ParserContainer &con): con(con) { }

bool ArrayInRound::parse() {
	con.record();
	if ((*con.next()++).type != TokenType::RoundOpenBracket) {
		return con.undo();
	}
	ctx = new SquareArray();
	while ((*con.next()++).type != TokenType::RoundCloseBracket) {
		auto expr = Expression::parse(con);
		if (!expr) {
			con.error("failed to parse square array, expected expression or ')'");
			return con.undo();
		}
		ctx->args.push(Context::wrap(expr));
	}
	ctx->type = SquareArray::Type::Square;
	con.discard();
	return true;
}

SquareArray* ArrayInRound::parse(ParserContainer &con) {
	ArrayInRound e(con);
	return !e.parse() ? nullptr : e.ctx;
}

}