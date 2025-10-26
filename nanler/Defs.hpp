#ifndef DEFS_HPP
#define DEFS_HPP

namespace nanler {
	struct Context;
	struct FunctionDeclaration;
	struct Context;
	struct TypeContext;
	struct FieldFlag;
	struct TypeHandler;
	struct NameContext;
	struct NativeHandler;
	struct InCodeHandler;
	struct TypeHandler;
	struct LineContext;
	struct SquareArray;
	struct FunctionDeclaration;
	struct FunctionCall;
	struct ForContext;
	struct WhileContext;
	struct IfContext;
	struct DeclareContext;
	struct InitContext;
	struct AssignContext;
	struct OperatorContext;
	struct MathContext;
	struct SizeofContext;
	struct RangeContext;
	struct SizeofContext2;
	struct CallContext;
	struct StructContext;
	struct EnumContext;
	struct TypeLimitterContext;
	struct TypeContext;
	struct GenericContext;
	struct ClassContext;
	struct EtcContext;
	struct ResultContext;
	struct Status;
	struct MacrosContext;
	struct ReturnContext;
	struct LROperatorContext;
	struct LROperatorNamedContext;
	struct GenericExpression;
	struct ExpressionContext;
	struct ExpressionType;
	struct UsingContext;
	struct EntryContext;
	struct BlockContext;
	struct BinContext;
	struct ExtraContext;
	struct TraitContext;
	struct IncapsulateContext;
	struct OperatorDeclaration;

	template<typename T>
	ContextType ContextTypeFromType() {
		if constexpr (mew::same_as<T, OperatorDeclaration>) {
			return ContextType::OperatorDeclaration;
		}
		if constexpr (mew::same_as<T, TraitContext>) {
			return ContextType::TraitContext;
		}
		if constexpr (mew::same_as<T, IncapsulateContext>) {
			return ContextType::IncapsulateContext;
		}
		if constexpr (mew::same_as<T, ExtraContext>) {
			return ContextType::ExtraContext;
		}
		if constexpr (mew::same_as<T, BinContext>) {
			return ContextType::BinContext;
		}
		if constexpr (mew::same_as<T, TypeContext>) {
			return ContextType::TypeContext;
		}
		if constexpr (mew::same_as<T, FieldFlag>) {
			return ContextType::FieldFlag;
		}
		if constexpr (mew::same_as<T, NameContext>) {
			return ContextType::NameContext;
		}
		if constexpr (mew::same_as<T, LineContext>) {
			return ContextType::LineContext;
		}
		if constexpr (mew::same_as<T, SquareArray>) {
			return ContextType::SquareArray;
		}
		if constexpr (mew::same_as<T, FunctionDeclaration>) {
			return ContextType::FunctionDeclaration;
		}
		if constexpr (mew::same_as<T, FunctionCall>) {
			return ContextType::FunctionCall;
		}
		if constexpr (mew::same_as<T, ForContext>) {
			return ContextType::ForContext;
		}
		if constexpr (mew::same_as<T, WhileContext>) {
			return ContextType::WhileContext;
		}
		if constexpr (mew::same_as<T, IfContext>) {
			return ContextType::IfContext;
		}
		if constexpr (mew::same_as<T, DeclareContext>) {
			return ContextType::DeclareContext;
		}
		if constexpr (mew::same_as<T, InitContext>) {
			return ContextType::InitContext;
		}
		if constexpr (mew::same_as<T, AssignContext>) {
			return ContextType::AssignContext;
		}
		if constexpr (mew::same_as<T, OperatorContext>) {
			return ContextType::OperatorContext;
		}
		if constexpr (mew::same_as<T, MathContext>) {
			return ContextType::MathContext;
		}
		if constexpr (mew::same_as<T, SizeofContext>) {
			return ContextType::SizeofContext;
		}
		if constexpr (mew::same_as<T, RangeContext>) {
			return ContextType::RangeContext;
		}
		if constexpr (mew::same_as<T, SizeofContext2>) {
			return ContextType::SizeofContext2;
		}
		if constexpr (mew::same_as<T, CallContext>) {
			return ContextType::CallContext;
		}
		if constexpr (mew::same_as<T, StructContext>) {
			return ContextType::StructContext;
		}
		if constexpr (mew::same_as<T, EnumContext>) {
			return ContextType::EnumContext;
		}
		if constexpr (mew::same_as<T, TypeLimitterContext>) {
			return ContextType::TypeLimitterContext;
		}
		if constexpr (mew::same_as<T, TypeContext>) {
			return ContextType::TypeContext;
		}
		if constexpr (mew::same_as<T, GenericContext>) {
			return ContextType::GenericContext;
		}
		if constexpr (mew::same_as<T, ClassContext>) {
			return ContextType::ClassContext;
		}
		if constexpr (mew::same_as<T, EtcContext>) {
			return ContextType::EtcContext;
		}
		if constexpr (mew::same_as<T, ResultContext>) {
			return ContextType::ResultContext;
		}
		if constexpr (mew::same_as<T, MacrosContext>) {
			return ContextType::MacrosContext;
		}
		if constexpr (mew::same_as<T, ReturnContext>) {
			return ContextType::ReturnContext;
		}
		if constexpr (mew::same_as<T, LROperatorContext>) {
			return ContextType::LROperatorContext;
		}
		if constexpr (mew::same_as<T, LROperatorNamedContext>) {
			return ContextType::LROperatorNamedContext;
		}
		if constexpr (mew::same_as<T, GenericExpression>) {
			return ContextType::GenericExpression;
		}
		if constexpr (mew::same_as<T, ExpressionContext>) {
			return ContextType::ExpressionContext;
		}
		if constexpr (mew::same_as<T, UsingContext>) {
			return ContextType::UsingContext;
		}
		if constexpr (mew::same_as<T, EntryContext>) {
			return ContextType::EntryContext;
		}
		if constexpr (mew::same_as<T, BlockContext>) {
			return ContextType::BlockContext;
		}
		return ContextType::Undefined;
	}

	NameContext* MakeNameContext(const char* name, mew::stack<const char*>* path = nullptr);
	
}

#endif