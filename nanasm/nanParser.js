// Generated from e:/so2u/GITHUB/cuba/nan/nanasm/nan.g4 by ANTLR 4.13.1
// jshint ignore: start
import antlr4 from 'antlr4';
import nanListener from './nanListener.js';
import nanVisitor from './nanVisitor.js';

const serializedATN = [4,1,28,123,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,
4,2,5,7,5,2,6,7,6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,
2,13,7,13,2,14,7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,1,
0,5,0,42,8,0,10,0,12,0,45,9,0,1,1,1,1,1,1,1,1,3,1,51,8,1,1,2,1,2,1,2,1,2,
1,2,1,3,1,3,1,3,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,
1,5,1,5,3,5,77,8,5,1,6,1,6,1,6,1,7,1,7,1,7,1,8,1,8,1,8,3,8,88,8,8,1,9,1,
9,1,9,1,10,1,10,1,11,1,11,1,11,1,12,1,12,1,12,1,13,1,13,1,13,1,14,1,14,1,
14,1,15,1,15,1,15,1,16,1,16,1,16,1,17,1,17,1,17,1,18,1,18,1,19,1,19,1,19,
1,19,1,19,1,19,0,0,20,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,
38,0,0,119,0,43,1,0,0,0,2,50,1,0,0,0,4,52,1,0,0,0,6,57,1,0,0,0,8,60,1,0,
0,0,10,76,1,0,0,0,12,78,1,0,0,0,14,81,1,0,0,0,16,84,1,0,0,0,18,89,1,0,0,
0,20,92,1,0,0,0,22,94,1,0,0,0,24,97,1,0,0,0,26,100,1,0,0,0,28,103,1,0,0,
0,30,106,1,0,0,0,32,109,1,0,0,0,34,112,1,0,0,0,36,115,1,0,0,0,38,117,1,0,
0,0,40,42,3,2,1,0,41,40,1,0,0,0,42,45,1,0,0,0,43,41,1,0,0,0,43,44,1,0,0,
0,44,1,1,0,0,0,45,43,1,0,0,0,46,51,3,6,3,0,47,51,3,4,2,0,48,51,3,8,4,0,49,
51,3,10,5,0,50,46,1,0,0,0,50,47,1,0,0,0,50,48,1,0,0,0,50,49,1,0,0,0,51,3,
1,0,0,0,52,53,5,1,0,0,53,54,5,21,0,0,54,55,5,23,0,0,55,56,5,27,0,0,56,5,
1,0,0,0,57,58,5,2,0,0,58,59,5,23,0,0,59,7,1,0,0,0,60,61,5,23,0,0,61,62,5,
3,0,0,62,9,1,0,0,0,63,77,3,12,6,0,64,77,3,14,7,0,65,77,3,16,8,0,66,77,3,
18,9,0,67,77,3,20,10,0,68,77,3,22,11,0,69,77,3,24,12,0,70,77,3,26,13,0,71,
77,3,28,14,0,72,77,3,30,15,0,73,77,3,32,16,0,74,77,3,34,17,0,75,77,3,36,
18,0,76,63,1,0,0,0,76,64,1,0,0,0,76,65,1,0,0,0,76,66,1,0,0,0,76,67,1,0,0,
0,76,68,1,0,0,0,76,69,1,0,0,0,76,70,1,0,0,0,76,71,1,0,0,0,76,72,1,0,0,0,
76,73,1,0,0,0,76,74,1,0,0,0,76,75,1,0,0,0,77,11,1,0,0,0,78,79,5,4,0,0,79,
80,5,23,0,0,80,13,1,0,0,0,81,82,5,5,0,0,82,83,3,38,19,0,83,15,1,0,0,0,84,
87,5,6,0,0,85,88,5,22,0,0,86,88,3,38,19,0,87,85,1,0,0,0,87,86,1,0,0,0,88,
17,1,0,0,0,89,90,5,7,0,0,90,91,3,38,19,0,91,19,1,0,0,0,92,93,5,8,0,0,93,
21,1,0,0,0,94,95,5,9,0,0,95,96,5,23,0,0,96,23,1,0,0,0,97,98,5,10,0,0,98,
99,5,23,0,0,99,25,1,0,0,0,100,101,5,11,0,0,101,102,5,23,0,0,102,27,1,0,0,
0,103,104,5,12,0,0,104,105,5,23,0,0,105,29,1,0,0,0,106,107,5,13,0,0,107,
108,5,23,0,0,108,31,1,0,0,0,109,110,5,14,0,0,110,111,5,23,0,0,111,33,1,0,
0,0,112,113,5,15,0,0,113,114,5,23,0,0,114,35,1,0,0,0,115,116,5,16,0,0,116,
37,1,0,0,0,117,118,5,17,0,0,118,119,5,18,0,0,119,120,5,22,0,0,120,121,5,
19,0,0,121,39,1,0,0,0,4,43,50,76,87];


