#include "parser_declaratins.hpp"
#pragma once

namespace nanler::Parser {

Name::Name(ParserContainer &con): con(con), ctx(new NameContext()) { }

bool Name::parse() {
	auto tk = *con.next();
	if (tk.type != TokenType::Text) return false;
	ctx->name = tk.value;
	ctx->path = con.getPath();
	++con.next();
	return true;
}

NameContext* Name::parse(ParserContainer &con) {
	Name e(con);
	return !e.parse() ? nullptr : e.ctx;
}


}