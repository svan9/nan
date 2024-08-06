#ifndef __TOKEN__NAN__
#define __TOKEN__NAN__

#include <string>
#include <Config.hpp>

class Token {
private:
	short _M_type;
	std::string_view _M_value;
	bool _M_after_space = false;
public:
	Token() {}

	Token(short __type, const std::string_view& __value = "") {
		_M_type = __type;
		_M_value = __value;
	}

	void after_space(bool __after_space) {
		_M_after_space = __after_space;
	}

	bool after_space() const noexcept {
		return _M_after_space;
	}

	std::string_view& value() {
		return _M_value;
	}

	void value(const std::string_view& __value) {
		_M_value = __value;
	}
	
	short& type() {
		return _M_type;
	}

	void type(short __type) { 
		_M_type = __type;
	}

	bool is(short type, bool after_spacing = true) {
		return (type == _M_type && _M_after_space == after_spacing);
	}

	bool is(std::string_view value, bool after_spacing = true) {
		return (value == _M_value && _M_after_space == after_spacing);
	}

	bool is_nocase(std::string_view value, bool after_spacing = true) {
		return (match_nocase(value, _M_value) &&  after_spacing == _M_after_space);
	}
};


#endif