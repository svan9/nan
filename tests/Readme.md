# <div style="text-align: center">Futuries syntax for nan language</div>

# Some
```
let a: string;
```
let - keyword with unstatic type, nan assumes what type could be a string but if you put into ***a*** for example type of int32, it could be done.
```
let a: string;
a = 12;
``` 
______
```
	int      a       =          10          ;
	^^^     ^^^     ^^^         ^^^        ^^^
	type    name   operator     value      end of expression
```

`int a = 10;` - expression \
`int a` - expression -> declare \
`a = 10` - expression -> operator \
`10` - expression -> number 
____

```
entry {
	std::console::print("hellow, word");
	ret OK();
}
```
entry function. If you connect another files with entry, all entry calls by invert order (nan main.nan second.nan third.nan -> `third::entry -> second::entry -> main::entry`)

Entry returns Result<,err> type. Without return default value could be OK() eq 0 code;

```c
Result <float, err> foo() {
// get ranom float number [0, 1]
	float number = randf();
	if (number > 0.5) {
// retun Error
		ret Error("something wrong");
	}
// return 'ok' result with packed value
	ret OK(number);
}
```
Example function ***foo*** return random float value if number is less 0.5 return error


> default value of number with float point is \<float\> if you want double add ***d*** after `0.5d`

____
> connect native function in nanvm
```
extern float randf() @native;
```
> connect linked nan lib function
```
extern float foo(float) @lib;
```
> connect linked dll lib function
```
extern void putc(char) @dll;
```
Custom flags
----
```

Flag nothing {
	void operator()(`fn, ...args) {
		fn(...args);
		ret void;
	}
}

float foo() @nothing;
```
> foo function with custom flag ***nothing*** returns void value, ignore signature return type of function.

```rust
Result <float, err> foo() {
// get ranom float number [0, 1]
	byte* m = new(1);
	float number = randf();
	if (number > 0.5) {
// retun Error
		retn Error("something wrong");
	}
// return 'ok' result with packed value
	retn OK(number);
	free(m);
}
```
> retn - keyword store return value once and before execute next code without ending

# Extra variables
### #stack - includes all stack values
### #regs - includes all regs values, syntax: `#regs.r1`
### #rip_stack - includes stack of all rips
### #rip - includes current rip value
> gets address of function
```
void foo() {
	print("hellow");
}

reg16 foo_address = foo::#rip;
```
### #func - type of any functions
```rust
struct arg_pair {
	typename arg_type;
	WORD arg_name;
};

struct #func {
	reg16 #rip;
	u64 argc;
	`arg_pair args;
	typename ret_type;
};
```

# Binary in code
```
> syntax:
bin { code }
> uses external variable ('$' name)
bin { or $a $b }
> uses ret value of binary operations (grab last stack element)
ret bin { and $a $b }
```

# Generics
``` rust
> syntax
template<Typename>
> uses types
template<u64 Number>
> example:

trait numeric = int + float + double + char + boolean;

template<Typename1, u64 Number, numeric Num2> 
struct foo {
	Typename1 first;
	Number second;
	Num2 third;
};

```
# Traits
```cpp
> syntax
trair foo = ...
> example

// includes all types
trait numeric = int + float + double + char + boolean;

template<numeric T>
T operator+ (T a, T b) @nonpath @autogen {
	ret bin{add $a $b};
}
// type of arguments a & b can be different but matches trait 'numeric'

// includes all types
trait diff_numeric = int - float - double - char - boolean;

template<numeric T>
T operator+ (T a, T b) @nonpath @autogen {
	ret bin{add $a $b};
}
// type of arguments a & b must be equal and matches trait 'numeric'

```

# Typedef
```rust
> syntax 
type foo = ...;
> examples from std

type bool = boolean;
type str = const char*
type i8 = char;
type i16 = char * 2;
type i32 = char * 4;
type i64 = char * 8;
type u8 = byte;
type u16 = byte * 2;
type u32 = byte * 4;
type u64 = byte * 8;
```

# Modifiers for types
```rust
> pointer
`Type ptr;
> reference
Type& ref;
> copied reference
Type&& ref2 = ref;
> range pointer
Type* range; // {size_t start, size_t size}
```

# Flags
```d
> syntax
@flag
> build-in flags
@gen - constructor of current class-namespace
@copy - copy constructor
@move - move constructor
@safe - safe realization of function
@nonpath - global named of field
@autogen - generic field auto gen supported types (used in trait template functions)
@right - function-operator right side operator
@left - function-operator left side operator
@native - native realization of external fields (build-in field)
@operator - stringed operator function
@dll - external dll function (suppored in future)
```

# Class
In nan class is same as namespace but can have constructors
```rust
> syntax
expand class foo

struct {
	u64 a;
	char b;
}

This& () @gen {
	a = rand<u64>();
	b = 'x';
}


narrow class foo
```