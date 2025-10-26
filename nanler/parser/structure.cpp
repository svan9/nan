#include "parser_declaratins.hpp"
#pragma once

namespace nanler::Parser {

Structure::Structure(ParserContainer &con): con(con) { }

bool Structure::parse() {
	con.record();
	auto template_ctx = Template::parse(con); // optional
	auto tk = *con.next()++;
	if (tk.type != TokenType::Struct) {
		return con.undo();
	}
	auto name = Name::parse(con);
	if (!name) return con.undo();
	ctx = new StructContext();
	ctx->name = Context::wrap(name);
	ctx->fields = mew::stack<AssignContext*>();
	ctx->generic = template_ctx;
	if ((*con.next()++).type != TokenType::FigureOpenBracket) {
		con.error("failed to parse structure, expected '{' after 'struct'");
		return con.undo();
	}
	while (!EOB(con)) {
		auto field = Assign::parse(con);
		if (!field && !EOL(con)) {
			con.error("failed to parse structure, expected field or '}'");
			return con.undo();
		}
		ctx->fields.push(field);
	}
	con.putStruct(ctx);
	con.discard();
	return true;
}

StructContext* Structure::parse(ParserContainer &con) {
	Structure e(con);
	return !e.parse() ? nullptr : e.ctx;
}

}