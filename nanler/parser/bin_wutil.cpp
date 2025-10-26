#include "parser_declaratins.hpp"
#pragma once

namespace nanler::Parser {

BinWutil::BinWutil(ParserContainer &con): con(con) { }

bool BinWutil::parse() {
	con.record();
	auto tk = *con.next();
	if (tk.type != TokenType::Bin) { return con.undo(); }
	++con.next();
	ctx = new BinContext();
	ctx->value = tk.value;
	con.discard();
	return true;
}

BinContext* BinWutil::parse(ParserContainer &con) {
	BinWutil e(con);
	return !e.parse() ? nullptr : e.ctx;
}

}