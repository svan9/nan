function get_enum(array) {
	let _enum = {};
	array.forEach((e,i) => {
		_enum[e] = i;
		_enum[i] = e;
	});
	return _enum;
} 

export default { 
	"Instruction": get_enum(["NONE","LDLL","CALL","PUSH","POP","ADD","SUB","MUL","DIV","INC","DEC","XOR","OR","NOT","AND","LS","RS","NUM","INT","FLT","DBL","UINT","BYTE","MEM","RMEM","HEAP","ST","JMP","RET","EXIT","TEST","JE","JEL","JEM","JNE","JL","JM","MOV","SWAP","MSET","SWST","WRITE","READ","OPEN","PUTC","PUTI","PUTS","MOVRDI",
	])
};