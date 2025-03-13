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
	labels = {}
	data = {}
	cursor = 0;
	code = new Uint8Array();
	data_defines = {}
	defines = {}
	callings = {}
	entry = ""
	source = []
	debug_info = []
	constructor() { }

	write_source(ctx) {
		this.source = ctx.start.source[1].strdata.split(/\r\n/);
	}

	write_debug(ctx) {
		let number = ctx.start.line;
		// let src = this.source[number];
		let cursor = this.cursor;
		this.debug_info.push({number, cursor});
	}

	add(code) {
		if (this.code.length <= this.cursor) {
			let temp = new Uint8Array(this.code.length+64);
			temp.set(this.code);
			this.code = temp;
		}
		this.code[this.cursor++] = code;
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

	push_arg(arg) {
		switch(arg.type) {
			case "reg": {
				this.add(vm.Instruction["REG"]);
				this.add(arg.kind);
				this.add(arg.idx);		
			} break;
			case "number": {
				this.add(vm.Instruction["NUM"]);
				this.addUint(arg.value);		
			} break;
			case "rdi_offset": {
				this.add(vm.Instruction["ST"]);
				this.addUint(arg.value);
			} break;
		}
	}

	_mov(args) {
		this.add(vm.Instruction["MOV"]);
		this.push_arg(args[0])
		this.push_arg(args[1])
	}

	_call(name) {
		this.add(vm.Instruction['CALL']);
		if (this.labels[name] == void 0) {
			this.callings[name] = this.callings[name] ?? [];
			this.callings[name].push(Number(this.cursor));
			this.cursor += 4;
		} else {
			this.addInt(this.labels[name]-(this.cursor+4))
		}
	}
	
	_puts(name) {
		let offset = this.get_data_pos(name);
		if (offset == void 0) {return false;}
		this.add(vm.Instruction["PUTS"]);
		this.data_defines[name] = this.cursor;
		this.addUint(offset);
		return true;
	}

	_puti(offset) {
		this.add(vm.Instruction["PUTI"])
		this.addUint(offset)
		this.add(vm.Instruction["NUM"])
	}
	
	_gch(offset) {
		this.add(vm.Instruction["GETCH"])
		this.addUint(offset)
	}
	_test() {
		this.add(vm.Instruction["TEST"])
		this.add(vm.Instruction["NUM"])
		this.add(vm.Instruction["NUM"])
	}

	_push(value) {
		this.add(vm.Instruction["PUSH"]);
		this.push_arg(value);
	}

	_pop() {
		this.add(vm.Instruction["POP"]);
	}
	
	_rpop(val) {
		this.add(vm.Instruction["RPOP"]);
		this.add(val.kind);
		this.add(val.idx);
	}

	_inc(value) {
		this.add(vm.Instruction["INC"]);
		this.push_arg(value);
	}
	_dec(value) {
		this.add(vm.Instruction["DEC"]);
		this.push_arg(value);
	}

	_add(a, b) {
		this.add(vm.Instruction["ADD"]);
		this.push_arg(a);
		this.push_arg(b);
	}

	_sub(a, b) {
		this.add(vm.Instruction["SUB"]);
		this.push_arg(a);
		this.push_arg(b);
	}

	_mul(a, b) {
		this.add(vm.Instruction["MUL"]);
		this.push_arg(a);
		this.push_arg(b);
	}

	_div(a, b) {
		this.add(vm.Instruction["DIV"]);
		this.push_arg(a);
		this.push_arg(b);
	}
	_jel(name) {
		this.add(vm.Instruction['JEL']);
		if (this.labels[name] == void 0) {
			this.defines[name] = this.defines[name] ?? [];
			this.defines[name].push(Number(this.cursor));
			this.cursor += 4;
		} else {
			this.addInt(this.cursor-this.labels[name])
		}
	}
	_jem(name) {
		this.add(vm.Instruction['JEM']);
		if (this.labels[name] == void 0) {
			this.defines[name] = this.defines[name] ?? [];
			this.defines[name].push(Number(this.cursor));
			this.cursor += 4;
		} else {
			this.addInt(this.cursor-this.labels[name])
		}
	}
	_je(name) {
		this.add(vm.Instruction['JE']);
		if (this.labels[name] == void 0) {
			this.defines[name] = this.defines[name] ?? [];
			this.defines[name].push(Number(this.cursor));
			this.cursor += 4;
		} else {
			this.addInt(this.cursor-this.labels[name])
		}
	}
	_jl(name) {
		this.add(vm.Instruction['JL']);
		if (this.labels[name] == void 0) {
			this.defines[name] = this.defines[name] ?? [];
			this.defines[name].push(Number(this.cursor));
			this.cursor += 4;
		} else {
			this.addInt(this.cursor-this.labels[name])
		}
	}
	_jm(name) {
		this.add(vm.Instruction['JM']);
		if (this.labels[name] == void 0) {
			this.defines[name] = this.defines[name] ?? [];
			this.defines[name].push(Number(this.cursor));
			this.cursor += 4;
		} else {
			this.addInt(this.cursor-this.labels[name])
		}
	}
	_jne(name) {
		this.add(vm.Instruction['JNE']);
		if (this.labels[name] == void 0) {
			this.defines[name] = this.defines[name] ?? [];
			this.defines[name].push(Number(this.cursor));
			this.cursor += 4;
		} else {
			this.addInt(this.cursor-this.labels[name])
		}
	}
	_jmp(name) {
		this.add(vm.Instruction['JMP']);
		if (this.labels[name] == void 0) {
			this.defines[name] = this.defines[name] ?? [];
			this.defines[name].push(Number(this.cursor));
			this.cursor += 4;
		} else {
			this.addInt(this.labels[name]-(this.cursor+4))
		}
	}
	_ret() {
		this.add(vm.Instruction['RET']);
	}
	markLabel(name, cursor = void 0) {
		let c_cursor = cursor ?? this.cursor;
		if (this.defines[name] != void 0) {
			this.defines[name].forEach(e=>{
				this.setInt(c_cursor-e, e);
			});
			this.defines[name] = void 0;
		}
		this.labels[name] = c_cursor;
	}
	markEntry(name) {
		this.entry = name;
	}

	setInt(code, pos) {
		this.code.set((
			code < 0 
				? numToInt8Array(code) 
				: numToUint8Array(code)),
				pos);
	}
	
	extendIfNeeds(size) {
		if (this.code.length < size+this.cursor) {
			let new_code = new Uint8Array(size+this.cursor+1);
			new_code.set(this.code.slice(0, this.cursor), 0);
			this.code = new_code;
		}
	}
	
	/**
	 * 
	 * @param {Uint8Array} code 
	 */
	add_code(code) {
		this.extendIfNeeds(code.length);
		// if (this.code.length < code.length+this.cursor) {
		// 	let new_code = new Uint8Array(code.length+this.cursor+10);
		// 	new_code.set(this.code.slice(0, this.cursor), 0);
		// 	this.code = new_code;
		// }
		this.code.set(code, this.cursor);
	}

	addInt(code) {
		this.extendIfNeeds(4);
		this.code.set((
			code < 0 
				? numToInt8Array(code) 
				: numToUint8Array(code)),
			this.cursor);
		this.cursor += 4;
	}

	addUint(code) {
		this.extendIfNeeds(4);
		this.code.set(numToUint8Array(code), this.cursor);
		this.cursor += 4;
	}

	pushFunction(fn) {
		this.fns[fn.name] = fn;
	}

	moveLabels(shift_size) {
		let keys = Object.keys(this.labels);
		keys.forEach(key=>{
			this.labels[key] += shift_size;
			// this.label_arg[key].forEach(([k, c]) => {
			// 	this.setInt((c)-k, c);
			// })
		})
	}

	/**
	 * 
	 * @param {CodeBuilder} cb 
	 * @returns CodeBuilder
	 */
	link(cb) {
		// concat datas
		this.data = {...this.data, ...cb.data};
		let dk = Object.keys(this.data_defines);
		dk.forEach(k=>{
			let pos = this.data_defines[k];
			let offset = this.get_data_pos(k);
			this.setInt(offset, pos);
		})
		let dkk = Object.keys(this.data_defines);
		dkk.forEach(k=>{
			let pos = cb.data_defines[k];
			let offset = this.get_data_pos(k);
			this.setInt(offset, pos);
		})
		// mark labels
		cb.moveLabels(this.cursor);
		let keys = Object.keys(cb.labels);
		keys.forEach(e=>{
			let pos = cb.labels[e];
			pos += this.cursor;
			this.markLabel(e, pos);
		})
		// concat codes
		this.add_code(cb.code);
		return this;
	}

	build(flags = {"debug": false}) {
		let debug_info = new Uint8Array(flags.debug ? (this.debug_info.length*8+6) : 0);
		let data_size = this.get_data_length();
		const manifest_length = 16;
		let len = this.cursor + data_size + manifest_length + debug_info.length + 2;
		// len = (data_size-len)+this.current_code_cursor + 12;
		let arr = new Uint8Array(len);
		let data_arr = new Uint8Array(data_size);
		let data_cursor = 0;
		this.extendIfNeeds(data_size+10);
		for (let [k, v] of Object.entries(this.data)) {
			let val = Uint8Array
				.from(v
					.split('')
					.map(letter => letter.charCodeAt(0)));
			this.code.set(val, this.cursor++);
			data_arr.set(val, data_cursor);
			data_cursor += v.length;
		}
		/** MANIFEST */
		let manifest_flags = 0;
		manifest_flags |= !flags.debug ? 0: (1 << 1);
		// version 0+4
		arr.set(numToUint8Array(vm.version), 0); 
		// manifest flags
		arr.set(numToUint8Array(manifest_flags), 4); 
		// code length 4+4
		arr.set(numToUint8Array(this.cursor), 8);
		// data length
		arr.set(numToUint8Array(data_size), 12);
		/** SECTIONS */
		// code 8+n
		arr.set(this.code.subarray(0, this.cursor-1), manifest_length);
		// data
		arr.set(data_arr, this.cursor+manifest_length);
		if (flags.debug) {
			let debug_cursor = 0;
			debug_info.set(numToUint8Array(debug_info.length), debug_cursor);
			debug_cursor += 4;
			this.debug_info.forEach(e=>{
				debug_info.set(numToUint8Array(e.number), debug_cursor);
				debug_info.set(numToUint8Array(e.cursor), debug_cursor+4);
				debug_cursor += 8;
			});
			arr.set(debug_info, this.cursor+manifest_length+data_arr.length);
		}

		return arr;
	}
};