#include "parser_declaratins.hpp"
#pragma once

namespace nanler::Parser {

Template::Template(ParserContainer &con): con(con) { }

bool Template::parse() {
	con.record();
	if ((*con.next()++).type != TokenType::Template) {
		return con.undo();
	}
	ctx = new GenericContext();
	if ((*con.next()++).type != TokenType::TriangleOpenBracket) {
		con.error("failed to parse template, expected '<'");
		return con.undo();
	}
	while ((*con.next()++).type != TokenType::TriangleCloseBracket) {
		auto type = Type::parse(con);
		if (!type) {
			con.error("failed to parse template, expected type or '>'");
			return con.undo();
		}
		ctx->types.push(type);
	}
	con.discard();
	return true;
}

GenericContext* Template::parse(ParserContainer &con) {
	Template e(con);
	return !e.parse() ? nullptr : e.ctx;
}

}