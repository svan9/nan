#ifndef TOKEN_HPP
#define TOKEN_HPP


namespace nanler {

	
	enum struct TokenType: mew::byte {
		// simple type
		Undefined,
		None, String, Number, Text,	Colon, Dot, Comma, Semicolon, DoubleColon,
		Float, Double, Int, Char, ETC,
		NumberInt, NumberFloat, NumberDouble, NumberBool,
		Use, Extern, Expand, Narrow, Class, Struct, Entry,
		If, Else, Final, Ret, Flag,
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
		Template,
		Bin,
		Null_KW, UNDEFINED_KW,
		Extra,
		More = TriangleCloseBracket,
		Less = FigureOpenBracket,
		Sharp,
	};

	inline const char* StringifyTokenType(TokenType type) {
		switch (type) {
			case TokenType::Undefined: return "Undefined";
			case TokenType::None: return "None";
			case TokenType::String: return "String";
			case TokenType::Number: return "Number";
			case TokenType::Text: return "Text";
			case TokenType::Colon: return "Colon";
			case TokenType::Dot: return "Dot";
			case TokenType::Comma: return "Comma";
			case TokenType::Semicolon: return "Semicolon";
			case TokenType::DoubleColon: return "DoubleColon";
			case TokenType::Float: return "Float";
			case TokenType::Double: return "Double";
			case TokenType::Int: return "Int";
			case TokenType::Char: return "Char";
			case TokenType::ETC: return "ETC";
			case TokenType::NumberInt: return "NumberInt";
			case TokenType::NumberFloat: return "NumberFloat";
			case TokenType::NumberDouble: return "NumberDouble";
			case TokenType::Use: return "Use";
			case TokenType::Extern: return "Extern";
			case TokenType::Expand: return "Expand";
			case TokenType::Narrow: return "Narrow";
			case TokenType::Class: return "Class";
			case TokenType::Struct: return "Struct";
			case TokenType::Entry: return "Entry";
			case TokenType::If: return "If";
			case TokenType::Else: return "Else";
			case TokenType::Ret: return "Ret";
			case TokenType::Flag: return "Flag";
			case TokenType::RoundArray: return "RoundArray";
			case TokenType::SquareArray: return "SquareArray";
			case TokenType::TriangleArray: return "TriangleArray";
			case TokenType::Block: return "Block";
			case TokenType::Minus: return "Minus";
			case TokenType::Plus: return "Plus";
			case TokenType::Equal: return "Equal";
			case TokenType::Multiply: return "Multiply";
			case TokenType::Divide: return "Divide";
			case TokenType::Add: return "Add";
			case TokenType::Sub: return "Sub";
			case TokenType::Mul: return "Mul";
			case TokenType::Div: return "Div";
			case TokenType::Inc: return "Inc";
			case TokenType::Dec: return "Dec";
			case TokenType::Xor: return "Xor";
			case TokenType::Or: return "Or";
			case TokenType::Not: return "Not";
			case TokenType::And: return "And";
			case TokenType::Ls: return "Ls";
			case TokenType::Rs: return "Rs";
			case TokenType::LogicOr: return "LogicOr";
			case TokenType::LogicAnd: return "LogicAnd";
			case TokenType::RoundOpenBracket: return "RoundOpenBracket";
			case TokenType::RoundCloseBracket: return "RoundCloseBracket";
			case TokenType::SquareOpenBracket: return "SquareOpenBracket";
			case TokenType::SquareCloseBracket: return "SquareCloseBracket";
			case TokenType::TriangleOpenBracket: return "TriangleOpenBracket";
			case TokenType::TriangleCloseBracket: return "TriangleCloseBracket";
			case TokenType::FigureOpenBracket: return "FigureOpenBracket";
			case TokenType::FigureCloseBracket: return "FigureCloseBracket";
			case TokenType::For: return "For";
			case TokenType::While: return "While";
			case TokenType::Template: return "Template";
			default: return "Unknown";
		}
	}
	
	struct Token {
		TokenType type;
		const char* value;
		int y_pos;
	};
	

	
static std::unordered_map<const char *, TokenType> token_semantic = {
	{":", TokenType::Colon},
	{";", TokenType::Semicolon},
	{"::", TokenType::DoubleColon},
	{"-", TokenType::Minus},
	{"+", TokenType::Plus},
	{"++", TokenType::Inc},
	{"--", TokenType::Dec},
	{"=", TokenType::Equal},
	{"*", TokenType::Multiply},
	{"/", TokenType::Divide},
	{"!", TokenType::Not},
	{"#", TokenType::Sharp},
	{"|", TokenType::Or},
	{"^", TokenType::Xor},
	{"&", TokenType::And},
	{">>", TokenType::Rs},
	{"<<", TokenType::Ls},
	{"||", TokenType::LogicOr},
	{"&&", TokenType::LogicAnd},
	{"(", TokenType::RoundOpenBracket},
	{")", TokenType::RoundCloseBracket},
	{"[", TokenType::SquareOpenBracket},
	{"]", TokenType::SquareCloseBracket},
	{"<", TokenType::TriangleOpenBracket},
	{">", TokenType::TriangleCloseBracket},
	{"{", TokenType::FigureOpenBracket},
	{"}", TokenType::FigureCloseBracket},
	{"if", TokenType::If},
	{"else", TokenType::Else},
	{"final", TokenType::Final},
	{"ret", TokenType::Ret},
	{"use", TokenType::Use},
	{"extern", TokenType::Extern},
	{"expand", TokenType::Expand},
	{"narrow", TokenType::Narrow},
	{"class", TokenType::Class},
	{"struct", TokenType::Struct},
	{"entry", TokenType::Entry},
	{"...", TokenType::ETC},
	{"float", TokenType::Float},
	{"double", TokenType::Double},
	{"int", TokenType::Int},
	{"char", TokenType::Char},
	{"string", TokenType::String},
	{"for", TokenType::For},
	{"while", TokenType::While},
	{"template", TokenType::Template},
	{"@", TokenType::Flag},
	{"bin", TokenType::Bin},
	{"true", TokenType::NumberBool},
	{"false", TokenType::NumberBool},
	{"null", TokenType::Null_KW},
	{"undefined", TokenType::UNDEFINED_KW},
	{"extra", TokenType::Extra},
	// {"undefined", TokenType::Undefined},
};

}
#endif