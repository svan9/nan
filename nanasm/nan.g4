grammar nan;

WS: [\t\r\n\f ] -> channel(HIDDEN);

program: line*;

line
	: entry
	| data
	| label
	| instr
;

data: 'data' MOD WORD (STRING | size_t);
entry: 'entry' WORD;
label: WORD ':';
instr
	: call
	| puts
	| puti
	| push
	| pop
	| rpop
	| inc
	| dec
	| gch
	| add
	| div
	| mul
	| sub
	| test
	| jel
	| jem
	| je
	| jl
	| jm
	| jne
	| jmp
	| ret
	| xor
	| or
	| not
	| and
	| ls
	| rs
	| mov
	| swap
	| mset
	| swst
	| write
	| read
	| open
	| putc
	;

call: 'call' WORD;
puts: 'puts' WORD;
puti: 'puti' any_arg;
push: 'push' any_arg;
pop: 'pop';
rpop: 'pop' register;
inc: 'inc' any_arg;
dec: 'dec' any_arg;
gch: 'gch' any_arg;
add: 'add' dua_arg;
div: 'div' dua_arg;
mul: 'mul' dua_arg;
sub: 'sub' dua_arg;
test: 'test';
jel: 'jel' WORD;
jem: 'jem' WORD;
je: 'je' WORD;
jl: 'el' WORD;
jm: 'jm' WORD;
jne: 'jne' WORD;
jmp: 'jmp' WORD;
ret: 'ret';
xor: 'xor' dua_arg;	
or: 'or' dua_arg;
not: 'not' any_arg;
and: 'and' dua_arg;
ls: 'ls' dua_arg;
rs: 'rs' dua_arg;
mov: 'mov' dua_arg;
swap: 'swap' dua_arg;
mset: 'mset' tre_arg;
swst: 'swst' any_arg;
write: 'write' any_arg;
read: 'read' any_arg;
open: 'open' any_arg;
putc: 'putc' any_arg;

tre_arg: any_arg ',' any_arg ',' any_arg;
dua_arg: any_arg ',' any_arg;
any_arg: (register | rdi_offset | NUMBER);
register: '(' WORD ')';
rdi_offset: '(' 'rdi' NUMBER ')';
size_t: '[' NUMBER ']';

MOD: 'db' | 'da';
NUMBER: ('-' | '+')? [0-9_]+;
WORD: [a-zA-Z_][a-zA-Z_0-9]*;
FLAG: [@][a-zA-Z_][a-zA-Z_0-9]*;
OPERATORS: ('*' | '+' | '-' | '%' | '==' | '!=' | '<' | '>' | '<=' | '>=' | '&&' | '||' | '!' | '=');
TYPEMOD: [&*]+;
STRING: '"' ~('"')* '"';
SSTRING: '\'' ~('\'')* '\'';