const atn = new antlr4.atn.ATNDeserializer().deserialize(serializedATN);

const decisionsToDFA = atn.decisionToState.map( (ds, index) => new antlr4.dfa.DFA(ds, index) );

const sharedContextCache = new antlr4.atn.PredictionContextCache();

export default class nanParser extends antlr4.Parser {

    static grammarFileName = "nan.g4";
    static literalNames = [ null, "'data'", "'entry'", "':'", "'puts'", 
                            "'puti'", "'push'", "'inc'", "'test'", "'jel'", 
                            "'jem'", "'je'", "'el'", "'jm'", "'jne'", "'jmp'", 
                            "'ret'", "'('", "'rdi'", "')'", null, "'db'" ];
    static symbolicNames = [ null, null, null, null, null, null, null, null, 
                             null, null, null, null, null, null, null, null, 
                             null, null, null, null, "WS", "MOD", "NUMBER", 
                             "WORD", "FLAG", "OPERATORS", "TYPEMOD", "STRING", 
                             "SSTRING" ];
    static ruleNames = [ "program", "line", "data", "entry", "label", "instr", 
                         "puts", "puti", "push", "inc", "test", "jel", "jem", 
                         "je", "jl", "jm", "jne", "jmp", "ret", "rdi_offset" ];

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
	        this.state = 43;
	        this._errHandler.sync(this);
	        _la = this._input.LA(1);
	        while((((_la) & ~0x1f) === 0 && ((1 << _la) & 8519670) !== 0)) {
	            this.state = 40;
	            this.line();
	            this.state = 45;
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
	        this.state = 50;
	        this._errHandler.sync(this);
	        switch(this._input.LA(1)) {
	        case 2:
	            this.enterOuterAlt(localctx, 1);
	            this.state = 46;
	            this.entry();
	            break;
	        case 1:
	            this.enterOuterAlt(localctx, 2);
	            this.state = 47;
	            this.data();
	            break;
	        case 23:
	            this.enterOuterAlt(localctx, 3);
	            this.state = 48;
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
	            this.enterOuterAlt(localctx, 4);
	            this.state = 49;
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
	        this.state = 52;
	        this.match(nanParser.T__0);
	        this.state = 53;
	        this.match(nanParser.MOD);
	        this.state = 54;
	        this.match(nanParser.WORD);
	        this.state = 55;
	        this.match(nanParser.STRING);
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
	        this.state = 57;
	        this.match(nanParser.T__1);
	        this.state = 58;
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
	        this.state = 60;
	        this.match(nanParser.WORD);
	        this.state = 61;
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
	        this.state = 76;
	        this._errHandler.sync(this);
	        switch(this._input.LA(1)) {
	        case 4:
	            this.enterOuterAlt(localctx, 1);
	            this.state = 63;
	            this.puts();
	            break;
	        case 5:
	            this.enterOuterAlt(localctx, 2);
	            this.state = 64;
	            this.puti();
	            break;
	        case 6:
	            this.enterOuterAlt(localctx, 3);
	            this.state = 65;
	            this.push();
	            break;
	        case 7:
	            this.enterOuterAlt(localctx, 4);
	            this.state = 66;
	            this.inc();
	            break;
	        case 8:
	            this.enterOuterAlt(localctx, 5);
	            this.state = 67;
	            this.test();
	            break;
	        case 9:
	            this.enterOuterAlt(localctx, 6);
	            this.state = 68;
	            this.jel();
	            break;
	        case 10:
	            this.enterOuterAlt(localctx, 7);
	            this.state = 69;
	            this.jem();
	            break;
	        case 11:
	            this.enterOuterAlt(localctx, 8);
	            this.state = 70;
	            this.je();
	            break;
	        case 12:
	            this.enterOuterAlt(localctx, 9);
	            this.state = 71;
	            this.jl();
	            break;
	        case 13:
	            this.enterOuterAlt(localctx, 10);
	            this.state = 72;
	            this.jm();
	            break;
	        case 14:
	            this.enterOuterAlt(localctx, 11);
	            this.state = 73;
	            this.jne();
	            break;
	        case 15:
	            this.enterOuterAlt(localctx, 12);
	            this.state = 74;
	            this.jmp();
	            break;
	        case 16:
	            this.enterOuterAlt(localctx, 13);
	            this.state = 75;
	            this.ret();
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



	puts() {
	    let localctx = new PutsContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 12, nanParser.RULE_puts);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 78;
	        this.match(nanParser.T__3);
	        this.state = 79;
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
	    this.enterRule(localctx, 14, nanParser.RULE_puti);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 81;
	        this.match(nanParser.T__4);
	        this.state = 82;
	        this.rdi_offset();
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
	    this.enterRule(localctx, 16, nanParser.RULE_push);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 84;
	        this.match(nanParser.T__5);
	        this.state = 87;
	        this._errHandler.sync(this);
	        switch(this._input.LA(1)) {
	        case 22:
	            this.state = 85;
	            this.match(nanParser.NUMBER);
	            break;
	        case 17:
	            this.state = 86;
	            this.rdi_offset();
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



	inc() {
	    let localctx = new IncContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 18, nanParser.RULE_inc);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 89;
	        this.match(nanParser.T__6);
	        this.state = 90;
	        this.rdi_offset();
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
	    this.enterRule(localctx, 20, nanParser.RULE_test);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 92;
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



	jel() {
	    let localctx = new JelContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 22, nanParser.RULE_jel);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 94;
	        this.match(nanParser.T__8);
	        this.state = 95;
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
	    this.enterRule(localctx, 24, nanParser.RULE_jem);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 97;
	        this.match(nanParser.T__9);
	        this.state = 98;
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
	    this.enterRule(localctx, 26, nanParser.RULE_je);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 100;
	        this.match(nanParser.T__10);
	        this.state = 101;
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
	    this.enterRule(localctx, 28, nanParser.RULE_jl);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 103;
	        this.match(nanParser.T__11);
	        this.state = 104;
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
	    this.enterRule(localctx, 30, nanParser.RULE_jm);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 106;
	        this.match(nanParser.T__12);
	        this.state = 107;
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
	    this.enterRule(localctx, 32, nanParser.RULE_jne);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 109;
	        this.match(nanParser.T__13);
	        this.state = 110;
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
	    this.enterRule(localctx, 34, nanParser.RULE_jmp);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 112;
	        this.match(nanParser.T__14);
	        this.state = 113;
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
	    this.enterRule(localctx, 36, nanParser.RULE_ret);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 115;
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



	rdi_offset() {
	    let localctx = new Rdi_offsetContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 38, nanParser.RULE_rdi_offset);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 117;
	        this.match(nanParser.T__16);
	        this.state = 118;
	        this.match(nanParser.T__17);
	        this.state = 119;
	        this.match(nanParser.NUMBER);
	        this.state = 120;
	        this.match(nanParser.T__18);
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
nanParser.WS = 20;
nanParser.MOD = 21;
nanParser.NUMBER = 22;
nanParser.WORD = 23;
nanParser.FLAG = 24;
nanParser.OPERATORS = 25;
nanParser.TYPEMOD = 26;
nanParser.STRING = 27;
nanParser.SSTRING = 28;

nanParser.RULE_program = 0;
nanParser.RULE_line = 1;
nanParser.RULE_data = 2;
nanParser.RULE_entry = 3;
nanParser.RULE_label = 4;
nanParser.RULE_instr = 5;
nanParser.RULE_puts = 6;
nanParser.RULE_puti = 7;
nanParser.RULE_push = 8;
nanParser.RULE_inc = 9;
nanParser.RULE_test = 10;
nanParser.RULE_jel = 11;
nanParser.RULE_jem = 12;
nanParser.RULE_je = 13;
nanParser.RULE_jl = 14;
nanParser.RULE_jm = 15;
nanParser.RULE_jne = 16;
nanParser.RULE_jmp = 17;
nanParser.RULE_ret = 18;
nanParser.RULE_rdi_offset = 19;

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

	puts() {
	    return this.getTypedRuleContext(PutsContext,0);
	};

	puti() {
	    return this.getTypedRuleContext(PutiContext,0);
	};

	push() {
	    return this.getTypedRuleContext(PushContext,0);
	};

	inc() {
	    return this.getTypedRuleContext(IncContext,0);
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

	rdi_offset() {
	    return this.getTypedRuleContext(Rdi_offsetContext,0);
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

	NUMBER() {
	    return this.getToken(nanParser.NUMBER, 0);
	};

	rdi_offset() {
	    return this.getTypedRuleContext(Rdi_offsetContext,0);
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

	rdi_offset() {
	    return this.getTypedRuleContext(Rdi_offsetContext,0);
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




nanParser.ProgramContext = ProgramContext; 
nanParser.LineContext = LineContext; 
nanParser.DataContext = DataContext; 
nanParser.EntryContext = EntryContext; 
nanParser.LabelContext = LabelContext; 
nanParser.InstrContext = InstrContext; 
nanParser.PutsContext = PutsContext; 
nanParser.PutiContext = PutiContext; 
nanParser.PushContext = PushContext; 
nanParser.IncContext = IncContext; 
nanParser.TestContext = TestContext; 
nanParser.JelContext = JelContext; 
nanParser.JemContext = JemContext; 
nanParser.JeContext = JeContext; 
nanParser.JlContext = JlContext; 
nanParser.JmContext = JmContext; 
nanParser.JneContext = JneContext; 
nanParser.JmpContext = JmpContext; 
nanParser.RetContext = RetContext; 
nanParser.Rdi_offsetContext = Rdi_offsetContext; 
