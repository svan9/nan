#ifndef __ABSTRACTSYNTAXTREE__NAN__
#define __ABSTRACTSYNTAXTREE__NAN__

#include <map>
#include <stack>
#include <string>

////////////////////////////////////////////////////////////
// UNIVERSAL MAP OBJECT
////////////////////////////////////////////////////////////
template<typename OPT_KEY, typename OPT_VAL>
class AST_base {
public:
	// typedef std::string_view OPT_KEY;
	// typedef std::string_view OPT_VAL;
	typedef AST_base Element_t;
	typedef Element_t* data_element_t;
	typedef std::stack<data_element_t> datatype_t;
	typedef std::map<OPT_KEY, OPT_VAL> opttype_t;
private:
	opttype_t  _M_options;
	datatype_t _M_data;
public:

	////////////////////////////////////////////////////////////
	AST_base() {}

	////////////////////////////////////////////////////////////
	AST_base(opttype_t& op) { _M_options = op; }
	
	////////////////////////////////////////////////////////////
	datatype_t data() const noexcept { return _M_data; }
	
	////////////////////////////////////////////////////////////
	void data(datatype_t& value) { _M_data = value; }
	
	////////////////////////////////////////////////////////////
	opttype_t options() const noexcept { return _M_options; }
	
	////////////////////////////////////////////////////////////
	void options(opttype_t& value) { _M_options = value; }
	
	////////////////////////////////////////////////////////////
	void append(Element_t& tk) { _M_data.push(&tk); }
	
	////////////////////////////////////////////////////////////
	Element_t* pop() {
		Element_t* tk = _M_data.top(); _M_data.pop();
		return tk;
	}
	
	////////////////////////////////////////////////////////////
	void add_option(OPT_KEY key, OPT_VAL val) {
		_M_options.insert(key, val);
	}
	
	////////////////////////////////////////////////////////////
	void add_option(OPT_KEY key) {
		_M_options.insert(key, static_cast<OPT_VAL>(0));
	}

	////////////////////////////////////////////////////////////
	void add_option(const char* key, const char* val) {
		_M_options.insert(AST_base::OPT_KEY(key), AST_base::OPT_VAL(val));
	}

	////////////////////////////////////////////////////////////
	void add_option(const char* key, OPT_VAL val) {
		_M_options.insert(AST_base::OPT_KEY(key), val);
	}
	
	////////////////////////////////////////////////////////////
	void add_option(OPT_KEY key, const char* val, size_t size) {
		_M_options.insert(key, std::string_view(val, size));
	}

	////////////////////////////////////////////////////////////
	bool has_option(OPT_KEY key, OPT_VAL val) {
		return (get_option(key) == val);
	}
	
	////////////////////////////////////////////////////////////
	bool has_option(OPT_KEY key) {
		return (_M_options.find("f") != _M_options.end());
	}


	////////////////////////////////////////////////////////////
	OPT_VAL get_option(OPT_KEY key) {
		if (has_option(key)) {
			return (*_M_options.find(key)).second;
		}
		return ((OPT_VAL)0);
	}
};

typedef AST_base<std::string_view, std::string_view> AST;

#endif