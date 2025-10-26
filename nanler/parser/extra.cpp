#include "parser_declaratins.hpp"
#pragma once

namespace nanler::Parser {

Extra::Extra(ParserContainer &con): con(con) { }

bool Extra::parse() {
	con.record();
	auto tk = *con.next()++;
	if (tk.type != TokenType::Extra) {
		return con.undo();
	}
	auto name = Name::parse(con);
	if (!name) return con.undo();
	ctx = new ExtraContext();
	ctx->name = name;
	ctx->fields = mew::stack<ExtraContextField>();
	if ((*con.next()++).type != TokenType::FigureOpenBracket) {
		con.error("failed to parse extra, expected '{' after 'extra'");
		return con.undo();
	}
	while (!EOB(con)) {
		ExtraContextField field;
		auto flag = Flag::parse(con);
		if (flag) {
			field.name = flag->name;
		}
		else {
			auto name = Name::parse(con);
			if (!name) {
				con.error("failed to parse extra field, expected name or flag");
				return con.undo();
			}
			field.name = name;
		}
		if ((*con.next()++).type != TokenType::Equal && 
			(*con.next()++).type != TokenType::More) {
			con.error("failed to parse extra field, expected syntax @name => #!value");
			return con.undo();
		}
		field.value = IternalName::parse(con);
		if (!field.value) {
			con.error("failed to parse extra field, expected #!value");
			return con.undo();
		}
		ctx->fields.push(field);	
	}
	con.discard();
	return true;
}

ExtraContext* Extra::parse(ParserContainer &con) {
	Extra e(con);
	return !e.parse() ? nullptr : e.ctx;
}

}