#include "parser_declaratins.hpp"
#pragma once

namespace nanler::Parser {

Expression::Expression(ParserContainer &con): con(con) { }

bool Expression::parse() {
	con.record();
	auto assign = Assign::parse(con);
	if (assign) {
		ctx = new ExpressionContext();
		ctx->push(Context::wrap(assign));
		con.discard();
		return true;
	}
	auto block = Block::parse(con);
	if (block) {
		ctx = new ExpressionContext();
		ctx->push(Context::wrap(block));
		con.discard();
		return true;
	}
	auto math = Operator::parse(con);
	if (math) {
		ctx = new ExpressionContext();
		ctx->push(Context::wrap(math));
		con.discard();
		return true;
	}
	auto call = CallFunction::parse(con);
	if (call) {
		ctx = new ExpressionContext();
		ctx->push(Context::wrap(call));
		con.discard();
		return true;
	}
	// ? not sure about this
	// auto expression = Expression::parse(con);
	// if (expression) {
	// 	ctx = new ExpressionContext();
	// 	ctx->push(Context::wrap(expression));
	// 	con.discard();
	// 	return true;
	// }
	auto incapsulate = Incapsulate::parse(con);
	if (incapsulate) {
		ctx = new ExpressionContext();
		ctx->push(Context::wrap(incapsulate));
		con.discard();
		return true;
	}
	auto ret = Return::parse(con);
	if (ret) {
		ctx = new ExpressionContext();
		ctx->push(Context::wrap(ret));
		con.discard();
		return true;
	}
	auto if_else_final = If_Else_Final::parse(con);
	if (if_else_final) {
		ctx = new ExpressionContext();
		ctx->push(Context::wrap(if_else_final));
		con.discard();
		return true;
	}
	auto bin = BinWutil::parse(con);
	if (bin) {
		ctx = new ExpressionContext();
		ctx->push(Context::wrap(bin));
		con.discard();
		return true;
	}
	auto trait = Trait::parse(con);
	if (trait) {
		ctx = new ExpressionContext();
		ctx->push(Context::wrap(trait));
		con.discard();
		return true;
	}
	auto typedef_ = Typedef::parse(con);
	if (typedef_) {
		ctx = new ExpressionContext();
		ctx->push(Context::wrap(typedef_));
		con.discard();
		return true;
	}
	/*
	? complete
		[x] | - assign
		[x] | - block
		[x] | - math == operator[]
		[x] | - function call
		[x] | - expression[]
		[x] | ?- incapsulate
		[x] | - return
		[x] | - if-else-final
		[x] | - bin
		[x] | ?- end 
		[x] | trait + template
		[x] | type ?+ template
		[x] | ?- reference function like `@gen => #!default`
		*/
	return false;
}

ExpressionContext* Expression::parse(ParserContainer &con) {
	Expression e(con);
	return !e.parse() ? nullptr : e.ctx;
}

}