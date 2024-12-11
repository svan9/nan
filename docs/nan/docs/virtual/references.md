---
sidebar_position: 3
---

### all 
```asm
	<real_bit>
	-stack-
	push <type:1b> <value:4b>
	pop -no args-
	add <type:1b> <type:1b>
	sub <type:1b> <type:1b>
	mul <type:1b> <type:1b>
	div <type:1b> <type:1b>
	inc <type:1b>
	dec <type:1b>
	xor <type:1b> <type:1b>
	or  <type:1b> <type:1b>
	not <type:1b>
	and <type:1b> <type:1b>
	ls  <type:1b> <type:1b>
	rs  <type:1b> <type:1b>
	jmp <offset:4b>
	ret -no args-
	test <type:1b> <type:1b>
	j<if> <offset:4b>
	mov <type:1b> <address:4b>
	mset <start> <size> <value> 
	putc <char:2b>
	puti -stack head-
	puts <address:4b>
	call <proc-idx:4b>
	swst <?use_stack:1b> <idx:4b>
	| swst 'true' <stack_type:1b> -idx:4b-
	| swst 'false' <idx:4b>
	write <address:4b>
	read <address:4b> <chunsize:2b>
		!uses simple char for path
	open <address:4b> <flags:4b>
```
> next addition float math 

### types
- Instruction_NUM  - simple number
- Instruction_MEM  - (unpack memory value) pointer offset to heap data
- Instruction_RMEM - (raw memory pointer) pointer offset to heap data


### push
Adds to stack n value
```cpp
	// push <type:1b> <value:4b>
	builder << Instruction_PUSH << Instruction_NUM << 2; 
```

### pop
Removes top element from stack
```cpp
	// pop [no args]
	builder << Instruction_POP; 
```

### add
Math operation add, adds to numbers from stack.
If first argument type is MEM changes to poiner value 
```cpp
	// add <type:1b> <type:1b>
	builder << Instruction_ADD << Instruction_NUM << Instruction_NUM; 
```
### sub
Math operation sub, subs to numbers from stack.
If first argument type is MEM changes to poiner value 
```cpp
	// sub <type:1b> <type:1b>
	builder << Instruction_SUB << Instruction_NUM << Instruction_NUM; 
```
### mul
Math operation mul, muls to numbers from stack.
If first argument type is MEM changes to poiner value 
```cpp
	// mul <type:1b> <type:1b>
	builder << Instruction_MUL << Instruction_NUM << Instruction_NUM; 
```
### div
Math operation div, divs to numbers from stack.
If first argument type is MEM changes to poiner value 
```cpp
	// div <type:1b> <type:1b>
	builder << Instruction_DIV << Instruction_NUM << Instruction_NUM; 
```
### inc
Math operation inc, increases the value from stack.
If first argument type is MEM changes to poiner value 
```cpp
	// inc <type:1b>
	builder << Instruction_INC << Instruction_NUM; 
```
### dec
Math operation dec, reduces the value from stack.
If first argument type is MEM changes to poiner value 
```cpp
	// dev <type:1b>
	builder << Instruction_DEC << Instruction_NUM; 
```
### xor
Math operation xor, 'xor'es the value from stack.
If first argument type is MEM changes to poiner value 
```cpp
	// xor <type:1b> <type:1b>
	builder << Instruction_XOR << Instruction_NUM << Instruction_NUM;
```
### or
Math operation or, 'or'es the value from stack.
If first argument type is MEM changes to poiner value 
```cpp
	// or <type:1b> <type:1b>
	builder << Instruction_OR << Instruction_NUM << Instruction_NUM;
```
### not
Math operation not, invert the value from stack.
If first argument type is MEM changes to poiner value 
```cpp
	// not <type:1b>
	builder << Instruction_NOT << Instruction_NUM;
```
### and
Math operation and, 'and'es the value from stack.
If first argument type is MEM changes to poiner value 
```cpp
	// and <type:1b> <type:1b>
	builder << Instruction_AND << Instruction_NUM << Instruction_NUM;
```
### ls
Math operation ls, binary left shift the value from stack.
If first argument type is MEM changes to poiner value 
```cpp
	// ls <type:1b> <type:1b>
	builder << Instruction_LS << Instruction_NUM << Instruction_NUM;
```
### rs
Math operation rs, binary right shift the value from stack.
If first argument type is MEM changes to poiner value 
```cpp
	// rs <type:1b> <type:1b>
	builder << Instruction_RS << Instruction_NUM << Instruction_NUM;
```
### jmp
jump with offset, uses integer for offset, can jump with negarive and positive offset
```cpp
	// jmp <offset:4b>
	builder << Instruction_JMP << 10;
```
### ret
returns to last jump
```cpp
	// ret [no args]
	builder << Instruction_RET;
```
### test
tests two numbers by bytes compare. Write to special register result
```cpp
	// test <type:1b> <type:1b>
	builder << Instruction_TEST << Instruction_NUM << Instruction_NUM;
```
### j\<cond>
Like [jump](#jmp), but uses special test register. If conditional match jump, else not.
all variants:
- JNE - jump if not equal
- JEL - jump if equal and less
- JEM - jump if equal and more
- JM - jump if more
- JL - jump if less
```cpp
	// j<cond> <offset:4b>
	builder << Instruction_J[__] << 10;
```
### mov
Moves from stack head to pointer offset, unsigned int value
```cpp
	// mov <type:1b> <offset:4b>
	builder << Instruction_MOV << Instruction_NUM << 0U;
```
### mset
Sets pointer value with size and value
```cpp
	// mset <start:4b> <size:4b> <value:4b>
	builder << Instruction_MSET << 0U << sizeof(uint) << 0U;
```

### putc
Puts wchar_t to console 
```cpp
	// putc <char:2b>
	builder << Instruction_PUTC << L'a';
```
### putc
Puts integer to console from stack
```cpp
	// puti -stack head-
	builder << Instruction_PUTI << Instruction_NUM;
```
### puts
Puts wchar_t string to console ends with zero byte
```cpp
	// puts <address:4b>
	builder << Instruction_PUTI << Instruction_NUM;
```

### call
```cpp
	// call <proc-idx:4b>
	TODO NOT IMPL
```
### swst
Open stream by destinator and sets current file stream
```cpp
// swst <?use_stack:1b> <idx:4b>
```
#### usage const dest
```cpp
	// swst 'false' <idx:4b>
	builder << Instruction_SWST << (uint)false << 12U;
```
#### usage stack dest
```cpp
	//  swst 'true' <stack_type:1b> -idx:4b-
	builder << Instruction_SWST << (uint)true << Instruction_NUM;
```
### write
Writes to current stream char string
```cpp
	// write <address:4b>
	builder << Instruction_WRITE << 0U;
	builder += "Hellow";
```
### read
Reads from current stream char string with size (max chunk size = ~MAX_SHORT_VALUE~)
```cpp
	// read <address:4b> <chunsize:2b>
	builder << Instruction_READ << 0U << 15U;
```
### open
Opens file - gets file destinator and push in stack
```cpp
	// open <address:4b> <flags:4b>
	builder << Instruction_OPEN << 0U << _O_RDWR;
	builder += "path/to/file";
```