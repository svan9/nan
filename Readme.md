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
