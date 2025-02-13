import vm from "./vm.js"

function numToUint8Array(num) {
  let arr = new Uint8Array(4);
  for (let i = 0; i < 8; i++) {
    arr[i] = num % 256;
    num = Math.floor(num / 256);
  }
  return arr;
}
function numToInt8Array(num) {
  let arr = new Int8Array(4);
  for (let i = 0; i < 8; i++) {
    arr[i] = num % 256;
    num = Math.floor(num / 256);
  }
  return arr;
}

function abs_add(a, b) {
	return a < 0? a-b: a+b;
}

export default class CodeBuilder {
	fns = {}
	global_block  = {}
	current_block = {}
	labels = {}
	data = {}
	code = "";
	current_code_cursor = 0;
	current_code = new Uint8Array();
	defines = {}
	entry = ""
	constructor() { }

	add(code) {
		if (this.current_code.length <= this.current_code_cursor) {
			let temp = new Uint8Array(this.current_code.length+64);
			temp.set(this.current_code);
			this.current_code = temp;
		}
		this.current_code[this.current_code_cursor++] = code;
	}

	add_data(mod, name, value) {
		if (mod == "db") {
			this.data[name] = value
				.replace(/\\0/gm, "\0")
				.replace(/\\n/gm, "\n")
				.replace(/\\t/gm, "\t")
				.replace(/\\r/gm, "\r")
				.slice(1, -1)
			return this.data[name];
		}
	}

	get_data_pos(name) {
		let offset = 0;
		for (let [k, v] of Object.entries(this.data)) {
			if (k == name) {
				return offset;
			}
			offset += v.length;
		}
		return void 0;
	}

	get_data_length() {
		let length = 0;
		for (let [k, v] of Object.entries(this.data)) {
			length += v.length;
		}
		return length;
	}
	
	_puts(name) {
		let offset = this.get_data_pos(name);
		if (offset == void 0) {return false;}
		this.add(vm.Instruction["PUTS"]);
		this.addUint(offset);
		return true;
	}

	_puti(offset) {
		this.add(vm.Instruction["PUTI"])
		this.addUint(offset)
		this.add(vm.Instruction["NUM"])
	}
	_test() {
		this.add(vm.Instruction["TEST"])
		this.add(vm.Instruction["NUM"])
		this.add(vm.Instruction["NUM"])
	}

	_push(value) {
		this.add(vm.Instruction["PUSH"]);
		this.add(vm.Instruction["NUM"]);
		this.addUint(value);
	}

	_inc(value) {
		this.add(vm.Instruction["INC"]);
		this.addUint(value);
	}
	_dec(value) {
		this.add(vm.Instruction["DEC"]);
		this.addUint(value);
	}

	_add(a, b) {
		this.add(vm.Instruction["ADD"]);
		this.addUint(a);
		this.addUint(b);
	}

	_sub(a, b) {
		this.add(vm.Instruction["SUB"]);
		this.addUint(a);
		this.addUint(b);
	}

	_mul(a, b) {
		this.add(vm.Instruction["MUL"]);
		this.addUint(a);
		this.addUint(b);
	}

