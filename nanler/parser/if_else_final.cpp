#include "parser_declaratins.hpp"
#pragma once

namespace nanler::Parser {

If_Else_Final::If_Else_Final(ParserContainer &con): con(con) { }

bool If_Else_Final::parse() {
	con.record();
	if ((*con.next()++).type != TokenType::If) {
		return con.undo();
	}
	ctx = new IfContext();
	ctx->condition = ArrayInRound::parse(con);
	if (!ctx->condition) return con.undo();
	ctx->if_body = Block::parse(con);
	if (!ctx->if_body) {
		con.error("failed to parse if block, expected block after condition");
		return con.undo();
	}
	while ((*(con.next()+1)).type == TokenType::If && 
		(*(con.next()+2)).type == TokenType::Else
	) {
		auto ief = If_Else_Final::parse(con);
		if (!ief) { break;}
		ctx->if_else_body.push(ief);
		con.next() += 2;
	}
	if ((*(con.next()+1)).type == TokenType::Else) {
		++con.next();
		ctx->else_body = Block::parse(con);
		if (!ctx->else_body) {
			con.error("failed to parse else block, expected block after 'else'");
			return con.undo();
		}
	} else {
		ctx->else_body = nullptr;
	}

	if ((*(con.next()+1)).type == TokenType::Final) {
		++con.next();
		ctx->final_body = Block::parse(con);
		if (!ctx->final_body) {
			con.error("failed to parse final block, expected block after 'final'");
			return con.undo();
		}
	} else {
		ctx->final_body = nullptr;
	}			
	con.discard();
	return true;
}

IfContext* If_Else_Final::parse(ParserContainer &con) {
	If_Else_Final e(con);
	return !e.parse() ? nullptr : e.ctx;
}

}