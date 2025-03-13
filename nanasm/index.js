import antlr4 from "antlr4";
import Lexer  from "./nanLexer.js";
import Parser from "./nanParser.js";
import Visitor from "./visitor.js";
import { spawn } from "node:child_process";


import fs, { existsSync } from "fs";
import path from "path";

import colors from "colors/index.js"

var inputs = ["test.nsm"];
var output = "./test.nb"

var visitors = inputs.map(e=>compile(e, "test.json"));
var linked = link(visitors);
var output_content = build(linked);
console.log(colors.green("BUILD COMPLETE"), /**/`\n>> Writen to ${output}`);
fs.writeFileSync(output, output_content, {"flag":"w"});
// if (for_run) {
// test(path.resolve(output));
	// run(path.resolve(output));
// } else {
// 	if (for_test) {
// 	}
// }


function compile(input_file, write_ast = void 0) {
	const input  = fs.readFileSync(input_file, "utf8");
	const chars  = new antlr4.InputStream(input);
	const lexer  = new Lexer(chars);
	const tokens = new antlr4.CommonTokenStream(lexer);
	const parser = new Parser(tokens);
	const tree   = parser.program();
	var visitor = new Visitor()
	let ast = visitor.visitProgram(tree);
	if (write_ast != void 0) {
		fs.writeFileSync(write_ast, JSON.stringify(ast, 0, 2), {"flag":"w"});
	}
	return visitor;
}

function link(visitors) {
	var main = visitors[0];
	if (visitors.length == 1) {
		return main;
	}
	visitors.slice(1).forEach(e=>{
		main.link(e);
	});
	return main;
}

function build(visitor) {
	return visitor.builder.build();
}

function run(path) {
	const cs = spawn('nanvm', [path], {"stdio": "pipe"});
	cs.stdout.on('data', (data) => {
		console.log(data.toString());
	});

	cs.stderr.on('data', (data) => {
		console.log("something wrong, error:", data.toString());
	});
	
	cs.on('close', (code) => { });
}

function test(path) {
	console.log(colors.green("STARTING TEST FOR "+ path));
	const cs = spawn('nanvm', [path]);
	console.log(colors.gray("OUTPUT:"));
	cs.stdout.on('data', (data) => {
		console.log(data.toString());
	});

	cs.stderr.on('data', (data) => {
		console.log("something wrong, error:", Buffer.from(data).toString());
	});
	
	cs.on('close', (code) => {
		console.log(">> test exit with code", code);
		if (code != 0) {
			console.log(colors.red("TEST FAILED"));
		} else {
			console.log(colors.green("TEST COMPLETE"));
		}
	});
}