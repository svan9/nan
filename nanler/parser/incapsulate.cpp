#include "parser_declaratins.hpp"
#pragma once

namespace nanler::Parser {

Incapsulate::Incapsulate(ParserContainer &con): con(con) { }

bool Incapsulate::parse() {
	con.record();
	auto left = Expression::parse(con);
	if (!left) { return con.undo(); }
	ctx = new IncapsulateContext();
	ctx->left = left;
	if ((*con.next(1)).type != TokenType::Minus && 
		(*con.next(2)).type != TokenType::More) {
			ctx->type = IncapsulateContext::Type::Pointer;
		con.next() += 2; 
	} else if ((*con.next(1)).type == TokenType::Dot) { 
			ctx->type = IncapsulateContext::Type::Dynamic;
		con.next() += 1; 
	} else if ((*con.next(1)).type == TokenType::DoubleColon) {
			ctx->type = IncapsulateContext::Type::Static;
		con.next() += 1; 
	} else {
		return con.undo();
	}
	auto right = Expression::parse(con);
	if (!right) { return con.undo(); }
	ctx->right = right;
	con.discard();
	return true;
}

IncapsulateContext* Incapsulate::parse(ParserContainer &con) {
	Incapsulate e(con);
	return !e.parse() ? nullptr : e.ctx;
}

}