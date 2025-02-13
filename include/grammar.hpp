#ifndef _NAN_GRAMMAR_IMPL
#define _NAN_GRAMMAR_IMPL

#include "mewlib.h"

namespace Token {

enum Kind: unsigned long long {
// punctuation
	Token_None,
	Token_Entry,
	Token_Extern,
	Token_Use,
	Token_Flag,
	Token_Ret,
	Token_Class,
	Token_For,
	Token_While,
	Token_Interface,
	Token_Struct,
	Token_Static,
	Token_Expand,
	Token_Narrow,
// primitive data types
	Token_Address,
	Token_Char,
	Token_Float,
	Token_Double,
	Token_Integer,
	Token_Unsigned,
	Token_Short,
	Token_String,
	Token_Number,
	Token_Let,
	Token_Const,
	Token_Void,
// singles
	Token_Star,
	Token_Sharp,
	Token_Semicolon,
	Token_Colon,
	Token_SingleQuote,
	Token_ApostropheQuote,
	Token_DoubleQuote,
	Token_TripleDot,
	Token_Dot,
	Token_Comma,
	Token_Equal,
	Token_Plus,
	Token_Minus,
	Token_Slash,
	Token_BackSlash,
	Token_Split,
	Token_Underscore,
	Token_Ampersand,
	Token_Dollar,
	Token_Percent,
	Token_At,
	Token_Exclamate,
	Token_Question,
	Token_Tilda,
	Token_ArrowUp,
	Token_ArrowOpen,
	Token_ArrowClose,
	Token_RoundOpen,
	Token_RoundClose,
	Token_SquareOpen,
	Token_SquareClose,
	Token_FigureOpen,
	Token_FigureClose,
	Token_One 	,//= (1 << 6),
	Token_Two 	,//= (1 << 7),
	Token_Three ,//= (1 << 8),
	Token_Four 	,//= (1 << 9),
	Token_Five	,//= (1 << 10),
	Token_Six 	,//= (1 << 11),
	Token_Seven ,//= (1 << 12),
	Token_Eight ,//= (1 << 13),
	Token_Nine 	,//= (1 << 14),
	Token_Zero 	,//= (1 << 15),
	// Token_Digit = Token_One | Token_Two | Token_Three | Token_Four | Token_Five | Token_Six | Token_Seven | Token_Eight | Token_Nine | Token_Zero,
// .. 
	Token_Text,
	// NANVM
	Token_PUTS,
	Token_PUTC,
	Token_PUTI,
	Token_PUSH,
	Token_POP,
	Token_TEST,
	Token_JEL,
	Token_JEM,
	Token_JE,
	Token_JL,
	Token_JM,
	Token_JNE,
	Token_INC,
	Token_DEC,
};

struct Token {
	Kind kind;
	data_t data;
};

}

#endif