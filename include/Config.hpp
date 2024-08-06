#ifndef __CONFIG__NAN__
#define __CONFIG__NAN__

#define TV_SEMICOLON 	";"
#define TV_COLON 			":"
#define TV_DIGIS 			"1234567890"
#define TV_SPECIAL 		"\'\"\\/=+(){}[]<>?.,!~@#$%^&*-|"
#define TV_SPACE 			" \t"
#define TV_STRING 		"\""
#define TV_CRLF 			"\n\r"
#define TV_OPEN_SQ 		"["
#define TV_OPEN_RN 		"("
#define TV_OPEN_TR 		"<"
#define TV_OPEN_FG 		"{"
#define TV_CLOSE_SQ 	"]"
#define TV_CLOSE_RN 	")"
#define TV_CLOSE_TR 	">"
#define TV_CLOSE_FG 	"}"
#define TV_DOT 				"."
#define TV_COMMA		 	","
#define TV_GRID			 	"#"
#define TV_PERCENT		"%"
#define TV_UP					"^"
#define TV_ATSIGN			"@"
#define TV_EM					"!"
#define TV_QM					"?"
#define TV_EQUAL			"="
#define TV_PLUS				"+"
#define TV_MINUS			"-"
#define TV_AND				"&"
#define TV_OR					"|"
#define TV_SLASH			"\\"
#define TV_BSLASH			"/"
#define TV_STAR				"*"
#define TV_DL					"$"
#define TV_AP					"`"
#define TV_SQUOTE			"'"


#include <string>

bool sub_str(const std::string& s1, const std::string& s2) {
	return s1.find(s2) != std::string::npos;
}

bool sub_str(const std::string& s1, char s2) {
	return s1.find(s2) != std::string::npos;
}

bool __is_lex_type__(const std::string s1, const std::string s2) {
	return sub_str(s1, s2);
}

bool __is_lex_type__(const std::string s1, const char s2) {
	return sub_str(s1, s2);
}

template<size_t k>
auto __toUpperCase__(char str[k]) -> char(&)[k] {
	char __new_str[k] = {0};
	for (int i = 0; i < k; i++) {
		_new_str[i] = toupper(str[i]);
	}
	return _new_str;
}

template<size_t k>
auto __toLowerCase__(char str[k]) -> char(&)[k] {
	char __new_str[k] = {0};
	for (int i = 0; i < k; i++) {
		_new_str[i] = tolower(str[i]);
	}
	return _new_str;
}

bool match_nocase(std::string left, std::string right) {
	if (left.size() != right.size()) { return false; }
	for (int i = 0; i < left.size(); i++) {
		if (tolower(left.at(i)) != tolower(right.at(i))) {
			return false;
		}
	}
	return true;
}

bool match_nocase(std::string_view left, std::string_view right) {
	if (left.size() != right.size()) { return false; }
	for (int i = 0; i < left.size(); i++) {
		if (tolower(left.at(i)) != tolower(right.at(i))) {
			return false;
		}
	}
	return true;
}

#define __concat__(A, B) A##B
#define is_lex_type(type, string) __is_lex_type__(__concat__(TV_, type), string)
#define lexer_ifis(type, string) if (is_lex_type(type, string)) { append(type); after_space = false; }


#endif