#include "parser_declaratins.hpp"
#pragma once

namespace nanler::Parser {

Operator::Operator(ParserContainer &con): con(con) { }

bool Operator::parse() {
	con.record();
	auto first = *con.next();
	if (first.type < TokenType::Minus || first.type > TokenType::Rs) {
		++con.next();
		auto name = Expression::parse(con);
		if (!name) { return con.undo(); }
		ctx = new OperatorContext();
		ctx->left = nullptr;
		ctx->operator_type = (ContextType)(((int)TokenType::Minus - (int)first.type)+(int)ContextType::Minus);
		ctx->right = Context::wrap(name);
		con.discard();
		return true;
	}
	auto left = Expression::parse(con);
	if (!left) return con.undo();
	auto op = *con.next()++;
	if (!(op.type < TokenType::Minus || op.type > TokenType::Rs)) return con.undo();
	auto right = Expression::parse(con);
	// if (!right) return con.undo(); // discard 
	ctx = new OperatorContext();
	ctx->left = Context::wrap(left);
	ctx->operator_type = (ContextType)(((int)TokenType::Minus - (int)op.type)+(int)ContextType::Minus);
	ctx->right = Context::wrap(right);
	con.discard();
	return true;
}

OperatorContext* Operator::parse(ParserContainer &con) {
	Operator e(con);
	return !e.parse() ? nullptr : e.ctx;
}

}