	_div(a, b) {
		this.add(vm.Instruction["DIV"]);
		this.addUint(a);
		this.addUint(b);
	}
	_jel(name) {
		this.add(vm.Instruction['JEL']);
		if (this.labels[name] == void 0) {
			this.defines[name] = this.defines[name] ?? [];
			this.defines[name].push(Number(this.current_code_cursor));
			this.current_code_cursor += 4;
		} else {
			this.addInt(this.current_code_cursor-this.labels[name])
		}
	}
	_jem(name) {
		this.add(vm.Instruction['JEM']);
		if (this.labels[name] == void 0) {
			this.defines[name] = this.defines[name] ?? [];
			this.defines[name].push(Number(this.current_code_cursor));
			this.current_code_cursor += 4;
		} else {
			this.addInt(this.current_code_cursor-this.labels[name])
		}
	}
	_je(name) {
		this.add(vm.Instruction['JE']);
		if (this.labels[name] == void 0) {
			this.defines[name] = this.defines[name] ?? [];
			this.defines[name].push(Number(this.current_code_cursor));
			this.current_code_cursor += 4;
		} else {
			this.addInt(this.current_code_cursor-this.labels[name])
		}
	}
	_jl(name) {
		this.add(vm.Instruction['JL']);
		if (this.labels[name] == void 0) {
			this.defines[name] = this.defines[name] ?? [];
			this.defines[name].push(Number(this.current_code_cursor));
			this.current_code_cursor += 4;
		} else {
			this.addInt(this.current_code_cursor-this.labels[name])
		}
	}
	_jm(name) {
		this.add(vm.Instruction['JM']);
		if (this.labels[name] == void 0) {
			this.defines[name] = this.defines[name] ?? [];
			this.defines[name].push(Number(this.current_code_cursor));
			this.current_code_cursor += 4;
		} else {
			this.addInt(this.current_code_cursor-this.labels[name])
		}
	}
	_jne(name) {
		this.add(vm.Instruction['JNE']);
		if (this.labels[name] == void 0) {
			this.defines[name] = this.defines[name] ?? [];
			this.defines[name].push(Number(this.current_code_cursor));
			this.current_code_cursor += 4;
		} else {
			this.addInt(this.current_code_cursor-this.labels[name])
		}
	}
	_jmp(name) {
		this.add(vm.Instruction['JMP']);
		if (this.labels[name] == void 0) {
			this.defines[name] = this.defines[name] ?? [];
			this.defines[name].push(Number(this.current_code_cursor));
			this.current_code_cursor += 4;
		} else {
			this.addInt(this.labels[name]-(this.current_code_cursor+4))
		}
	}
	_ret() {
		this.add(vm.Instruction['RET']);
	}
	markLabel(name) {
		if (this.defines[name] != void 0) {
			this.defines[name].forEach(e=>{
				this.setInt(this.current_code_cursor-e, e)
			});
			this.defines[name] = void 0;
		}
		this.labels[name] = this.current_code_cursor;
	}
	markEntry(name) {
		this.entry = name;
	}
	setInt(code, pos) {
		console.log(code)
		this.current_code.set((
			code < 0 
				? numToInt8Array(code) 
				: numToUint8Array(code)),
				pos);
	}
	addInt(code) {
		console.log(code)
		this.current_code.set((
			code < 0 
				? numToInt8Array(code) 
				: numToUint8Array(code)),
			this.current_code_cursor);
		this.current_code_cursor += 4;
	}
	addUint(code) {
		this.current_code.set(numToUint8Array(code), this.current_code_cursor);
		this.current_code_cursor += 4;
	}

	pushFunction(fn) {
		this.fns[fn.name] = fn;
	}


	addCallFunction(fn, args) {
		for (let i = 0; i < args.argc; ++i) {
			// this.add(vm.Instruction.PUSH);
			// this.add(vm.Instruction.);
			console.log(args.content[i]);
		}
		// args.forEach(arg => {
		// });	
		// this.fns[fn.name]
		console.log(args);
	}

	buildFunction(fn) {
		
	}

	getFunction(name) {
		return this.fns[name];
	}
	
	beginBlock() {
		this.current_block = {
			"vars": {}		
		};
	}

	pushVar(obj) {
		this.current_block.vars[obj.name] = obj; 
	}
	
	endBlock() {
		this.current_block = {
			"vars": {}		
		};
	}

	build() {
		let data_size = this.get_data_length();
		let len = this.current_code_cursor + data_size + 13;
		// len = (data_size-len)+this.current_code_cursor + 12;
		let arr = new Uint8Array(len);
		let data_arr = new Uint8Array(data_size);
		let data_cursor = 0;
		for (let [k, v] of Object.entries(this.data)) {
			let val = Uint8Array
				.from(v
					.split('')
					.map(letter => letter.charCodeAt(0)));
			this.current_code.set(val, this.current_code_cursor++);
			data_arr.set(val, data_cursor);
			data_cursor += v.length;
		}
		/** MANIFEST */
		const manifest_length = 12;
		// version 0+4
		arr.set(numToUint8Array(4652), 0); 
		// code length 4+4
		arr.set(numToUint8Array(this.current_code_cursor), 4);
		// data length
		arr.set(numToUint8Array(data_size), 8);
		/** SECTIONS */
		// code 8+n
		arr.set(this.current_code.subarray(0, this.current_code_cursor-1), manifest_length);
		// data
		arr.set(data_arr, this.current_code_cursor+manifest_length)
		return arr;
	}
};