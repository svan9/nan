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
		if (vis.length == 0) {
			return null; // todo error
		}
		this.builder._puti(vis);
		return {"type": "puti"};
	}

	visitInc(ctx) {
		let vis = this.visitChildren(ctx)?.filter(e=>e!=void 0)?.[0]
		if (vis.length == 0) {
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

	visitRdi_offset(ctx) {
		let [,,num,] = ctx.children.map(e=>e.getText())
		num = parseInt(num);
		return Math.abs(num);
	}

	visitPush(ctx) {
		let vis = this.visitChildren(ctx)
		// todo offset push from stack (and c++)
		// console.log(vis)
		let [type,value] = ctx.children.map(e=>e.getText())
		value = parseInt(value);
		this.builder._push(value);
		return {type, value};
	}
	
	
}