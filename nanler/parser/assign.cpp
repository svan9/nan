#include "parser_declaratins.hpp"
#pragma once

namespace nanler::Parser {

Assign::Assign(ParserContainer &con): con(con) { }

bool Assign::parse() {
	con.record();
	auto type = Type::parse(con);
	if (!type) return con.undo();
	auto name = Name::parse(con);
	if (!name) return con.undo();
	if (EOL(con)) {
		con.discard();
		ctx = new AssignContext(type, name);
		return true;
	}
	if ((*con.next()++).type != TokenType::Equal) {
		con.error("failed assign initialization, bad symbol, expected '=' ");
		return con.undo();
	}
	auto expr = Expression::parse(con);
	if (!expr) {
		con.error("failed assign initialization, bad symbols, expected expression after '=' ");
		return con.undo();
	}
	con.discard();
	ctx = new AssignContext(type, name, Context::wrap(expr));
	return true;
}

AssignContext* Assign::parse(ParserContainer &con) {
	Assign e(con);
	return !e.parse() ? nullptr : e.ctx;
}

}