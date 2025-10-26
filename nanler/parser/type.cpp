#include "parser_declaratins.hpp"
#pragma once

namespace nanler::Parser {

Type::Type(ParserContainer &con): con(con) { }

bool Type::parse() {
	auto tk = *con.next();
	if (tk.type != TokenType::Text) return false;
	++con.next();
	ctx = new TypeContext(tk.value);
	return true;
}

TypeContext* Type::parse(ParserContainer &con) {
	Type e(con);
	return !e.parse() ? nullptr : e.ctx;
}

}