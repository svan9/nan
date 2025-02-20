import antlr4 from "antlr4";
import Lexer  from "../nanLexer.js";
import Parser from "../nanParser.js";
import Visitor from "../visitor.js";
import { spawn } from "node:child_process";


import fs, { existsSync } from "fs";
import path from "path";
import minimist from "minimist";

import colors from "colors"

var argv = minimist(process.argv.slice(2), {"--": true});

var for_run = false;
var for_noinfo = false;
var for_test = false;

var inputs = argv["_"];
var outputs = argv["o"];
var links = argv["l"];

if (inputs[0] == "run") {
	for_run = true;
	inputs = inputs.slice(1);
}
if (argv.noinfo == true) {
	for_noinfo = true;
}
if (argv.test == true) {
	for_test = true;
}

function lcpath(p) {
	return colors.italic(colors.gray(p));
}

function log_error(...text) {
	const _text = text.join(" ");
	console.log(colors.italic(colors.brightRed("ERROR:\n")), _text)
}

if (inputs.length < 1) {
	console.log("ERROR cannot compile zero path input");
	process.exit(1);
}

if (outputs != void 0 && typeof outputs == "object") {
	console.log("WARN cannot be multiply output files, will be used first");
}

const output = (typeof outputs == "object" ?  outputs[0]: outputs) ?? path.basename(inputs[0]).replace(/\.(.*)/, ".nb");

var __exist = true;
inputs.forEach(e=>{
	if (!existsSync(e)) {
		log_error(/**/`>> Undefined file '${e}'`);
		__exist = false;
	}
})

if (!__exist) {
	process.exit(1);
}

var visitors = inputs.map(e=>compile(e));
var linked = link(visitors);
var output_content = build(linked);
if (!for_noinfo) {
	console.log(colors.green("BUILD COMPLETE"), /**/`\n>> Writen to ${output}`);
}
fs.writeFileSync(output, output_content, {"flag":"w"});
if (for_run) {
	run(path.resolve(output));
} else {
	if (for_test) {
		test(path.resolve(output));
	}
}


function compile(input_file) {
	const input  = fs.readFileSync(input_file, "utf8");
	const chars  = new antlr4.InputStream(input);
	const lexer  = new Lexer(chars);
	const tokens = new antlr4.CommonTokenStream(lexer);
	const parser = new Parser(tokens);
	const tree   = parser.program();
	var visitor = new Visitor()
	let ast = visitor.visitProgram(tree);
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
	// fs.writeFileSync(path.join(cacheDir, "./temp.json"), content);
	// fs.writeFileSync("./temp.json", content);
	// fs.writeFileSync(path.join(cacheDir, "./temp.nb"), b, {"flag":"w"});
	// fs.writeFileSync("./temp.nb", b, {"flag":"w"});