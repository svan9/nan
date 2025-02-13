```
LDLL
CALL
PUSH
POP

ADD -offset:4b- -offset:4b-
SUB -offset:4b- -offset:4b-
MUL -offset:4b- -offset:4b-
DIV -offset:4b- -offset:4b-

INC -offset:4b-
DEC -offset:4b-

XOR -offset:4b- -offset:4b-
OR 	-offset:4b- -offset:4b-
NOT -offset:4b-
AND	-offset:4b- -offset:4b-
LS 	-offset:4b- -offset:4b-
RS	-offset:4b- -offset:4b-

JMP <offset:4b>
RET -no-args-
EXIT  
TEST -no-args-
JE 	<offset:4b>
JEL <offset:4b>
JEM <offset:4b>
JNE <offset:4b>
JL 	<offset:4b>
JM 	<offset:4b>
MOV -offset:4b- -offset:4b-
MSET

SWST
WRITE
READ
OPEN

PUTC [char:2b]
PUTI -offset:4b-
PUTS <offset:4b>
```