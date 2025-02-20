import antlr4 from 'antlr4';
import Visitor from './nanVisitor.js';
import CodeBuilder from './code_builder.js';

export default class VisitorImpl extends Visitor {	
	builder = new CodeBuilder();
	
	visitProgram(ctx) {
		let vis = this.visitChildren(ctx);
		return vis;
	}
	
	visitLine(ctx) {
		let vis = this.visitChildren(ctx)?.flat(1)?.[0];
		return vis;
	}
	visitRdi_offset(ctx) {
		let [,,num,] = ctx.children.map(e=>e.getText())
		num = parseInt(num);
		return {
			"type":"rdi_offset",
			"value":Math.abs(num)
		};
	}

	visitAny_arg(ctx) {
		let vis = this.visitChildren(ctx)?.filter(e=>e!=void 0)?.[0];
		let data = ctx.children.map(e=>e.getText())
		var value, type;
		// use NUMBER
		if (vis == void 0) {
			value = {"value":parseInt(data[0])};
			type = "number";
		} else {
			value = vis;
			if (value.reg != void 0) {
				type = "reg";
			} else {
				type = value.type;
			}
		}
		return {type, ...value};
	}

	visitDua_arg(ctx) {
		let vis = this.visitChildren(ctx)?.filter(e=>e!=void 0);
		return vis;
	}

	visitTre_arg(ctx) {
		let vis = this.visitChildren(ctx)?.filter(e=>e!=void 0);
		return vis;
	}

	visitMov(ctx) {
		let vis = this.visitChildren(ctx)?.filter(e=>e!=void 0)?.[0];
		this.builder._mov(vis);
		return {
			"type":"mov",
			"value":vis
		}
		console.log(vis);
	}

	visitCall(ctx) {
		let [,name] = ctx.children.map(e=>e.getText())
		this.builder._call(name);
		return {
			"type": "call",
			name,
		};
	}

	visitPop(ctx) {
		this.builder._pop();
		return {"type": "pop"}
	}

	visitRpop(ctx) {
		let vis = this.visitChildren(ctx)?.filter(e=>e!=void 0)?.[0];
		this.builder._rpop(vis);
		return {"type": "rpop", ...vis}
	}

	visitRegister(ctx) {
		let [,reg,] = ctx.children.map(e=>e.getText())
		let kind, idx;
		let r = /r(\d)/.exec(reg)?.[1];
		let rx = /rx(\d)/.exec(reg)?.[1];
		let dx = /dx(\d)/.exec(reg)?.[1];
		let fx = /fx(\d)/.exec(reg)?.[1];
		if (r != void 0) {
			kind = 1; idx = parseInt(r);
		} else if (rx != void 0) {
			kind = 2; idx = parseInt(rx);
		} else if (dx != void 0) {
			kind = 3; idx = parseInt(dx);
		} else if (fx != void 0) {
			kind = 4; idx = parseInt(fx);
		} else { return null; } 
		return {reg, kind, idx};
	}

	visitData(ctx) {
		let [,mod,name,value] = ctx.children.map(e=>e.getText())
		return {
			"type": "data",
			mod, name,
			"value": this.builder.add_data(mod, name, value)
		};
	}
	
	visitEntry(ctx) {
		let [,name] = ctx.children.map(e=>e.getText())
		this.builder.markEntry(name);
		return {
			"type": "entry",
			name
		};
	}
	visitLabel(ctx) {
		let [name,] = ctx.children.map(e=>e.getText())
		this.builder.markLabel(name);
		return {
			"type": "label",
			name
		}
	}
	visitInstr(ctx) {
		let vis = this.visitChildren(ctx)?.flat(1)?.[0];
		// console.log(vis);
		return vis;
	}

	visitPuts(ctx) {
		let [type,value] = ctx.children.map(e=>e.getText())
		this.builder._puts(value);
		return {type, value};
	}

	visitPuti(ctx) {
		let vis = this.visitChildren(ctx)?.filter(e=>e!=void 0)?.[0];
		if (vis?.length == 0) {
			return null; // todo error
		}
		this.builder._puti(vis);
		return {"type": "puti"};
	}

	visitInc(ctx) {
		let vis = this.visitChildren(ctx)?.filter(e=>e!=void 0)?.[0]
		if (vis?.length == 0) {
			return null; // todo error
		}
		this.builder._inc(vis);
		return {"type":"inc", "value":vis};
	}
	visitTest(ctx) {
		this.builder._test();
		return {"type":"test"};
	}
	
	visitJel(ctx) {
		let [type,value] = ctx.children.map(e=>e.getText())
		this.builder._jel(value);
		return {type, value};
	}
	visitJem(ctx) {
		let [type,value] = ctx.children.map(e=>e.getText())
		this.builder._jem(value);
		return {type, value};
	}
	visitJl(ctx) {
		let [type,value] = ctx.children.map(e=>e.getText())
		this.builder._jl(value);
		return {type, value};
	}
	visitJm(ctx) {
		let [type,value] = ctx.children.map(e=>e.getText())
		this.builder._jm(value);
		return {type, value};
	}
	visitJe(ctx) {
		let [type,value] = ctx.children.map(e=>e.getText())
		this.builder._je(value);
		return {type, value};
	}
	visitJne(ctx) {
		let [type,value] = ctx.children.map(e=>e.getText())
		this.builder._jne(value);
		return {type, value};
	}
	visitJmp(ctx) {
		let [type,value] = ctx.children.map(e=>e.getText())
		this.builder._jmp(value);
		return {type, value};
	}
	visitRet(ctx) {
		this.builder._ret();
		return {"type":"ret"};
	}


	visitPush(ctx) {
		let vis = this.visitChildren(ctx)?.filter(e=>e!=void 0)?.[0]
		let [type,value] = ctx.children.map(e=>e.getText())
		if (vis != void 0) {
			if (vis.reg != void 0) {
				this.builder._rpush(vis);
				return {type, "vtype": "reg", "value":vis};
			}
			return {type, value};
		} 
		value = parseInt(value);
		this.builder._push(value);
		return {type, value};
	}
	
	
}