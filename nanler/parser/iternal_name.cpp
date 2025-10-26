#include "parser_declaratins.hpp"
#pragma once

namespace nanler::Parser {

IternalName::IternalName(ParserContainer &con): con(con) { }

bool IternalName::parse() {
	con.record();
	if ((*con.next()++).type != TokenType::Sharp && (*con.next()++).type != TokenType::Not) return con.undo();
	++con.next();
	ctx = Name::parse(con);
	con.discard();
	return true;
}

NameContext* IternalName::parse(ParserContainer &con) {
	IternalName e(con);
	return !e.parse() ? nullptr : e.ctx;
}

}