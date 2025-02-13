import antlr4 from "antlr4";
import Lexer  from "./nanLexer.js";
import Parser from "./nanParser.js";
import Visitor from "./visitor.js";
// import MyGrammarListener from "./MyGrammarListener.js";

import fs from "fs";
import path from "path";

const path = process.argv[2];
if (path == void 0) {
	console.log("cannot file path");
	exit(1);
}

const input  = fs.readFileSync(path, "utf8");
const chars  = new antlr4.InputStream(input);
const lexer  = new Lexer(chars);
const tokens = new antlr4.CommonTokenStream(lexer);
const parser = new Parser(tokens);
const tree   = parser.program();
// console.log(
// 	tree.toStringTree(parser.ruleNames));

function getUserHome() {
  return process.env[(process.platform == 'win32') ? 'USERPROFILE' : 'HOME'];
}

let vis = new Visitor()
let program = vis.visitProgram(tree);

const cacheDir = path.join(getUserHome(), "/.nan/cache/");
fs.mkdir(cacheDir, { recursive: true }, 
	(err, path) => {
		if (err) {
			console.error(err);
		}
	});

let b = (vis.builder.build());
	
const content = JSON.stringify(program, 2, 2);
fs.writeFileSync(path.join(cacheDir, "./temp.json"), content);
fs.writeFileSync("./temp.json", content);
fs.writeFileSync(path.join(cacheDir, "./temp.nb"), b, {"flag":"w"});
fs.writeFileSync("./temp.nb", b, {"flag":"w"});
