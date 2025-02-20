// Generated from e:/so2u/GITHUB/cuba/nan/nanasm/nan.g4 by ANTLR 4.13.1
// jshint ignore: start
import antlr4 from 'antlr4';
import nanListener from './nanListener.js';
import nanVisitor from './nanVisitor.js';

const serializedATN = [4,1,53,293,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,
4,2,5,7,5,2,6,7,6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,
2,13,7,13,2,14,7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,
20,7,20,2,21,7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,
7,27,2,28,7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,
34,2,35,7,35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,
2,42,7,42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,1,0,5,0,98,8,
0,10,0,12,0,101,9,0,1,1,1,1,1,1,1,1,3,1,107,8,1,1,2,1,2,1,2,1,2,1,2,3,2,
114,8,2,1,3,1,3,1,3,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,
1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,
1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,3,5,158,8,5,1,6,1,6,1,6,1,7,1,7,1,7,1,8,
1,8,1,8,1,9,1,9,1,9,1,10,1,10,1,11,1,11,1,11,1,12,1,12,1,12,1,13,1,13,1,
13,1,14,1,14,1,14,1,15,1,15,1,15,1,16,1,16,1,16,1,17,1,17,1,17,1,18,1,18,
1,18,1,19,1,19,1,20,1,20,1,20,1,21,1,21,1,21,1,22,1,22,1,22,1,23,1,23,1,
23,1,24,1,24,1,24,1,25,1,25,1,25,1,26,1,26,1,26,1,27,1,27,1,28,1,28,1,28,
1,29,1,29,1,29,1,30,1,30,1,30,1,31,1,31,1,31,1,32,1,32,1,32,1,33,1,33,1,
33,1,34,1,34,1,34,1,35,1,35,1,35,1,36,1,36,1,36,1,37,1,37,1,37,1,38,1,38,
1,38,1,39,1,39,1,39,1,40,1,40,1,40,1,41,1,41,1,41,1,42,1,42,1,42,1,42,1,
42,1,42,1,43,1,43,1,43,1,43,1,44,1,44,1,44,3,44,278,8,44,1,45,1,45,1,45,
1,45,1,46,1,46,1,46,1,46,1,46,1,47,1,47,1,47,1,47,1,47,0,0,48,0,2,4,6,8,
10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,
58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,0,0,286,0,99,1,
0,0,0,2,106,1,0,0,0,4,108,1,0,0,0,6,115,1,0,0,0,8,118,1,0,0,0,10,157,1,0,
0,0,12,159,1,0,0,0,14,162,1,0,0,0,16,165,1,0,0,0,18,168,1,0,0,0,20,171,1,
0,0,0,22,173,1,0,0,0,24,176,1,0,0,0,26,179,1,0,0,0,28,182,1,0,0,0,30,185,
1,0,0,0,32,188,1,0,0,0,34,191,1,0,0,0,36,194,1,0,0,0,38,197,1,0,0,0,40,199,
1,0,0,0,42,202,1,0,0,0,44,205,1,0,0,0,46,208,1,0,0,0,48,211,1,0,0,0,50,214,
1,0,0,0,52,217,1,0,0,0,54,220,1,0,0,0,56,222,1,0,0,0,58,225,1,0,0,0,60,228,
1,0,0,0,62,231,1,0,0,0,64,234,1,0,0,0,66,237,1,0,0,0,68,240,1,0,0,0,70,243,
1,0,0,0,72,246,1,0,0,0,74,249,1,0,0,0,76,252,1,0,0,0,78,255,1,0,0,0,80,258,
1,0,0,0,82,261,1,0,0,0,84,264,1,0,0,0,86,270,1,0,0,0,88,277,1,0,0,0,90,279,
1,0,0,0,92,283,1,0,0,0,94,288,1,0,0,0,96,98,3,2,1,0,97,96,1,0,0,0,98,101,
1,0,0,0,99,97,1,0,0,0,99,100,1,0,0,0,100,1,1,0,0,0,101,99,1,0,0,0,102,107,
3,6,3,0,103,107,3,4,2,0,104,107,3,8,4,0,105,107,3,10,5,0,106,102,1,0,0,0,
106,103,1,0,0,0,106,104,1,0,0,0,106,105,1,0,0,0,107,3,1,0,0,0,108,109,5,
1,0,0,109,110,5,46,0,0,110,113,5,48,0,0,111,114,5,52,0,0,112,114,3,94,47,
0,113,111,1,0,0,0,113,112,1,0,0,0,114,5,1,0,0,0,115,116,5,2,0,0,116,117,
5,48,0,0,117,7,1,0,0,0,118,119,5,48,0,0,119,120,5,3,0,0,120,9,1,0,0,0,121,
158,3,12,6,0,122,158,3,14,7,0,123,158,3,16,8,0,124,158,3,18,9,0,125,158,
3,20,10,0,126,158,3,22,11,0,127,158,3,24,12,0,128,158,3,26,13,0,129,158,
3,28,14,0,130,158,3,30,15,0,131,158,3,32,16,0,132,158,3,34,17,0,133,158,
3,36,18,0,134,158,3,38,19,0,135,158,3,40,20,0,136,158,3,42,21,0,137,158,
3,44,22,0,138,158,3,46,23,0,139,158,3,48,24,0,140,158,3,50,25,0,141,158,
3,52,26,0,142,158,3,54,27,0,143,158,3,56,28,0,144,158,3,58,29,0,145,158,
3,60,30,0,146,158,3,62,31,0,147,158,3,64,32,0,148,158,3,66,33,0,149,158,
3,68,34,0,150,158,3,70,35,0,151,158,3,72,36,0,152,158,3,74,37,0,153,158,
3,76,38,0,154,158,3,78,39,0,155,158,3,80,40,0,156,158,3,82,41,0,157,121,
1,0,0,0,157,122,1,0,0,0,157,123,1,0,0,0,157,124,1,0,0,0,157,125,1,0,0,0,
157,126,1,0,0,0,157,127,1,0,0,0,157,128,1,0,0,0,157,129,1,0,0,0,157,130,
1,0,0,0,157,131,1,0,0,0,157,132,1,0,0,0,157,133,1,0,0,0,157,134,1,0,0,0,
157,135,1,0,0,0,157,136,1,0,0,0,157,137,1,0,0,0,157,138,1,0,0,0,157,139,
1,0,0,0,157,140,1,0,0,0,157,141,1,0,0,0,157,142,1,0,0,0,157,143,1,0,0,0,
157,144,1,0,0,0,157,145,1,0,0,0,157,146,1,0,0,0,157,147,1,0,0,0,157,148,
1,0,0,0,157,149,1,0,0,0,157,150,1,0,0,0,157,151,1,0,0,0,157,152,1,0,0,0,
157,153,1,0,0,0,157,154,1,0,0,0,157,155,1,0,0,0,157,156,1,0,0,0,158,11,1,
0,0,0,159,160,5,4,0,0,160,161,5,48,0,0,161,13,1,0,0,0,162,163,5,5,0,0,163,
164,5,48,0,0,164,15,1,0,0,0,165,166,5,6,0,0,166,167,3,88,44,0,167,17,1,0,
0,0,168,169,5,7,0,0,169,170,3,88,44,0,170,19,1,0,0,0,171,172,5,8,0,0,172,
21,1,0,0,0,173,174,5,8,0,0,174,175,3,90,45,0,175,23,1,0,0,0,176,177,5,9,
0,0,177,178,3,88,44,0,178,25,1,0,0,0,179,180,5,10,0,0,180,181,3,88,44,0,
181,27,1,0,0,0,182,183,5,11,0,0,183,184,3,88,44,0,184,29,1,0,0,0,185,186,
5,12,0,0,186,187,3,86,43,0,187,31,1,0,0,0,188,189,5,13,0,0,189,190,3,86,
43,0,190,33,1,0,0,0,191,192,5,14,0,0,192,193,3,86,43,0,193,35,1,0,0,0,194,
195,5,15,0,0,195,196,3,86,43,0,196,37,1,0,0,0,197,198,5,16,0,0,198,39,1,
0,0,0,199,200,5,17,0,0,200,201,5,48,0,0,201,41,1,0,0,0,202,203,5,18,0,0,
203,204,5,48,0,0,204,43,1,0,0,0,205,206,5,19,0,0,206,207,5,48,0,0,207,45,
1,0,0,0,208,209,5,20,0,0,209,210,5,48,0,0,210,47,1,0,0,0,211,212,5,21,0,
0,212,213,5,48,0,0,213,49,1,0,0,0,214,215,5,22,0,0,215,216,5,48,0,0,216,
51,1,0,0,0,217,218,5,23,0,0,218,219,5,48,0,0,219,53,1,0,0,0,220,221,5,24,
0,0,221,55,1,0,0,0,222,223,5,25,0,0,223,224,3,86,43,0,224,57,1,0,0,0,225,
226,5,26,0,0,226,227,3,86,43,0,227,59,1,0,0,0,228,229,5,27,0,0,229,230,3,
88,44,0,230,61,1,0,0,0,231,232,5,28,0,0,232,233,3,86,43,0,233,63,1,0,0,0,
234,235,5,29,0,0,235,236,3,86,43,0,236,65,1,0,0,0,237,238,5,30,0,0,238,239,
3,86,43,0,239,67,1,0,0,0,240,241,5,31,0,0,241,242,3,86,43,0,242,69,1,0,0,
0,243,244,5,32,0,0,244,245,3,86,43,0,245,71,1,0,0,0,246,247,5,33,0,0,247,
248,3,84,42,0,248,73,1,0,0,0,249,250,5,34,0,0,250,251,3,88,44,0,251,75,1,
0,0,0,252,253,5,35,0,0,253,254,3,88,44,0,254,77,1,0,0,0,255,256,5,36,0,0,
256,257,3,88,44,0,257,79,1,0,0,0,258,259,5,37,0,0,259,260,3,88,44,0,260,
81,1,0,0,0,261,262,5,38,0,0,262,263,3,88,44,0,263,83,1,0,0,0,264,265,3,88,
44,0,265,266,5,39,0,0,266,267,3,88,44,0,267,268,5,39,0,0,268,269,3,88,44,
0,269,85,1,0,0,0,270,271,3,88,44,0,271,272,5,39,0,0,272,273,3,88,44,0,273,
87,1,0,0,0,274,278,3,90,45,0,275,278,3,92,46,0,276,278,5,47,0,0,277,274,
1,0,0,0,277,275,1,0,0,0,277,276,1,0,0,0,278,89,1,0,0,0,279,280,5,40,0,0,
280,281,5,48,0,0,281,282,5,41,0,0,282,91,1,0,0,0,283,284,5,40,0,0,284,285,
5,42,0,0,285,286,5,47,0,0,286,287,5,41,0,0,287,93,1,0,0,0,288,289,5,43,0,
0,289,290,5,47,0,0,290,291,5,44,0,0,291,95,1,0,0,0,5,99,106,113,157,277];


