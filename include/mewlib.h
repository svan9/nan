/**************************************************
 * - Author: so2u
 * - Create Time: 2024-11-28 17:48:15
 * - Git: https://github.com/svan9
 **************************************************/

#ifndef MewLib_IMPL
#define MewLib_IMPL

#include <stdlib.h>
#include <stdio.h>

#ifndef MEW_NO_RELEASE
	#define MEW_NO_RELEASE
#endif
#ifndef MEW_USE_THROWS
	#define MEW_USE_THROWS
#endif

#ifndef MEW_NO_RELEASE
	#ifndef DEBUG
		#define RELEASE
	#endif
#endif

#if defined(__cplusplus) && __cplusplus >= 202002L
	#define __CXX20
#endif

#if defined(__cplusplus) && defined(MEW_USE_THROWS) 
#undef MEW_USE_THROWS
#endif 

#ifndef NULLVAL
#define NULLVAL ((void)0)
#endif

#ifdef __cplusplus
	#include <exception>
#endif

#ifdef RELEASE
	#define __mewassert(strexpr, message, file, line, func) NULLVAL
	#define __mewassert_nm(strexpr, file, line, func) NULLVAL
#else
	#define __mewassert(strexpr, message, file, line, func) \
		printf("\nAssert failed at %s:%i, %s(...)\n  With expression (%s)\n  `%s`", file, line, func, strexpr, message);
	#define __mewassert_nm(strexpr, file, line, func) \
		printf("\nAssert failed at %s:%i, %s(...)\n  With expression (%s)\n", file, line, func, strexpr);
	#define __mewassert_r(strexpr, message, file, line, func) \
		"\nAssert failed at %s:%i, %s(...)\n  With expression (%s)\n  `%s`", file, line, func, strexpr, message
	#define __mewassert_nm_r(strexpr, file, line, func) \
		"\nAssert failed at %s:%i, %s(...)\n  With expression (%s)\n", file, line, func, strexpr
#endif

