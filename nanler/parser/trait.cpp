#include "parser_declaratins.hpp"
#pragma once

namespace nanler::Parser {

Trait::Trait(ParserContainer &con): con(con) { }

bool Trait::parse() {
	return false; // TODO: implement Trait parsing
}

TraitContext* Trait::parse(ParserContainer &con) {
	Trait e(con);
	return !e.parse() ? nullptr : e.ctx;
}

}