#include "parser_declaratins.hpp"
#pragma once

namespace nanler::Parser {

Namespace::Namespace(ParserContainer &con): con(con) { }

bool Namespace::parse() {
	return Namespace_expand::parse(con) || 
			Namespace_narrow::parse(con);
}

static bool Namespace::parse(ParserContainer &con) {
	Namespace e(con);
	return e.parse();
}

}