#if defined(MEW_USE_THROWS) && __cplusplus
	#define MewUserAssert(expr, message) \
		if (!(expr)) { throw std::runtime_error(message); }
	#define MewAssert(expr) \
		if (!(expr)) { throw std::runtime_error(#expr);}
#else
	#define MewUserAssert(expr, message) \
		if (!(expr)) {__mewassert(#expr, message, __FILE__, __LINE__, __func__); exit(1); }
	#define MewAssert(expr) \
		if (!(expr)) {__mewassert_nm(#expr, __FILE__, __LINE__, __func__); exit(1); }
#endif
#define MewNot() MewUserAssert(false, "not")
#define MewNoImpl() MewUserAssert(false, "not implemented")
#define MewNotImpl() MewUserAssert(false, "not implemented")
#define MewWarn(fmt, ...) printf("-- MEW WARN " fmt " --\n", __VA_ARGS__)

#ifndef DISABLE_MEW_PING
	#define __mew printf("-- mew at %s:%i, %s(...) --\n", __FILE__, __LINE__, __func__);
	#define _mew() __mew;
	#define MEWMEW __mew
	#define ____MEWMEW____ __mew
#endif

#ifndef DISABLE_MEW_MATH
	#define MEW_FIND_MASK(_val, _flag) (((_val) & (_flag)) == (_flag))
	#ifdef __cplusplus
		#define MEW_ADD_MASK(_val, _flag) (decltype(_val))((int)(_val) | (int)(_flag))
	#else
		#define MEW_ADD_MASK(_val, _flag) ((_val) | (_flag))
	#endif

	bool __mew_bvtr(bool s) { return true; }

	#define MEW_ONE_OR_NONE(_el) (__mew_bvtr(_el))
	#define MEW_POW2(expr) ((expr)*(expr))
	#define MEW_IN_RANGE(min, max, value) ((min) <= (value) && (value) <= (max))
	#define MEW_RM_ALIGN(value, align) ((value) - ((value) % (align)))
	#define MEW_RM_ALIGN_A(value, align) ((value) + ((value) % (align)))

	#define MEW_RANGE_EQ_PRT(lexpr, rexpr, range) ()

	#define MEW_RANGE_EQ(lexpr, rexpr, range) (  \
			(lexpr) == (rexpr) ||                    \
			MEW_IN_RANGE((lexpr)-(range), (lexpr)+(range), rexpr))
#endif

#ifdef __cplusplus
	#define MewPrintError(_error) printf("\nErrored from %s:%i at function `%s(...)`\n\twhat: %s", __FILE__, __LINE__, __func__, (_error).what());

	#include <string.h>
	#include <string>
	#include <wchar.h>
	#include <concepts>

char *ansi(wchar_t *unicode) {
	size_t size = wcslen(unicode);
	char* buffer = new char[size+1]; 
	for (int i = 0; i < size; i++) {
		buffer[i] = wctob(unicode[i]);
	}
	buffer[size] = '\0';
	return buffer;
}

namespace mew {
#ifdef __CXX20
	template<typename>
	struct ClearType;

	template<typename T>
	struct ClearType<T*> {
		typedef T type;
	};

	template<typename T, size_t size>
	struct ClearType<T[size]> {
		typedef T type;
	};

	template<typename T>
	struct ClearType<const T> {
		typedef T type;
	};

	template<typename T>
	struct ClearType<const T&> {
		typedef T type;
	};

	template<typename T>
	struct ClearType<const T*> {
		typedef T type;
	};

	template<typename T>
	struct ClearType {
		typedef T type;
	};
	
	template<typename Base, typename Derived>
	concept baseof = std::is_base_of_v<ClearType<Base>, ClearType<Derived>>;

	template<typename VF, typename VS>
	concept same_as = std::same_as<ClearType<VF>, ClearType<VS>>;

#endif
	class Error: public std::exception {
	private:
		std::string msg;
	public:
		Error() {
			
		}

    const char* what() const throw() {
			return msg.c_str();
    }
	};

namespace string {
	class StringIterator {
	public:
		const char *cbegin, *begin, *end;
		typedef StringIterator iterator;
		typedef const StringIterator const_iterator;

		////////////////////////////////////////////////////////////
		StringIterator() {}

		////////////////////////////////////////////////////////////
		StringIterator(const char* source): cbegin(source), begin(source), end(source+strlen(source)) {}

		////////////////////////////////////////////////////////////
		iterator Begin() {
			return iterator(*this);
		}

		////////////////////////////////////////////////////////////
		iterator End() {
			return iterator(*this)+(end-begin);
		}
		
		////////////////////////////////////////////////////////////
		bool IncCheck(int v = 1) {
			return begin+v == end;
		}
				
		////////////////////////////////////////////////////////////
		bool DecCheck(int v = 1) {
			return begin-v == cbegin;
		}

		////////////////////////////////////////////////////////////
		iterator& operator++() {
			if (IncCheck()) { begin++; }
			return *this;
		}
		
		////////////////////////////////////////////////////////////
		iterator operator++(int) {
			iterator tmp(*this);
			operator++();
			return tmp;
		}
		
		////////////////////////////////////////////////////////////
		iterator& operator--() {
			if (DecCheck()) { begin--; }
			return *this;
		}

		////////////////////////////////////////////////////////////
		iterator operator--(int) {
			iterator tmp(*this);
			operator--();
			return tmp;
		}  

		////////////////////////////////////////////////////////////
		iterator& operator+=(const int v) noexcept {
			if (IncCheck(v)) { begin += v; }
			return *this;
		}

		///////////////////////////////////////////////////////////.
		iterator operator+(const int _Off) const noexcept {
			iterator _Tmp = *this;
			_Tmp += _Off;
			return _Tmp;
		}

		////////////////////////////////////////////////////////////
		friend iterator operator+(const int _Off, iterator _Next) noexcept {
			_Next += _Off;
			return _Next;
		}

		////////////////////////////////////////////////////////////
		iterator& operator-=(const int v) noexcept {
			if (DecCheck(v)) { begin += v; }
			return *this;
		}

		////////////////////////////////////////////////////////////
		iterator operator-(const int _Off) const noexcept {
			iterator _Tmp = *this;
			_Tmp -= _Off;
			return _Tmp;
		}

		////////////////////////////////////////////////////////////
		friend iterator operator-(const int _Off, iterator _Next) noexcept {
			_Next -= _Off;
			return _Next;
		}

		////////////////////////////////////////////////////////////
		friend bool operator==(const iterator& l, const iterator& r) noexcept {
			return l.end == r.end && l.begin == r.begin;
		}

		////////////////////////////////////////////////////////////
		friend bool operator!=(const iterator& l, const iterator& r) noexcept {
			return l.end != r.end || l.begin != r.begin;
		}

		////////////////////////////////////////////////////////////
		bool IsEnd() {
			return begin == end;	
		}

		////////////////////////////////////////////////////////////
		char operator*() {
			return *begin;
		}

		////////////////////////////////////////////////////////////
		static char BeginChar(const char* source) {
			return *(source);
		}

		////////////////////////////////////////////////////////////
		static char EndChar(const char* source) {
			return *(strlen(source)+source-1);
		}

		////////////////////////////////////////////////////////////
		static bool HasChar(const char* source, char c) {
			for (int i = 0; i < strlen(source); i++) {
				if (source[i] == c) {
					return true;
				}
			}
			return false;
		}

		////////////////////////////////////////////////////////////
		static bool HasCharNoCase(const char* source, char c) {
			for (int i = 0; i < strlen(source); i++) {
				if (tolower(source[i]) == tolower(c)) {
					return true;
				}
			}
			return false;
		}

		////////////////////////////////////////////////////////////
		static bool HasChars(const char* source, char* c) {
			bool value = false;
			for (int i = 0; i < strlen(c); i++) {
				value &= HasChar(source, c[i]);
			}
			return value;
		}

		////////////////////////////////////////////////////////////
		static bool HasCharsNoCase(const char* source, char* c) {
			bool value = false;
			for (int i = 0; i < strlen(c); i++) {
				value &= HasCharNoCase(source, c[i]);
			}
			return value;
		}
	};

	////////////////////////////////////////////////////////////
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

	////////////////////////////////////////////////////////////
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
	
	////////////////////////////////////////////////////////////
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
}

namespace Lib {
	enum struct NumberType {
		None 			= 0,
		Unsigned 	= 1 << 0,
		Float 		= 1 << 1,
		Int 			= 1 << 2,
		Double 		= 1 << 3,
		Char 			= 1 << 4,
	};

	struct RawNumber {
		NumberType type;
		union {
			float float_v;
			int int_v;
			double double_v;
			char char_v;
		};
	};
}
	
}

#endif

#endif