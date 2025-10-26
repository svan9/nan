#include "parser_declaratins.hpp"
#pragma once

namespace nanler::Parser {

Block::Block(ParserContainer &con): con(con) { }

bool Block::parse() {
	con.record();
	if ((*con.next()++).type != TokenType::FigureOpenBracket) {
		return con.undo();
	}
	ctx = new BlockContext();
	while ((*con.next()++).type != TokenType::FigureCloseBracket) {
		auto line = Line::parse(con);
		if (!line) {
			con.error("failed to parse block, expected line or '}'");
			return con.undo();
		}
		ctx->lines.push(*line);
	}				
	con.discard();
	return true;
}

BlockContext* Block::parse(ParserContainer &con) {
	Block e(con);
	return !e.parse() ? nullptr : e.ctx;
}

}