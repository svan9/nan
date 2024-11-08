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

#ifndef DISABLE_MEW_PING
	#define __mew printf("-- mew at %s:%i, %s(...) --\n", __FILE__, __LINE__, __func__);
	#define _mew() __mew;
	#define MEWMEW __mew
	#define ____MEWMEW____ __mew
#endif

#ifndef DISABLE_MEW_MATH

#define MEW_POW2(expr) ((expr)*(expr))
#define MEW_IN_RANGE(min, max, value) ((min) <= (value) && (value) >= (max))

#define MEW_RANGE_EQ_PRT(lexpr, rexpr, range) ()

#define MEW_RANGE_EQ(lexpr, rexpr, range) (  \
		(lexpr) == (rexpr) ||                    \
		MEW_IN_RANGE((lexpr)-(range), (lexpr)+(range), rexpr))
#endif

#endif