const atn = new antlr4.atn.ATNDeserializer().deserialize(serializedATN);

const decisionsToDFA = atn.decisionToState.map( (ds, index) => new antlr4.dfa.DFA(ds, index) );

const sharedContextCache = new antlr4.atn.PredictionContextCache();

export default class nanParser extends antlr4.Parser {

    static grammarFileName = "nan.g4";
    static literalNames = [ null, "'data'", "'entry'", "':'", "'call'", 
                            "'puts'", "'puti'", "'push'", "'pop'", "'inc'", 
                            "'dec'", "'gch'", "'add'", "'div'", "'mul'", 
                            "'sub'", "'test'", "'jel'", "'jem'", "'je'", 
                            "'el'", "'jm'", "'jne'", "'jmp'", "'ret'", "'xor'", 
                            "'or'", "'not'", "'and'", "'ls'", "'rs'", "'mov'", 
                            "'swap'", "'mset'", "'swst'", "'write'", "'read'", 
                            "'open'", "'putc'", "','", "'('", "')'", "'rdi'", 
                            "'['", "']'" ];
    static symbolicNames = [ null, null, null, null, null, null, null, null, 
                             null, null, null, null, null, null, null, null, 
                             null, null, null, null, null, null, null, null, 
                             null, null, null, null, null, null, null, null, 
                             null, null, null, null, null, null, null, null, 
                             null, null, null, null, null, "WS", "MOD", 
                             "NUMBER", "WORD", "FLAG", "OPERATORS", "TYPEMOD", 
                             "STRING", "SSTRING" ];
    static ruleNames = [ "program", "line", "data", "entry", "label", "instr", 
                         "call", "puts", "puti", "push", "pop", "rpop", 
                         "inc", "dec", "gch", "add", "div", "mul", "sub", 
                         "test", "jel", "jem", "je", "jl", "jm", "jne", 
                         "jmp", "ret", "xor", "or", "not", "and", "ls", 
                         "rs", "mov", "swap", "mset", "swst", "write", "read", 
                         "open", "putc", "tre_arg", "dua_arg", "any_arg", 
                         "register", "rdi_offset", "size_t" ];

