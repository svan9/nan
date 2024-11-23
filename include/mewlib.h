#ifndef MewLib_IMPL
#define MewLib_IMPL

#define __mewassert(strexpr, message, file, line, func) \
	printf("\nAssert failed at %s:%i, %s(...)\n  With expression (%s)\n  `%s`", file, line, func, strexpr, message);
#define __mewassert_nm(strexpr, file, line, func) \
	printf("\nAssert failed at %s:%i, %s(...)\n  With expression (%s)\n", file, line, func, strexpr);
#define MewUserAssert(expr, message) if (!(expr)) {__mewassert(#expr, message, __FILE__, __LINE__, __func__); exit(1); }
#define MewAssert(expr) if (!(expr)) {__mewassert_nm(#expr, __FILE__, __LINE__, __func__); exit(1); }
#define MewNot() MewUserAssert(false, "not")
#define MewNoImpl() MewUserAssert(false, "not implemented")
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
	
	#define MEW_POW2(expr) ((expr)*(expr))
	#define MEW_IN_RANGE(min, max, value) ((min) <= (value) && (value) >= (max))

	#define MEW_RANGE_EQ_PRT(lexpr, rexpr, range) ()

	#define MEW_RANGE_EQ(lexpr, rexpr, range) (  \
			(lexpr) == (rexpr) ||                    \
			MEW_IN_RANGE((lexpr)-(range), (lexpr)+(range), rexpr))
#endif

#ifdef __cplusplus
	#define MewPrintError(_error) printf("\nErrored from %s:%i at function `%s(...)`\n\twhat: %s", __FILE__, __LINE__, __func__, (_error).what());

	#include <concepts>

namespace Mew {
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
	concept BaseOf = std::is_base_of_v<ClearType<Base>, ClearType<Derived>>;

	namespace String {
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

			static char BeginChar(const char* source) {
				return *(source);
			}
			static char EndChar(const char* source) {
				return *(strlen(source)+source-1);
			}

			static bool HasChar(const char* source, char c) {
				for (int i = 0; i < strlen(source); i++) {
					if (source[i] == c) {
						return true;
					}
				}
				return false;
			}

			static bool HasCharNoCase(const char* source, char c) {
				for (int i = 0; i < strlen(source); i++) {
					if (tolower(source[i]) == tolower(c)) {
						return true;
					}
				}
				return false;
			}

			static bool HasChars(const char* source, char* c) {
				bool value = false;
				for (int i = 0; i < strlen(c); i++) {
					value &= HasChar(source, c[i]);
				}
				return value;
			}

			static bool HasCharsNoCase(const char* source, char* c) {
				bool value = false;
				for (int i = 0; i < strlen(c); i++) {
					value &= HasCharNoCase(source, c[i]);
				}
				return value;
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

		class Number {
		private:
			NumberType container_type;
			void* _M_value;
		public:
			////////////////////////////////////////////////////////////
			Number() { container_type = NumberType::None; }

			////////////////////////////////////////////////////////////
			Number(const char* str) { 
				StringIterator it(str);
				NumberType ntype = NumberType::Int;
				char buffer[strlen(str)+1];
				int i = 0;
				while (!it.IsEnd()) {
					char c = *it++;
					if (c == '.') {
						ntype = NumberType::Double;
						buffer[i++] = c;
					} else if(isdigit(c)) {
						buffer[i++] = c;
					}
				}
				buffer[i] = '\0';
				if (StringIterator::HasCharNoCase(str, 'D')) {
					ntype = NumberType::Double;
					double v = atof(buffer);
					_M_value = &v;
				} 
				else if (StringIterator::HasCharNoCase(str, 'F')) {
					ntype = NumberType::Float;
					float v = atof(buffer);
					_M_value = &v;
				}
				else if (StringIterator::HasCharNoCase(str, 'I')) {
					ntype = NumberType::Int;
					int v = atoi(buffer);
					_M_value = &v;
				}
				else if (StringIterator::HasCharNoCase(str, 'C')) {
					ntype = NumberType::Char;
					_M_value = (void*)buffer;
				}
				if (StringIterator::HasCharNoCase(str, 'U')) {
					ntype = MEW_ADD_MASK(ntype, (int)NumberType::Unsigned);
				}
				container_type = ntype;
			}

			////////////////////////////////////////////////////////////
			Number(int&& value) { 
				container_type = NumberType::Int; 
				_M_value = &value;
			}

			////////////////////////////////////////////////////////////
			Number(float&& value) { 
				container_type = NumberType::Float; 
				_M_value = &value;
			}
			
			////////////////////////////////////////////////////////////
			Number(double&& value) { 
				container_type = NumberType::Double; 
				_M_value = &value;
			}
			
			////////////////////////////////////////////////////////////
			Number(char&& value) { 
				container_type = NumberType::Char; 
				_M_value = &value;
			}
			
			template<typename T>
			////////////////////////////////////////////////////////////
			void unpack(T* container) {
				static_assert(
					(std::same_as<T, int> && container_type == NumberType::Int) ||
					(std::same_as<T, float> && container_type == NumberType::Float) ||
					(std::same_as<T, char> && container_type == NumberType::Char) ||
					(std::same_as<T, double> && container_type == NumberType::Double) ||
				);
				*container = *(T*)_M_value;
			}

			template<typename T>
			////////////////////////////////////////////////////////////
			T unpack_raw() {
				return *(T*)_M_value;
			}

			template<typename T>
			////////////////////////////////////////////////////////////
			T unpack() {
				T value;
				unpack(&value);
				return value;
			}	
			
			bool is_Int() const noexcept {
				return container_type == NumberType::Int;
			}
			bool is_float() const noexcept {
				return container_type == NumberType::Float;
			}
			bool is_char() const noexcept {
				return container_type == NumberType::Char;
			}
			bool is_Double() const noexcept {
				return container_type == NumberType::Double;
			}
		};

	}
	
}

#endif

#endif