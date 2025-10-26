#include "parser_declaratins.hpp"
#pragma once

namespace nanler::Parser {

Line::Line(ParserContainer &con): con(con) { }

bool Line::parse() {
	con.record();
	auto expression = Expression::parse(con);
	if (expression) { 
		if (!EOL(con)) {
			con.error("failed to parse line, expected ';' at the end");
			return con.undo();
		}
		ctx = new LineContext();
		ctx->expression = Context::wrap(expression);
		con.discard();
		return true;
	}
	auto func = Function::parse(con);
	if (func) {
		ctx = new LineContext();
		ctx->expression = Context::wrap(func);
		con.discard();
		return true;
	}
	auto block = Block::parse(con);
	if (block) {
		ctx = new LineContext();
		ctx->expression = Context::wrap(block);
		con.discard();
		return true;
	}
	if (Namespace::parse(con)) {
		con.discard();
		return true;
	}
	auto structure = Structure::parse(con);
	if (structure) {
		ctx = new LineContext();
		ctx->expression = Context::wrap(structure);
		con.discard();
		return true;
	}
	auto extra = Extra::parse(con);
	if (extra) {
		ctx = new LineContext();
		ctx->expression = Context::wrap(extra);
		con.discard();
		return true;
	}
	/*
	? complete
		[x] | - expression ';'
		[x] | - function + operator like
		[x] | - ?? block 
		[x] | - namespace 
		[x] | - struct + template
		[x] | - extra
	*/
	return false;
}

LineContext* Line::parse(ParserContainer &con) {
	Line e(con);
	return !e.parse() ? nullptr : e.ctx;
}

}