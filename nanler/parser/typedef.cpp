#include "parser_declaratins.hpp"
#pragma once

namespace nanler::Parser {

Typedef::Typedef(ParserContainer &con): con(con) { }

bool Typedef::parse() {
	return false; // TODO: implement Typedef parsing
}

TypeContext* Typedef::parse(ParserContainer &con) {
	Typedef e(con);
	return !e.parse() ? nullptr : e.ctx;
}

}