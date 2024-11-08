#ifndef NAN_CFG_IML
#define NAN_CFG_IML

#include <string.h>

typedef char* data_t;
typedef unsigned char byte;
typedef unsigned int uint;

// template<typename T>
// struct List {

// 	T* begin, end;
// };

class StringIterator {
private:
public:
	const char *cbegin, *begin, *end;
	typedef StringIterator iterator;
	typedef const StringIterator const_iterator;

	StringIterator() {}
	StringIterator(const char* source): cbegin(source), begin(source), end(source+strlen(source)) {}

	iterator Begin() {
		return iterator(*this);
	}
	iterator End() {
		return iterator(*this)+(end-begin);
	}

	bool IncCheck(int v = 1) {
		return begin+v == end;
	}
	bool DecCheck(int v = 1) {
		return begin-v == cbegin;
	}

	iterator& operator++() {
		if (IncCheck()) { begin++; }
    return *this;
  }
  iterator operator++(int) {
    iterator tmp(*this);
    operator++();
    return tmp;
  }
	iterator& operator--() {
		if (DecCheck()) { begin--; }
    return *this;
  }
  iterator operator--(int) {
    iterator tmp(*this);
    operator--();
    return tmp;
  }    
	iterator& operator+=(const int v) noexcept {
		if (IncCheck(v)) { begin += v; }
    return *this;
	}

	iterator operator+(const int _Off) const noexcept {
		iterator _Tmp = *this;
		_Tmp += _Off;
		return _Tmp;
	}

	friend iterator operator+(const int _Off, iterator _Next) noexcept {
		_Next += _Off;
		return _Next;
	}
	iterator& operator-=(const int v) noexcept {
		if (DecCheck(v)) { begin += v; }
    return *this;
	}

	iterator operator-(const int _Off) const noexcept {
		iterator _Tmp = *this;
		_Tmp -= _Off;
		return _Tmp;
	}

	friend iterator operator-(const int _Off, iterator _Next) noexcept {
		_Next -= _Off;
		return _Next;
	}
	friend bool operator==(const iterator& l, const iterator& r) noexcept {
		return l.end == r.end && l.begin == r.begin;
	}
	friend bool operator!=(const iterator& l, const iterator& r) noexcept {
		return l.end != r.end || l.begin != r.begin;
	}

	bool IsEnd() {
		return begin == end;	
	}

	char operator*() {
		return *begin;
	}
};

size_t CountRightBefore(const char* source, char c) {
	size_t count = 0;
	const char* begin = source;
	const char* end = begin+strlen(source);
	while (begin != end) {
		if (*(begin++) == c) { break; }
		count++;
	}
	return count;
}

bool CharInString(const char* str, char c) {
	const char* begin = str;
	const char* end = begin+strlen(str);
	while (begin != end) {
		if (*(begin++) == c) {
			return true;
		}
	}
	return false;
}

size_t CountRightBefore(const char* source, const char* c) {
	size_t count = 0;
	const char* begin = source;
	const char* end = begin+strlen(source);
	while (begin != end) {
		if (CharInString(c, *(begin++))) { break; }
		count++;
	}
	return count;
}

#endif