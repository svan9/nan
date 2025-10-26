#include "parser_declaratins.hpp"
#pragma once

namespace nanler::Parser {

Namespace_expand::Namespace_expand(ParserContainer &con): con(con) { }

bool Namespace_expand::parse() {
	con.record();
	auto template_ctx = Template::parse(con);
	auto tk = *con.next()++;
	if (tk.type != TokenType::Expand) {
		return con.undo();
	}
	tk = *con.next()++;
	if (tk.type != TokenType::Class) {
		con.error("failed to parse namespace, expected 'class' after 'expand'");
		return con.undo();
	}
	auto name = Name::parse(con);
	if (!name) return con.undo();
	con.expand(name, template_ctx);
	con.discard();
	return true;
}

static bool Namespace_expand::parse(ParserContainer &con) {
	Namespace_expand e(con);
	return e.parse();
}

}