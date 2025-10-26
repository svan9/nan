#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "Config.hpp"
#include "mewlib.h"

namespace nanler {
	class Visitor {
	public:
		virtual ~Visitor() = default;

		Context visit(Context* ctx) {
			switch(ctx->type) {
				case ContextType::BinContext: 
					visitBinContext((BinContext*)ctx->data);
					break;
				case ContextType::TypeContext: 
					visitTypeContext((TypeContext*)ctx->data);
					break;
				case ContextType::FieldFlag: 
					visitFieldFlag((FieldFlag*)ctx->data);
					break;
				case ContextType::NameContext: 
					visitNameContext((NameContext*)ctx->data);
					break;
				case ContextType::LineContext: 
					visitLineContext((LineContext*)ctx->data);
					break;
				case ContextType::SquareArray: 
					visitSquareArray((SquareArray*)ctx->data);
					break;
				case ContextType::FunctionDeclaration: 
					visitFunctionDeclaration((FunctionDeclaration*)ctx->data);
					break;
				case ContextType::FunctionCall: 
					visitFunctionCall((FunctionCall*)ctx->data);
					break;
				case ContextType::ForContext: 
					visitForContext((ForContext*)ctx->data);
					break;
				case ContextType::WhileContext: 
					visitWhileContext((WhileContext*)ctx->data);
					break;
				case ContextType::IfContext: 
					visitIfContext((IfContext*)ctx->data);
					break;
				case ContextType::DeclareContext: 
					visitDeclareContext((DeclareContext*)ctx->data);
					break;
				case ContextType::InitContext: 
					visitInitContext((InitContext*)ctx->data);
					break;
				case ContextType::AssignContext: 
					visitAssignContext((AssignContext*)ctx->data);
					break;
				case ContextType::OperatorContext: 
					visitOperatorContext((OperatorContext*)ctx->data);
					break;
				case ContextType::MathContext: 
					visitMathContext((MathContext*)ctx->data);
					break;
				case ContextType::SizeofContext: 
					visitSizeofContext((SizeofContext*)ctx->data);
					break;
				case ContextType::RangeContext: 
					visitRangeContext((RangeContext*)ctx->data);
					break;
				case ContextType::SizeofContext2: 
					visitSizeofContext2((SizeofContext2*)ctx->data);
					break;
				case ContextType::CallContext: 
					visitCallContext((CallContext*)ctx->data);
					break;
				case ContextType::StructContext: 
					visitStructContext((StructContext*)ctx->data);
					break;
				case ContextType::EnumContext: 
					visitEnumContext((EnumContext*)ctx->data);
					break;
				case ContextType::TypeLimitterContext: 
					visitTypeLimitterContext((TypeLimitterContext*)ctx->data);
					break;
				case ContextType::TypeContext: 
					visitTypeContext((TypeContext*)ctx->data);
					break;
				case ContextType::GenericContext: 
					visitGenericContext((GenericContext*)ctx->data);
					break;
				case ContextType::ClassContext: 
					visitClassContext((ClassContext*)ctx->data);
					break;
				case ContextType::EtcContext: 
					visitEtcContext((EtcContext*)ctx->data);
					break;
				case ContextType::ResultContext: 
					visitResultContext((ResultContext*)ctx->data);
					break;
				case ContextType::MacrosContext: 
					visitMacrosContext((MacrosContext*)ctx->data);
					break;
				case ContextType::ReturnContext: 
					visitReturnContext((ReturnContext*)ctx->data);
					break;
				case ContextType::LROperatorContext: 
					visitLROperatorContext((LROperatorContext*)ctx->data);
					break;
				case ContextType::LROperatorNamedContext: 
					visitLROperatorNamedContext((LROperatorNamedContext*)ctx->data);
					break;
				case ContextType::GenericExpression: 
					visitGenericExpression((GenericExpression*)ctx->data);
					break;
				case ContextType::ExpressionContext: 
					visitExpressionContext((ExpressionContext*)ctx->data);
					break;
				case ContextType::UsingContext: 
					visitUsingContext((UsingContext*)ctx->data);
					break;
				case ContextType::EntryContext: 
					visitEntryContext((EntryContext*)ctx->data);
					break;
				case ContextType::BlockContext: 
					visitBlockContext((BlockContext*)ctx->data);
					break;
				default:
					MewWarn("Unknown context type: " << (int)ctx->type);
					return Context{ContextType::Undefined, nullptr};
			}
		}
		

