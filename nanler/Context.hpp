#ifndef CONTEXT_HPP
#define CONTEXT_HPP

enum struct ContextType {
	/*(token types)*/
	Undefined,
	None, String, Number, Text,	Colon, Dot, Comma, Semicolon, DoubleColon,
	Float, Double, Int, Char, ETC,
	Use, Extern, Expand, Narrow, Class, Struct, Entry,
	If, Else, Ret, Flag,
	RoundArray, SquareArray, TriangleArray, Block,
	// operators
	Minus, Plus, Equal, Multiply, Divide,
	// commands
	Add, Sub, Mul, Div, Inc, Dec, Xor, Or, 
	Not, And, Ls, Rs,

	LogicOr, LogicAnd, 
	
	RoundOpenBracket, RoundCloseBracket,
	SquareOpenBracket, SquareCloseBracket,
	TriangleOpenBracket, TriangleCloseBracket,
	FigureOpenBracket, FigureCloseBracket,
	For, While,
	/*(additional types)*/
	FunctionCall,
	FunctionDeclaration,
	DeclareContext,
	InitContext,
	AssignContext,
	IfContext,
	ForContext,
	WhileContext,
	LROperatorContext,
	RIncContext, LIncContext, LDecContext, RDecContext, 
	LStarContext, RStarContext, LAmperContext, RAmperContext,
	LTildeContext, RTildeContext,
	MacrosContext, ReturnContext,
	EtcContext,
	LineContext,
	OperatorContext,
	MathContext,
	SizeofContext,
	RangeContext,
	SizeofContext2,
	CallContext,
	StructContext,
	EnumContext,
	TypeLimitterContext,
	TypeContext,
	GenericContext,
	ClassContext,
	ExpressionContext,
	NameContext,
	UsingContext,
	ResultContext,
	EntryContext,
	BlockContext,
	FieldFlag,
	LROperatorNamedContext,
	GenericExpression,
	BinContext,
	ExtraContext,
	IncapsulateContext,
	TraitContext,
};


struct Context {
	ContextType type;
	void* data;
};

#endif