    constructor(input) {
        super(input);
        this._interp = new antlr4.atn.ParserATNSimulator(this, atn, decisionsToDFA, sharedContextCache);
        this.ruleNames = nanParser.ruleNames;
        this.literalNames = nanParser.literalNames;
        this.symbolicNames = nanParser.symbolicNames;
    }



	program() {
	    let localctx = new ProgramContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 0, nanParser.RULE_program);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 99;
	        this._errHandler.sync(this);
	        _la = this._input.LA(1);
	        while((((_la) & ~0x1f) === 0 && ((1 << _la) & 4294967286) !== 0) || ((((_la - 32)) & ~0x1f) === 0 && ((1 << (_la - 32)) & 65663) !== 0)) {
	            this.state = 96;
	            this.line();
	            this.state = 101;
	            this._errHandler.sync(this);
	            _la = this._input.LA(1);
	        }
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	line() {
	    let localctx = new LineContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 2, nanParser.RULE_line);
	    try {
	        this.state = 106;
	        this._errHandler.sync(this);
	        switch(this._input.LA(1)) {
	        case 2:
	            this.enterOuterAlt(localctx, 1);
	            this.state = 102;
	            this.entry();
	            break;
	        case 1:
	            this.enterOuterAlt(localctx, 2);
	            this.state = 103;
	            this.data();
	            break;
	        case 48:
	            this.enterOuterAlt(localctx, 3);
	            this.state = 104;
	            this.label();
	            break;
	        case 4:
	        case 5:
	        case 6:
	        case 7:
	        case 8:
	        case 9:
	        case 10:
	        case 11:
	        case 12:
	        case 13:
	        case 14:
	        case 15:
	        case 16:
	        case 17:
	        case 18:
	        case 19:
	        case 20:
	        case 21:
	        case 22:
	        case 23:
	        case 24:
	        case 25:
	        case 26:
	        case 27:
	        case 28:
	        case 29:
	        case 30:
	        case 31:
	        case 32:
	        case 33:
	        case 34:
	        case 35:
	        case 36:
	        case 37:
	        case 38:
	            this.enterOuterAlt(localctx, 4);
	            this.state = 105;
	            this.instr();
	            break;
	        default:
	            throw new antlr4.error.NoViableAltException(this);
	        }
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	data() {
	    let localctx = new DataContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 4, nanParser.RULE_data);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 108;
	        this.match(nanParser.T__0);
	        this.state = 109;
	        this.match(nanParser.MOD);
	        this.state = 110;
	        this.match(nanParser.WORD);
	        this.state = 113;
	        this._errHandler.sync(this);
	        switch(this._input.LA(1)) {
	        case 52:
	            this.state = 111;
	            this.match(nanParser.STRING);
	            break;
	        case 43:
	            this.state = 112;
	            this.size_t();
	            break;
	        default:
	            throw new antlr4.error.NoViableAltException(this);
	        }
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	entry() {
	    let localctx = new EntryContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 6, nanParser.RULE_entry);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 115;
	        this.match(nanParser.T__1);
	        this.state = 116;
	        this.match(nanParser.WORD);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	label() {
	    let localctx = new LabelContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 8, nanParser.RULE_label);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 118;
	        this.match(nanParser.WORD);
	        this.state = 119;
	        this.match(nanParser.T__2);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	instr() {
	    let localctx = new InstrContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 10, nanParser.RULE_instr);
	    try {
	        this.state = 157;
	        this._errHandler.sync(this);
	        var la_ = this._interp.adaptivePredict(this._input,3,this._ctx);
	        switch(la_) {
	        case 1:
	            this.enterOuterAlt(localctx, 1);
	            this.state = 121;
	            this.call();
	            break;

	        case 2:
	            this.enterOuterAlt(localctx, 2);
	            this.state = 122;
	            this.puts();
	            break;

	        case 3:
	            this.enterOuterAlt(localctx, 3);
	            this.state = 123;
	            this.puti();
	            break;

	        case 4:
	            this.enterOuterAlt(localctx, 4);
	            this.state = 124;
	            this.push();
	            break;

	        case 5:
	            this.enterOuterAlt(localctx, 5);
	            this.state = 125;
	            this.pop();
	            break;

	        case 6:
	            this.enterOuterAlt(localctx, 6);
	            this.state = 126;
	            this.rpop();
	            break;

	        case 7:
	            this.enterOuterAlt(localctx, 7);
	            this.state = 127;
	            this.inc();
	            break;

	        case 8:
	            this.enterOuterAlt(localctx, 8);
	            this.state = 128;
	            this.dec();
	            break;

	        case 9:
	            this.enterOuterAlt(localctx, 9);
	            this.state = 129;
	            this.gch();
	            break;

	        case 10:
	            this.enterOuterAlt(localctx, 10);
	            this.state = 130;
	            this.add();
	            break;

	        case 11:
	            this.enterOuterAlt(localctx, 11);
	            this.state = 131;
	            this.div();
	            break;

	        case 12:
	            this.enterOuterAlt(localctx, 12);
	            this.state = 132;
	            this.mul();
	            break;

	        case 13:
	            this.enterOuterAlt(localctx, 13);
	            this.state = 133;
	            this.sub();
	            break;

	        case 14:
	            this.enterOuterAlt(localctx, 14);
	            this.state = 134;
	            this.test();
	            break;

	        case 15:
	            this.enterOuterAlt(localctx, 15);
	            this.state = 135;
	            this.jel();
	            break;

	        case 16:
	            this.enterOuterAlt(localctx, 16);
	            this.state = 136;
	            this.jem();
	            break;

	        case 17:
	            this.enterOuterAlt(localctx, 17);
	            this.state = 137;
	            this.je();
	            break;

	        case 18:
	            this.enterOuterAlt(localctx, 18);
	            this.state = 138;
	            this.jl();
	            break;

	        case 19:
	            this.enterOuterAlt(localctx, 19);
	            this.state = 139;
	            this.jm();
	            break;

	        case 20:
	            this.enterOuterAlt(localctx, 20);
	            this.state = 140;
	            this.jne();
	            break;

	        case 21:
	            this.enterOuterAlt(localctx, 21);
	            this.state = 141;
	            this.jmp();
	            break;

	        case 22:
	            this.enterOuterAlt(localctx, 22);
	            this.state = 142;
	            this.ret();
	            break;

	        case 23:
	            this.enterOuterAlt(localctx, 23);
	            this.state = 143;
	            this.xor();
	            break;

	        case 24:
	            this.enterOuterAlt(localctx, 24);
	            this.state = 144;
	            this.or();
	            break;

	        case 25:
	            this.enterOuterAlt(localctx, 25);
	            this.state = 145;
	            this.not();
	            break;

	        case 26:
	            this.enterOuterAlt(localctx, 26);
	            this.state = 146;
	            this.and();
	            break;

	        case 27:
	            this.enterOuterAlt(localctx, 27);
	            this.state = 147;
	            this.ls();
	            break;

	        case 28:
	            this.enterOuterAlt(localctx, 28);
	            this.state = 148;
	            this.rs();
	            break;

	        case 29:
	            this.enterOuterAlt(localctx, 29);
	            this.state = 149;
	            this.mov();
	            break;

	        case 30:
	            this.enterOuterAlt(localctx, 30);
	            this.state = 150;
	            this.swap();
	            break;

	        case 31:
	            this.enterOuterAlt(localctx, 31);
	            this.state = 151;
	            this.mset();
	            break;

	        case 32:
	            this.enterOuterAlt(localctx, 32);
	            this.state = 152;
	            this.swst();
	            break;

	        case 33:
	            this.enterOuterAlt(localctx, 33);
	            this.state = 153;
	            this.write();
	            break;

	        case 34:
	            this.enterOuterAlt(localctx, 34);
	            this.state = 154;
	            this.read();
	            break;

	        case 35:
	            this.enterOuterAlt(localctx, 35);
	            this.state = 155;
	            this.open();
	            break;

	        case 36:
	            this.enterOuterAlt(localctx, 36);
	            this.state = 156;
	            this.putc();
	            break;

	        }
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	call() {
	    let localctx = new CallContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 12, nanParser.RULE_call);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 159;
	        this.match(nanParser.T__3);
	        this.state = 160;
	        this.match(nanParser.WORD);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	puts() {
	    let localctx = new PutsContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 14, nanParser.RULE_puts);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 162;
	        this.match(nanParser.T__4);
	        this.state = 163;
	        this.match(nanParser.WORD);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	puti() {
	    let localctx = new PutiContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 16, nanParser.RULE_puti);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 165;
	        this.match(nanParser.T__5);
	        this.state = 166;
	        this.any_arg();
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	push() {
	    let localctx = new PushContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 18, nanParser.RULE_push);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 168;
	        this.match(nanParser.T__6);
	        this.state = 169;
	        this.any_arg();
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	pop() {
	    let localctx = new PopContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 20, nanParser.RULE_pop);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 171;
	        this.match(nanParser.T__7);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	rpop() {
	    let localctx = new RpopContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 22, nanParser.RULE_rpop);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 173;
	        this.match(nanParser.T__7);
	        this.state = 174;
	        this.register();
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	inc() {
	    let localctx = new IncContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 24, nanParser.RULE_inc);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 176;
	        this.match(nanParser.T__8);
	        this.state = 177;
	        this.any_arg();
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	dec() {
	    let localctx = new DecContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 26, nanParser.RULE_dec);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 179;
	        this.match(nanParser.T__9);
	        this.state = 180;
	        this.any_arg();
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	gch() {
	    let localctx = new GchContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 28, nanParser.RULE_gch);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 182;
	        this.match(nanParser.T__10);
	        this.state = 183;
	        this.any_arg();
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	add() {
	    let localctx = new AddContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 30, nanParser.RULE_add);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 185;
	        this.match(nanParser.T__11);
	        this.state = 186;
	        this.dua_arg();
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	div() {
	    let localctx = new DivContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 32, nanParser.RULE_div);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 188;
	        this.match(nanParser.T__12);
	        this.state = 189;
	        this.dua_arg();
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	mul() {
	    let localctx = new MulContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 34, nanParser.RULE_mul);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 191;
	        this.match(nanParser.T__13);
	        this.state = 192;
	        this.dua_arg();
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	sub() {
	    let localctx = new SubContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 36, nanParser.RULE_sub);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 194;
	        this.match(nanParser.T__14);
	        this.state = 195;
	        this.dua_arg();
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	test() {
	    let localctx = new TestContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 38, nanParser.RULE_test);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 197;
	        this.match(nanParser.T__15);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	jel() {
	    let localctx = new JelContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 40, nanParser.RULE_jel);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 199;
	        this.match(nanParser.T__16);
	        this.state = 200;
	        this.match(nanParser.WORD);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	jem() {
	    let localctx = new JemContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 42, nanParser.RULE_jem);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 202;
	        this.match(nanParser.T__17);
	        this.state = 203;
	        this.match(nanParser.WORD);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	je() {
	    let localctx = new JeContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 44, nanParser.RULE_je);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 205;
	        this.match(nanParser.T__18);
	        this.state = 206;
	        this.match(nanParser.WORD);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	jl() {
	    let localctx = new JlContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 46, nanParser.RULE_jl);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 208;
	        this.match(nanParser.T__19);
	        this.state = 209;
	        this.match(nanParser.WORD);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	jm() {
	    let localctx = new JmContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 48, nanParser.RULE_jm);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 211;
	        this.match(nanParser.T__20);
	        this.state = 212;
	        this.match(nanParser.WORD);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	jne() {
	    let localctx = new JneContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 50, nanParser.RULE_jne);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 214;
	        this.match(nanParser.T__21);
	        this.state = 215;
	        this.match(nanParser.WORD);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	jmp() {
	    let localctx = new JmpContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 52, nanParser.RULE_jmp);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 217;
	        this.match(nanParser.T__22);
	        this.state = 218;
	        this.match(nanParser.WORD);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	ret() {
	    let localctx = new RetContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 54, nanParser.RULE_ret);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 220;
	        this.match(nanParser.T__23);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	xor() {
	    let localctx = new XorContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 56, nanParser.RULE_xor);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 222;
	        this.match(nanParser.T__24);
	        this.state = 223;
	        this.dua_arg();
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	or() {
	    let localctx = new OrContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 58, nanParser.RULE_or);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 225;
	        this.match(nanParser.T__25);
	        this.state = 226;
	        this.dua_arg();
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	not() {
	    let localctx = new NotContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 60, nanParser.RULE_not);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 228;
	        this.match(nanParser.T__26);
	        this.state = 229;
	        this.any_arg();
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	and() {
	    let localctx = new AndContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 62, nanParser.RULE_and);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 231;
	        this.match(nanParser.T__27);
	        this.state = 232;
	        this.dua_arg();
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	ls() {
	    let localctx = new LsContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 64, nanParser.RULE_ls);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 234;
	        this.match(nanParser.T__28);
	        this.state = 235;
	        this.dua_arg();
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	rs() {
	    let localctx = new RsContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 66, nanParser.RULE_rs);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 237;
	        this.match(nanParser.T__29);
	        this.state = 238;
	        this.dua_arg();
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	mov() {
	    let localctx = new MovContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 68, nanParser.RULE_mov);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 240;
	        this.match(nanParser.T__30);
	        this.state = 241;
	        this.dua_arg();
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	swap() {
	    let localctx = new SwapContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 70, nanParser.RULE_swap);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 243;
	        this.match(nanParser.T__31);
	        this.state = 244;
	        this.dua_arg();
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	mset() {
	    let localctx = new MsetContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 72, nanParser.RULE_mset);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 246;
	        this.match(nanParser.T__32);
	        this.state = 247;
	        this.tre_arg();
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	swst() {
	    let localctx = new SwstContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 74, nanParser.RULE_swst);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 249;
	        this.match(nanParser.T__33);
	        this.state = 250;
	        this.any_arg();
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	write() {
	    let localctx = new WriteContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 76, nanParser.RULE_write);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 252;
	        this.match(nanParser.T__34);
	        this.state = 253;
	        this.any_arg();
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	read() {
	    let localctx = new ReadContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 78, nanParser.RULE_read);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 255;
	        this.match(nanParser.T__35);
	        this.state = 256;
	        this.any_arg();
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	open() {
	    let localctx = new OpenContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 80, nanParser.RULE_open);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 258;
	        this.match(nanParser.T__36);
	        this.state = 259;
	        this.any_arg();
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	putc() {
	    let localctx = new PutcContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 82, nanParser.RULE_putc);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 261;
	        this.match(nanParser.T__37);
	        this.state = 262;
	        this.any_arg();
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	tre_arg() {
	    let localctx = new Tre_argContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 84, nanParser.RULE_tre_arg);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 264;
	        this.any_arg();
	        this.state = 265;
	        this.match(nanParser.T__38);
	        this.state = 266;
	        this.any_arg();
	        this.state = 267;
	        this.match(nanParser.T__38);
	        this.state = 268;
	        this.any_arg();
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	dua_arg() {
	    let localctx = new Dua_argContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 86, nanParser.RULE_dua_arg);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 270;
	        this.any_arg();
	        this.state = 271;
	        this.match(nanParser.T__38);
	        this.state = 272;
	        this.any_arg();
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	any_arg() {
	    let localctx = new Any_argContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 88, nanParser.RULE_any_arg);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 277;
	        this._errHandler.sync(this);
	        var la_ = this._interp.adaptivePredict(this._input,4,this._ctx);
	        switch(la_) {
	        case 1:
	            this.state = 274;
	            this.register();
	            break;

	        case 2:
	            this.state = 275;
	            this.rdi_offset();
	            break;

	        case 3:
	            this.state = 276;
	            this.match(nanParser.NUMBER);
	            break;

	        }
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	register() {
	    let localctx = new RegisterContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 90, nanParser.RULE_register);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 279;
	        this.match(nanParser.T__39);
	        this.state = 280;
	        this.match(nanParser.WORD);
	        this.state = 281;
	        this.match(nanParser.T__40);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	rdi_offset() {
	    let localctx = new Rdi_offsetContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 92, nanParser.RULE_rdi_offset);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 283;
	        this.match(nanParser.T__39);
	        this.state = 284;
	        this.match(nanParser.T__41);
	        this.state = 285;
	        this.match(nanParser.NUMBER);
	        this.state = 286;
	        this.match(nanParser.T__40);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	size_t() {
	    let localctx = new Size_tContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 94, nanParser.RULE_size_t);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 288;
	        this.match(nanParser.T__42);
	        this.state = 289;
	        this.match(nanParser.NUMBER);
	        this.state = 290;
	        this.match(nanParser.T__43);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}


}

nanParser.EOF = antlr4.Token.EOF;
nanParser.T__0 = 1;
nanParser.T__1 = 2;
nanParser.T__2 = 3;
nanParser.T__3 = 4;
nanParser.T__4 = 5;
nanParser.T__5 = 6;
nanParser.T__6 = 7;
nanParser.T__7 = 8;
nanParser.T__8 = 9;
nanParser.T__9 = 10;
nanParser.T__10 = 11;
nanParser.T__11 = 12;
nanParser.T__12 = 13;
nanParser.T__13 = 14;
nanParser.T__14 = 15;
nanParser.T__15 = 16;
nanParser.T__16 = 17;
nanParser.T__17 = 18;
nanParser.T__18 = 19;
nanParser.T__19 = 20;
nanParser.T__20 = 21;
nanParser.T__21 = 22;
nanParser.T__22 = 23;
nanParser.T__23 = 24;
nanParser.T__24 = 25;
nanParser.T__25 = 26;
nanParser.T__26 = 27;
nanParser.T__27 = 28;
nanParser.T__28 = 29;
nanParser.T__29 = 30;
nanParser.T__30 = 31;
nanParser.T__31 = 32;
nanParser.T__32 = 33;
nanParser.T__33 = 34;
nanParser.T__34 = 35;
nanParser.T__35 = 36;
nanParser.T__36 = 37;
nanParser.T__37 = 38;
nanParser.T__38 = 39;
nanParser.T__39 = 40;
nanParser.T__40 = 41;
nanParser.T__41 = 42;
nanParser.T__42 = 43;
nanParser.T__43 = 44;
nanParser.WS = 45;
nanParser.MOD = 46;
nanParser.NUMBER = 47;
nanParser.WORD = 48;
nanParser.FLAG = 49;
nanParser.OPERATORS = 50;
nanParser.TYPEMOD = 51;
nanParser.STRING = 52;
nanParser.SSTRING = 53;

nanParser.RULE_program = 0;
nanParser.RULE_line = 1;
nanParser.RULE_data = 2;
nanParser.RULE_entry = 3;
nanParser.RULE_label = 4;
nanParser.RULE_instr = 5;
nanParser.RULE_call = 6;
nanParser.RULE_puts = 7;
nanParser.RULE_puti = 8;
nanParser.RULE_push = 9;
nanParser.RULE_pop = 10;
nanParser.RULE_rpop = 11;
nanParser.RULE_inc = 12;
nanParser.RULE_dec = 13;
nanParser.RULE_gch = 14;
nanParser.RULE_add = 15;
nanParser.RULE_div = 16;
nanParser.RULE_mul = 17;
nanParser.RULE_sub = 18;
nanParser.RULE_test = 19;
nanParser.RULE_jel = 20;
nanParser.RULE_jem = 21;
nanParser.RULE_je = 22;
nanParser.RULE_jl = 23;
nanParser.RULE_jm = 24;
nanParser.RULE_jne = 25;
nanParser.RULE_jmp = 26;
nanParser.RULE_ret = 27;
nanParser.RULE_xor = 28;
nanParser.RULE_or = 29;
nanParser.RULE_not = 30;
nanParser.RULE_and = 31;
nanParser.RULE_ls = 32;
nanParser.RULE_rs = 33;
nanParser.RULE_mov = 34;
nanParser.RULE_swap = 35;
nanParser.RULE_mset = 36;
nanParser.RULE_swst = 37;
nanParser.RULE_write = 38;
nanParser.RULE_read = 39;
nanParser.RULE_open = 40;
nanParser.RULE_putc = 41;
nanParser.RULE_tre_arg = 42;
nanParser.RULE_dua_arg = 43;
nanParser.RULE_any_arg = 44;
nanParser.RULE_register = 45;
nanParser.RULE_rdi_offset = 46;
nanParser.RULE_size_t = 47;

class ProgramContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_program;
    }

	line = function(i) {
	    if(i===undefined) {
	        i = null;
	    }
	    if(i===null) {
	        return this.getTypedRuleContexts(LineContext);
	    } else {
	        return this.getTypedRuleContext(LineContext,i);
	    }
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterProgram(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitProgram(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitProgram(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class LineContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_line;
    }

	entry() {
	    return this.getTypedRuleContext(EntryContext,0);
	};

	data() {
	    return this.getTypedRuleContext(DataContext,0);
	};

	label() {
	    return this.getTypedRuleContext(LabelContext,0);
	};

	instr() {
	    return this.getTypedRuleContext(InstrContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterLine(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitLine(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitLine(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class DataContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_data;
    }

	MOD() {
	    return this.getToken(nanParser.MOD, 0);
	};

	WORD() {
	    return this.getToken(nanParser.WORD, 0);
	};

	STRING() {
	    return this.getToken(nanParser.STRING, 0);
	};

	size_t() {
	    return this.getTypedRuleContext(Size_tContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterData(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitData(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitData(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class EntryContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_entry;
    }

	WORD() {
	    return this.getToken(nanParser.WORD, 0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterEntry(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitEntry(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitEntry(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class LabelContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_label;
    }

	WORD() {
	    return this.getToken(nanParser.WORD, 0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterLabel(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitLabel(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitLabel(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class InstrContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_instr;
    }

	call() {
	    return this.getTypedRuleContext(CallContext,0);
	};

	puts() {
	    return this.getTypedRuleContext(PutsContext,0);
	};

	puti() {
	    return this.getTypedRuleContext(PutiContext,0);
	};

	push() {
	    return this.getTypedRuleContext(PushContext,0);
	};

	pop() {
	    return this.getTypedRuleContext(PopContext,0);
	};

	rpop() {
	    return this.getTypedRuleContext(RpopContext,0);
	};

	inc() {
	    return this.getTypedRuleContext(IncContext,0);
	};

	dec() {
	    return this.getTypedRuleContext(DecContext,0);
	};

	gch() {
	    return this.getTypedRuleContext(GchContext,0);
	};

	add() {
	    return this.getTypedRuleContext(AddContext,0);
	};

	div() {
	    return this.getTypedRuleContext(DivContext,0);
	};

	mul() {
	    return this.getTypedRuleContext(MulContext,0);
	};

	sub() {
	    return this.getTypedRuleContext(SubContext,0);
	};

	test() {
	    return this.getTypedRuleContext(TestContext,0);
	};

	jel() {
	    return this.getTypedRuleContext(JelContext,0);
	};

	jem() {
	    return this.getTypedRuleContext(JemContext,0);
	};

	je() {
	    return this.getTypedRuleContext(JeContext,0);
	};

	jl() {
	    return this.getTypedRuleContext(JlContext,0);
	};

	jm() {
	    return this.getTypedRuleContext(JmContext,0);
	};

	jne() {
	    return this.getTypedRuleContext(JneContext,0);
	};

	jmp() {
	    return this.getTypedRuleContext(JmpContext,0);
	};

	ret() {
	    return this.getTypedRuleContext(RetContext,0);
	};

	xor() {
	    return this.getTypedRuleContext(XorContext,0);
	};

	or() {
	    return this.getTypedRuleContext(OrContext,0);
	};

	not() {
	    return this.getTypedRuleContext(NotContext,0);
	};

	and() {
	    return this.getTypedRuleContext(AndContext,0);
	};

	ls() {
	    return this.getTypedRuleContext(LsContext,0);
	};

	rs() {
	    return this.getTypedRuleContext(RsContext,0);
	};

	mov() {
	    return this.getTypedRuleContext(MovContext,0);
	};

	swap() {
	    return this.getTypedRuleContext(SwapContext,0);
	};

	mset() {
	    return this.getTypedRuleContext(MsetContext,0);
	};

	swst() {
	    return this.getTypedRuleContext(SwstContext,0);
	};

	write() {
	    return this.getTypedRuleContext(WriteContext,0);
	};

	read() {
	    return this.getTypedRuleContext(ReadContext,0);
	};

	open() {
	    return this.getTypedRuleContext(OpenContext,0);
	};

	putc() {
	    return this.getTypedRuleContext(PutcContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterInstr(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitInstr(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitInstr(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class CallContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_call;
    }

	WORD() {
	    return this.getToken(nanParser.WORD, 0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterCall(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitCall(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitCall(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class PutsContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_puts;
    }

	WORD() {
	    return this.getToken(nanParser.WORD, 0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterPuts(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitPuts(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitPuts(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class PutiContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_puti;
    }

	any_arg() {
	    return this.getTypedRuleContext(Any_argContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterPuti(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitPuti(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitPuti(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class PushContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_push;
    }

	any_arg() {
	    return this.getTypedRuleContext(Any_argContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterPush(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitPush(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitPush(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class PopContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_pop;
    }


	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterPop(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitPop(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitPop(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class RpopContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_rpop;
    }

	register() {
	    return this.getTypedRuleContext(RegisterContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterRpop(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitRpop(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitRpop(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class IncContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_inc;
    }

	any_arg() {
	    return this.getTypedRuleContext(Any_argContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterInc(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitInc(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitInc(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class DecContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_dec;
    }

	any_arg() {
	    return this.getTypedRuleContext(Any_argContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterDec(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitDec(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitDec(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class GchContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_gch;
    }

	any_arg() {
	    return this.getTypedRuleContext(Any_argContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterGch(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitGch(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitGch(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class AddContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_add;
    }

	dua_arg() {
	    return this.getTypedRuleContext(Dua_argContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterAdd(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitAdd(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitAdd(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class DivContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_div;
    }

	dua_arg() {
	    return this.getTypedRuleContext(Dua_argContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterDiv(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitDiv(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitDiv(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class MulContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_mul;
    }

	dua_arg() {
	    return this.getTypedRuleContext(Dua_argContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterMul(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitMul(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitMul(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class SubContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_sub;
    }

	dua_arg() {
	    return this.getTypedRuleContext(Dua_argContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterSub(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitSub(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitSub(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class TestContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_test;
    }


	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterTest(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitTest(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitTest(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class JelContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_jel;
    }

	WORD() {
	    return this.getToken(nanParser.WORD, 0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterJel(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitJel(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitJel(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class JemContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_jem;
    }

	WORD() {
	    return this.getToken(nanParser.WORD, 0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterJem(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitJem(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitJem(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class JeContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_je;
    }

	WORD() {
	    return this.getToken(nanParser.WORD, 0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterJe(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitJe(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitJe(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class JlContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_jl;
    }

	WORD() {
	    return this.getToken(nanParser.WORD, 0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterJl(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitJl(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitJl(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class JmContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_jm;
    }

	WORD() {
	    return this.getToken(nanParser.WORD, 0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterJm(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitJm(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitJm(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class JneContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_jne;
    }

	WORD() {
	    return this.getToken(nanParser.WORD, 0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterJne(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitJne(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitJne(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class JmpContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_jmp;
    }

	WORD() {
	    return this.getToken(nanParser.WORD, 0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterJmp(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitJmp(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitJmp(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class RetContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_ret;
    }


	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterRet(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitRet(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitRet(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class XorContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_xor;
    }

	dua_arg() {
	    return this.getTypedRuleContext(Dua_argContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterXor(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitXor(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitXor(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class OrContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_or;
    }

	dua_arg() {
	    return this.getTypedRuleContext(Dua_argContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterOr(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitOr(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitOr(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class NotContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_not;
    }

	any_arg() {
	    return this.getTypedRuleContext(Any_argContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterNot(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitNot(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitNot(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class AndContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_and;
    }

	dua_arg() {
	    return this.getTypedRuleContext(Dua_argContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterAnd(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitAnd(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitAnd(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class LsContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_ls;
    }

	dua_arg() {
	    return this.getTypedRuleContext(Dua_argContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterLs(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitLs(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitLs(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class RsContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_rs;
    }

	dua_arg() {
	    return this.getTypedRuleContext(Dua_argContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterRs(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitRs(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitRs(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class MovContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_mov;
    }

	dua_arg() {
	    return this.getTypedRuleContext(Dua_argContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterMov(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitMov(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitMov(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class SwapContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_swap;
    }

	dua_arg() {
	    return this.getTypedRuleContext(Dua_argContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterSwap(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitSwap(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitSwap(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class MsetContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_mset;
    }

	tre_arg() {
	    return this.getTypedRuleContext(Tre_argContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterMset(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitMset(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitMset(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class SwstContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_swst;
    }

	any_arg() {
	    return this.getTypedRuleContext(Any_argContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterSwst(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitSwst(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitSwst(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class WriteContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_write;
    }

	any_arg() {
	    return this.getTypedRuleContext(Any_argContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterWrite(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitWrite(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitWrite(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class ReadContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_read;
    }

	any_arg() {
	    return this.getTypedRuleContext(Any_argContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterRead(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitRead(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitRead(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class OpenContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_open;
    }

	any_arg() {
	    return this.getTypedRuleContext(Any_argContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterOpen(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitOpen(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitOpen(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class PutcContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_putc;
    }

	any_arg() {
	    return this.getTypedRuleContext(Any_argContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterPutc(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitPutc(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitPutc(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class Tre_argContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_tre_arg;
    }

	any_arg = function(i) {
	    if(i===undefined) {
	        i = null;
	    }
	    if(i===null) {
	        return this.getTypedRuleContexts(Any_argContext);
	    } else {
	        return this.getTypedRuleContext(Any_argContext,i);
	    }
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterTre_arg(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitTre_arg(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitTre_arg(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class Dua_argContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_dua_arg;
    }

	any_arg = function(i) {
	    if(i===undefined) {
	        i = null;
	    }
	    if(i===null) {
	        return this.getTypedRuleContexts(Any_argContext);
	    } else {
	        return this.getTypedRuleContext(Any_argContext,i);
	    }
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterDua_arg(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitDua_arg(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitDua_arg(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class Any_argContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_any_arg;
    }

	register() {
	    return this.getTypedRuleContext(RegisterContext,0);
	};

	rdi_offset() {
	    return this.getTypedRuleContext(Rdi_offsetContext,0);
	};

	NUMBER() {
	    return this.getToken(nanParser.NUMBER, 0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterAny_arg(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitAny_arg(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitAny_arg(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class RegisterContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_register;
    }

	WORD() {
	    return this.getToken(nanParser.WORD, 0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterRegister(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitRegister(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitRegister(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class Rdi_offsetContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_rdi_offset;
    }

	NUMBER() {
	    return this.getToken(nanParser.NUMBER, 0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterRdi_offset(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitRdi_offset(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitRdi_offset(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class Size_tContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = nanParser.RULE_size_t;
    }

	NUMBER() {
	    return this.getToken(nanParser.NUMBER, 0);
	};

	enterRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.enterSize_t(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof nanListener ) {
	        listener.exitSize_t(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof nanVisitor ) {
	        return visitor.visitSize_t(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}




nanParser.ProgramContext = ProgramContext; 
nanParser.LineContext = LineContext; 
nanParser.DataContext = DataContext; 
nanParser.EntryContext = EntryContext; 
nanParser.LabelContext = LabelContext; 
nanParser.InstrContext = InstrContext; 
nanParser.CallContext = CallContext; 
nanParser.PutsContext = PutsContext; 
nanParser.PutiContext = PutiContext; 
nanParser.PushContext = PushContext; 
nanParser.PopContext = PopContext; 
nanParser.RpopContext = RpopContext; 
nanParser.IncContext = IncContext; 
nanParser.DecContext = DecContext; 
nanParser.GchContext = GchContext; 
nanParser.AddContext = AddContext; 
nanParser.DivContext = DivContext; 
nanParser.MulContext = MulContext; 
nanParser.SubContext = SubContext; 
nanParser.TestContext = TestContext; 
nanParser.JelContext = JelContext; 
nanParser.JemContext = JemContext; 
nanParser.JeContext = JeContext; 
nanParser.JlContext = JlContext; 
nanParser.JmContext = JmContext; 
nanParser.JneContext = JneContext; 
nanParser.JmpContext = JmpContext; 
nanParser.RetContext = RetContext; 
nanParser.XorContext = XorContext; 
nanParser.OrContext = OrContext; 
nanParser.NotContext = NotContext; 
nanParser.AndContext = AndContext; 
nanParser.LsContext = LsContext; 
nanParser.RsContext = RsContext; 
nanParser.MovContext = MovContext; 
nanParser.SwapContext = SwapContext; 
nanParser.MsetContext = MsetContext; 
nanParser.SwstContext = SwstContext; 
nanParser.WriteContext = WriteContext; 
nanParser.ReadContext = ReadContext; 
nanParser.OpenContext = OpenContext; 
nanParser.PutcContext = PutcContext; 
nanParser.Tre_argContext = Tre_argContext; 
nanParser.Dua_argContext = Dua_argContext; 
nanParser.Any_argContext = Any_argContext; 
nanParser.RegisterContext = RegisterContext; 
nanParser.Rdi_offsetContext = Rdi_offsetContext; 
nanParser.Size_tContext = Size_tContext; 