		virtual Context visitBinContext(BinContext* ctx) { return Context{ContextType::BinContext, (void*)ctx}; }
		virtual Context visitTypeContext(TypeContext* ctx) { return Context{ContextType::TypeContext, (void*)ctx}; }
		virtual Context visitFieldFlag(FieldFlag* ctx) { return Context{ContextType::FieldFlag, (void*)ctx}; }
		virtual Context visitNameContext(NameContext* ctx) { return Context{ContextType::NameContext, (void*)ctx}; }
		virtual Context visitLineContext(LineContext* ctx) { return Context{ContextType::LineContext, (void*)ctx}; }
		virtual Context visitSquareArray(SquareArray* ctx) { return Context{ContextType::SquareArray, (void*)ctx}; }
		virtual Context visitFunctionDeclaration(FunctionDeclaration* ctx) { return Context{ContextType::FunctionDeclaration, (void*)ctx}; }
		virtual Context visitFunctionCall(FunctionCall* ctx) { return Context{ContextType::FunctionCall, (void*)ctx}; }
		virtual Context visitForContext(ForContext* ctx) { return Context{ContextType::ForContext, (void*)ctx}; }
		virtual Context visitWhileContext(WhileContext* ctx) { return Context{ContextType::WhileContext, (void*)ctx}; }
		virtual Context visitIfContext(IfContext* ctx) { return Context{ContextType::IfContext, (void*)ctx}; }
		virtual Context visitDeclareContext(DeclareContext* ctx) { return Context{ContextType::DeclareContext, (void*)ctx}; }
		virtual Context visitInitContext(InitContext* ctx) { return Context{ContextType::InitContext, (void*)ctx}; }
		virtual Context visitAssignContext(AssignContext* ctx) { return Context{ContextType::AssignContext, (void*)ctx}; }
		virtual Context visitOperatorContext(OperatorContext* ctx) { return Context{ContextType::OperatorContext, (void*)ctx}; }
		virtual Context visitMathContext(MathContext* ctx) { return Context{ContextType::MathContext, (void*)ctx}; }
		virtual Context visitSizeofContext(SizeofContext* ctx) { return Context{ContextType::SizeofContext, (void*)ctx}; }
		virtual Context visitRangeContext(RangeContext* ctx) { return Context{ContextType::RangeContext, (void*)ctx}; }
		virtual Context visitSizeofContext2(SizeofContext2* ctx) { return Context{ContextType::SizeofContext2, (void*)ctx}; }
		virtual Context visitCallContext(CallContext* ctx) { return Context{ContextType::CallContext, (void*)ctx}; }
		virtual Context visitStructContext(StructContext* ctx) { return Context{ContextType::StructContext, (void*)ctx}; }
		virtual Context visitEnumContext(EnumContext* ctx) { return Context{ContextType::EnumContext, (void*)ctx}; }
		virtual Context visitTypeLimitterContext(TypeLimitterContext* ctx) { return Context{ContextType::TypeLimitterContext, (void*)ctx}; }
		virtual Context visitTypeContext(TypeContext* ctx) { return Context{ContextType::TypeContext, (void*)ctx}; }
		virtual Context visitGenericContext(GenericContext* ctx) { return Context{ContextType::GenericContext, (void*)ctx}; }
		virtual Context visitClassContext(ClassContext* ctx) { return Context{ContextType::ClassContext, (void*)ctx}; }
		virtual Context visitEtcContext(EtcContext* ctx) { return Context{ContextType::EtcContext, (void*)ctx}; }
		virtual Context visitResultContext(ResultContext* ctx) { return Context{ContextType::ResultContext, (void*)ctx}; }
		virtual Context visitMacrosContext(MacrosContext* ctx) { return Context{ContextType::MacrosContext, (void*)ctx}; }
		virtual Context visitReturnContext(ReturnContext* ctx) { return Context{ContextType::ReturnContext, (void*)ctx}; }
		virtual Context visitLROperatorContext(LROperatorContext* ctx) { return Context{ContextType::LROperatorContext, (void*)ctx}; }
		virtual Context visitLROperatorNamedContext(LROperatorNamedContext* ctx) { return Context{ContextType::LROperatorNamedContext, (void*)ctx}; }
		virtual Context visitGenericExpression(GenericExpression* ctx) { return Context{ContextType::GenericExpression, (void*)ctx}; }
		virtual Context visitExpressionContext(ExpressionContext* ctx) { return Context{ContextType::ExpressionContext, (void*)ctx}; }
		virtual Context visitUsingContext(UsingContext* ctx) { return Context{ContextType::UsingContext, (void*)ctx}; }
		virtual Context visitEntryContext(EntryContext* ctx) { return Context{ContextType::EntryContext, (void*)ctx}; }
		virtual Context visitBlockContext(BlockContext* ctx) { return Context{ContextType::BlockContext, (void*)ctx}; }
	};
}

#endif