grammar nan;

WS: [\t\r\n\f ] -> channel(HIDDEN);

program: line*;

line
	: entry
	| data
	| label
	| instr
;

data: 'data' MOD WORD STRING;
entry: 'entry' WORD;
label: WORD ':';
instr
	: puts 
	| puti
	| push
	| inc
	| test
	| jel
	| jem
	| je
	| jl
	| jm
	| jne
	| jmp
	| ret
	;

puts: 'puts' WORD;
puti: 'puti' rdi_offset;
push: 'push' (NUMBER | rdi_offset);
inc: 'inc' rdi_offset;
test: 'test';
jel: 'jel' WORD;
jem: 'jem' WORD;
je: 'je' WORD;
jl: 'el' WORD;
jm: 'jm' WORD;
jne: 'jne' WORD;
jmp: 'jmp' WORD;
ret: 'ret';


rdi_offset: '(' 'rdi' NUMBER ')';

MOD: 'db';
NUMBER: ('-' | '+')? [0-9_]+;
WORD: [a-zA-Z_][a-zA-Z_0-9]*;
FLAG: [@][a-zA-Z_][a-zA-Z_0-9]*;
OPERATORS: ('*' | '+' | '-' | '%' | '==' | '!=' | '<' | '>' | '<=' | '>=' | '&&' | '||' | '!' | '=');
TYPEMOD: [&*]+;
STRING: '"' ~('"')* '"';
SSTRING: '\'' ~('\'')* '\'';