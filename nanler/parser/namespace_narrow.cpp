#include "parser_declaratins.hpp"
#pragma once

namespace nanler::Parser {

Namespace_narrow::Namespace_narrow(ParserContainer &con): con(con) { }

bool Namespace_narrow::parse() {
	con.record();
	auto tk = *con.next()++;
	if (tk.type != TokenType::Narrow) {
		return con.undo();
	}
	tk = *con.next()++;
	if (tk.type != TokenType::Class) {
		con.error("failed to parse namespace, expected 'class' after 'narrow'");
		return con.undo();
	}
	auto name = Name::parse(con);
	if (!name) return con.undo();
	con.narrow(name);
	con.discard();
	return true;
}

static bool Namespace_narrow::parse(ParserContainer &con) {
	Namespace_narrow e(con);
	return e.parse();
}

}