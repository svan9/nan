#ifndef __ASTLIB_SO2U__
#define __ASTLIB_SO2U__

#include <map>
#include <unordered_map>
#include <stack>
#include <vector>
#include <string>
#include "mewall.h"

#ifndef __CXX20
	#error NEEDS VERSION CXX >= 20
#endif

namespace iternal::ast::lib {
	template<typename T>
	concept opt_type = requires(T v) {
		{ v.size() } noexcept;
		{ v.data() } noexcept -> mew::same_as<const char*>;
	};
};


////////////////////////////////////////////////////////////
// UNIVERSAL MAP OBJECT
////////////////////////////////////////////////////////////
template<iternal::ast::lib::opt_type OPT_KEY, iternal::ast::lib::opt_type OPT_VAL>
class AST_base {
public:
	// typedef std::string_view OPT_KEY;
	// typedef std::string_view OPT_VAL;
	typedef AST_base Element_t;
	typedef Element_t* data_element_t;
	typedef std::vector<data_element_t> datatype_t;
	typedef std::unordered_map<OPT_KEY, OPT_VAL> opttype_t;
private:
	opttype_t  _M_options;
	datatype_t _M_data;

	////////////////////////////////////////////////////////////
	void rm_pop() {
		MewAssert(_M_data.size() >= 1);
		_M_data.pop_back();
	}
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
	void append(Element_t& tk) { _M_data.push_back(&tk); }

	////////////////////////////////////////////////////////////
	void append(const Element_t& tk) {_M_data.push_back(&tk); }

	////////////////////////////////////////////////////////////
	void append(Element_t* tk) { _M_data.push_back(tk); }
		
	////////////////////////////////////////////////////////////
	Element_t* at(int idx) {
		size_t real_idx = (_M_data.size() + idx) % _M_data.size();
		return _M_data.at(idx);
	}

	////////////////////////////////////////////////////////////
	bool is_empty() {
		return _M_data.size() == 0;
	}

	////////////////////////////////////////////////////////////
	Element_t* top() {
		MewAssert(_M_data.size() >= 1);
		Element_t* et = at(-1);
		return et;
	}
	
	////////////////////////////////////////////////////////////
	void pop() {
		MewAssert(_M_data.size() >= 1);
		rm_pop();
	}
	
	////////////////////////////////////////////////////////////
	void add_option(OPT_KEY key, OPT_VAL val) {
		_M_options.insert({key, val});
	}
	
	////////////////////////////////////////////////////////////
	void add_option(OPT_KEY key) {
		_M_options.insert({key, static_cast<OPT_VAL>(0)});
	}

	////////////////////////////////////////////////////////////
	void add_option(const char* key, const char* val) {
		_M_options.insert({OPT_KEY(key), OPT_VAL(val)});
	}

	////////////////////////////////////////////////////////////
	void add_option(const char* key, OPT_VAL val) {
		_M_options.insert({OPT_KEY(key), val});
	}
	
	////////////////////////////////////////////////////////////
	void add_option(OPT_KEY key, const char* val, size_t size) {
		_M_options.insert({key, std::string_view(val, size)});
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
		MewAssert(has_option(key));
		return (*_M_options.find(key)).second;
	}

	////////////////////////////////////////////////////////////
	template<typename T>
	T get_option_v(const char* key) {
		MewAssert(has_option(key));
		OPT_VAL val = get_option(key);
		MewUserAssert(val.size() == sizeof(T), "types not matches");
		T value;
		memcpy(&value, val.data(), sizeof(T));
		return value;
	}

	////////////////////////////////////////////////////////////
	template<typename T>
	T get_option_v(OPT_KEY key) {
		MewAssert(has_option(key));
		OPT_VAL val = (*_M_options.find(key)).second;
		MewUserAssert(val.size() == sizeof(T), "types not matches");
		T value;
		memcpy(&value, val.data(), sizeof(T));
		return value;
	}

	////////////////////////////////////////////////////////////
	template<typename T, typename K>
	K get_option_v(const T& key) {
		char bk[sizeof(T)];
		memcpy(bk, &key, sizeof(T));
		return get_option_v<K>(bk);
	}

	////////////////////////////////////////////////////////////
	template<typename T>
	void add_option_v(OPT_KEY key, T&& value) {
		char buffer[sizeof(T)];
		memcpy(buffer, &value, sizeof(T));
		add_option(key, buffer, sizeof(T));
	}

	////////////////////////////////////////////////////////////
	template<typename T>
	void add_option_v(OPT_KEY key, const T& value) {
		char buffer[sizeof(T)];
		memcpy(buffer, &value, sizeof(T));
		add_option(key, buffer, sizeof(T));
	}

	////////////////////////////////////////////////////////////
	template<typename T, typename K>
	void add_option_v(const T& key, const K& value) {
		char bk[sizeof(T)+1];
		memcpy(bk, &key, sizeof(T));
		bk[sizeof(T)] = '\0';
		char bv[sizeof(K)];
		memcpy(bv, &value, sizeof(K));
		add_option(bk, bv, sizeof(K));
	}

	////////////////////////////////////////////////////////////
	template<typename T>
	void add_option_v(const T& key, OPT_VAL value) {
		char bk[sizeof(T)+1];
		memcpy(bk, &key, sizeof(T));
		bk[sizeof(T)] = '\0';
		add_option(bk, value);
	}

	////////////////////////////////////////////////////////////
	template<typename T>
	void add_option_v(const T& key, const char* value, size_t size) {
		char bk[sizeof(T)+1];
		memcpy(bk, &key, sizeof(T));
		bk[sizeof(T)] = '\0';
		add_option(bk, value, size);
	}
};

typedef AST_base<std::string_view, std::string_view> AST;



#endif