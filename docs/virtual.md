## Uses
```cpp
	using namespace Virtual;
	CodeBuilder builder;
	builder << Instruction_PUTS;
	builder << 0U;
	builder++; // or builder.Enter();
	builder += L"hellow, word";
	Code* code = *builder;
	Execute(*code);
``` 

## Reference
> `<type:1b>` - stack type

```asm
	<real_bit>
	-stack-
	push <type:1b> <value:4b>
	pop -no args-
	add <type:1b> <type:1b>
	sub <type:1b> <type:1b>
	mul <type:1b> <type:1b>
	div <type:1b> <type:1b>
	xor <type:1b> <type:1b>
	or  <type:1b> <type:1b>
	not <type:1b>
	and <type:1b> <type:1b>
	ls  <type:1b> <type:1b>
	rs  <type:1b> <type:1b>
	jmp <offset:4b>
	ret -no args-
	test -no args-
	j<if> <offset:4b>
	mov <type:1b> <address:4b>
	mset -start- -size- -value- 
	putc <char:2b>
	puti -stack head-
	puts <address:4b>
	call <proc-idx:4b>
```
> next addition float math 

### call 
```
	call 0
```
