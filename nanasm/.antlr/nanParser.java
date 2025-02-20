// Generated from f:/so2u/GITHUB/cuba/nan/nanasm/nan.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue"})
public class nanParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.13.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		T__9=10, T__10=11, T__11=12, T__12=13, T__13=14, T__14=15, T__15=16, T__16=17, 
		T__17=18, T__18=19, T__19=20, WS=21, MOD=22, NUMBER=23, WORD=24, FLAG=25, 
		OPERATORS=26, TYPEMOD=27, STRING=28, SSTRING=29;
	public static final int
		RULE_program = 0, RULE_line = 1, RULE_data = 2, RULE_entry = 3, RULE_label = 4, 
		RULE_instr = 5, RULE_call = 6, RULE_puts = 7, RULE_puti = 8, RULE_push = 9, 
		RULE_inc = 10, RULE_test = 11, RULE_jel = 12, RULE_jem = 13, RULE_je = 14, 
		RULE_jl = 15, RULE_jm = 16, RULE_jne = 17, RULE_jmp = 18, RULE_ret = 19, 
		RULE_rdi_offset = 20;
	private static String[] makeRuleNames() {
		return new String[] {
			"program", "line", "data", "entry", "label", "instr", "call", "puts", 
			"puti", "push", "inc", "test", "jel", "jem", "je", "jl", "jm", "jne", 
			"jmp", "ret", "rdi_offset"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'data'", "'entry'", "':'", "'call'", "'puts'", "'puti'", "'push'", 
			"'inc'", "'test'", "'jel'", "'jem'", "'je'", "'el'", "'jm'", "'jne'", 
			"'jmp'", "'ret'", "'('", "'rdi'", "')'", null, "'db'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, null, null, "WS", "MOD", "NUMBER", 
			"WORD", "FLAG", "OPERATORS", "TYPEMOD", "STRING", "SSTRING"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "nan.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public nanParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ProgramContext extends ParserRuleContext {
		public List<LineContext> line() {
			return getRuleContexts(LineContext.class);
		}
		public LineContext line(int i) {
			return getRuleContext(LineContext.class,i);
		}
		public ProgramContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_program; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).enterProgram(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).exitProgram(this);
		}
	}

	public final ProgramContext program() throws RecognitionException {
		ProgramContext _localctx = new ProgramContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_program);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(45);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 17039350L) != 0)) {
				{
				{
				setState(42);
				line();
				}
				}
				setState(47);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class LineContext extends ParserRuleContext {
		public EntryContext entry() {
			return getRuleContext(EntryContext.class,0);
		}
		public DataContext data() {
			return getRuleContext(DataContext.class,0);
		}
		public LabelContext label() {
			return getRuleContext(LabelContext.class,0);
		}
		public InstrContext instr() {
			return getRuleContext(InstrContext.class,0);
		}
		public LineContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_line; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).enterLine(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).exitLine(this);
		}
	}

	public final LineContext line() throws RecognitionException {
		LineContext _localctx = new LineContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_line);
		try {
			setState(52);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__1:
				enterOuterAlt(_localctx, 1);
				{
				setState(48);
				entry();
				}
				break;
			case T__0:
				enterOuterAlt(_localctx, 2);
				{
				setState(49);
				data();
				}
				break;
			case WORD:
				enterOuterAlt(_localctx, 3);
				{
				setState(50);
				label();
				}
				break;
			case T__3:
			case T__4:
			case T__5:
			case T__6:
			case T__7:
			case T__8:
			case T__9:
			case T__10:
			case T__11:
			case T__12:
			case T__13:
			case T__14:
			case T__15:
			case T__16:
				enterOuterAlt(_localctx, 4);
				{
				setState(51);
				instr();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class DataContext extends ParserRuleContext {
		public TerminalNode MOD() { return getToken(nanParser.MOD, 0); }
		public TerminalNode WORD() { return getToken(nanParser.WORD, 0); }
		public TerminalNode STRING() { return getToken(nanParser.STRING, 0); }
		public DataContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_data; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).enterData(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).exitData(this);
		}
	}

	public final DataContext data() throws RecognitionException {
		DataContext _localctx = new DataContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_data);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(54);
			match(T__0);
			setState(55);
			match(MOD);
			setState(56);
			match(WORD);
			setState(57);
			match(STRING);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class EntryContext extends ParserRuleContext {
		public TerminalNode WORD() { return getToken(nanParser.WORD, 0); }
		public EntryContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_entry; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).enterEntry(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).exitEntry(this);
		}
	}

	public final EntryContext entry() throws RecognitionException {
		EntryContext _localctx = new EntryContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_entry);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(59);
			match(T__1);
			setState(60);
			match(WORD);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class LabelContext extends ParserRuleContext {
		public TerminalNode WORD() { return getToken(nanParser.WORD, 0); }
		public LabelContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_label; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).enterLabel(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).exitLabel(this);
		}
	}

	public final LabelContext label() throws RecognitionException {
		LabelContext _localctx = new LabelContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_label);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(62);
			match(WORD);
			setState(63);
			match(T__2);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class InstrContext extends ParserRuleContext {
		public PutsContext puts() {
			return getRuleContext(PutsContext.class,0);
		}
		public PutiContext puti() {
			return getRuleContext(PutiContext.class,0);
		}
		public PushContext push() {
			return getRuleContext(PushContext.class,0);
		}
		public IncContext inc() {
			return getRuleContext(IncContext.class,0);
		}
		public TestContext test() {
			return getRuleContext(TestContext.class,0);
		}
		public JelContext jel() {
			return getRuleContext(JelContext.class,0);
		}
		public JemContext jem() {
			return getRuleContext(JemContext.class,0);
		}
		public JeContext je() {
			return getRuleContext(JeContext.class,0);
		}
		public JlContext jl() {
			return getRuleContext(JlContext.class,0);
		}
		public JmContext jm() {
			return getRuleContext(JmContext.class,0);
		}
		public JneContext jne() {
			return getRuleContext(JneContext.class,0);
		}
		public JmpContext jmp() {
			return getRuleContext(JmpContext.class,0);
		}
		public RetContext ret() {
			return getRuleContext(RetContext.class,0);
		}
		public CallContext call() {
			return getRuleContext(CallContext.class,0);
		}
		public InstrContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_instr; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).enterInstr(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).exitInstr(this);
		}
	}

	public final InstrContext instr() throws RecognitionException {
		InstrContext _localctx = new InstrContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_instr);
		try {
			setState(79);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__4:
				enterOuterAlt(_localctx, 1);
				{
				setState(65);
				puts();
				}
				break;
			case T__5:
				enterOuterAlt(_localctx, 2);
				{
				setState(66);
				puti();
				}
				break;
			case T__6:
				enterOuterAlt(_localctx, 3);
				{
				setState(67);
				push();
				}
				break;
			case T__7:
				enterOuterAlt(_localctx, 4);
				{
				setState(68);
				inc();
				}
				break;
			case T__8:
				enterOuterAlt(_localctx, 5);
				{
				setState(69);
				test();
				}
				break;
			case T__9:
				enterOuterAlt(_localctx, 6);
				{
				setState(70);
				jel();
				}
				break;
			case T__10:
				enterOuterAlt(_localctx, 7);
				{
				setState(71);
				jem();
				}
				break;
			case T__11:
				enterOuterAlt(_localctx, 8);
				{
				setState(72);
				je();
				}
				break;
			case T__12:
				enterOuterAlt(_localctx, 9);
				{
				setState(73);
				jl();
				}
				break;
			case T__13:
				enterOuterAlt(_localctx, 10);
				{
				setState(74);
				jm();
				}
				break;
			case T__14:
				enterOuterAlt(_localctx, 11);
				{
				setState(75);
				jne();
				}
				break;
			case T__15:
				enterOuterAlt(_localctx, 12);
				{
				setState(76);
				jmp();
				}
				break;
			case T__16:
				enterOuterAlt(_localctx, 13);
				{
				setState(77);
				ret();
				}
				break;
			case T__3:
				enterOuterAlt(_localctx, 14);
				{
				setState(78);
				call();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class CallContext extends ParserRuleContext {
		public TerminalNode WORD() { return getToken(nanParser.WORD, 0); }
		public CallContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_call; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).enterCall(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).exitCall(this);
		}
	}

	public final CallContext call() throws RecognitionException {
		CallContext _localctx = new CallContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_call);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(81);
			match(T__3);
			setState(82);
			match(WORD);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class PutsContext extends ParserRuleContext {
		public TerminalNode WORD() { return getToken(nanParser.WORD, 0); }
		public PutsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_puts; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).enterPuts(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).exitPuts(this);
		}
	}

	public final PutsContext puts() throws RecognitionException {
		PutsContext _localctx = new PutsContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_puts);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(84);
			match(T__4);
			setState(85);
			match(WORD);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class PutiContext extends ParserRuleContext {
		public Rdi_offsetContext rdi_offset() {
			return getRuleContext(Rdi_offsetContext.class,0);
		}
		public PutiContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_puti; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).enterPuti(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).exitPuti(this);
		}
	}

	public final PutiContext puti() throws RecognitionException {
		PutiContext _localctx = new PutiContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_puti);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(87);
			match(T__5);
			setState(88);
			rdi_offset();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class PushContext extends ParserRuleContext {
		public TerminalNode NUMBER() { return getToken(nanParser.NUMBER, 0); }
		public Rdi_offsetContext rdi_offset() {
			return getRuleContext(Rdi_offsetContext.class,0);
		}
		public PushContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_push; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).enterPush(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).exitPush(this);
		}
	}

	public final PushContext push() throws RecognitionException {
		PushContext _localctx = new PushContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_push);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(90);
			match(T__6);
			setState(93);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case NUMBER:
				{
				setState(91);
				match(NUMBER);
				}
				break;
			case T__17:
				{
				setState(92);
				rdi_offset();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class IncContext extends ParserRuleContext {
		public Rdi_offsetContext rdi_offset() {
			return getRuleContext(Rdi_offsetContext.class,0);
		}
		public IncContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_inc; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).enterInc(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).exitInc(this);
		}
	}

	public final IncContext inc() throws RecognitionException {
		IncContext _localctx = new IncContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_inc);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(95);
			match(T__7);
			setState(96);
			rdi_offset();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class TestContext extends ParserRuleContext {
		public TestContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_test; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).enterTest(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).exitTest(this);
		}
	}

	public final TestContext test() throws RecognitionException {
		TestContext _localctx = new TestContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_test);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(98);
			match(T__8);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class JelContext extends ParserRuleContext {
		public TerminalNode WORD() { return getToken(nanParser.WORD, 0); }
		public JelContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_jel; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).enterJel(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).exitJel(this);
		}
	}

	public final JelContext jel() throws RecognitionException {
		JelContext _localctx = new JelContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_jel);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(100);
			match(T__9);
			setState(101);
			match(WORD);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class JemContext extends ParserRuleContext {
		public TerminalNode WORD() { return getToken(nanParser.WORD, 0); }
		public JemContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_jem; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).enterJem(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).exitJem(this);
		}
	}

	public final JemContext jem() throws RecognitionException {
		JemContext _localctx = new JemContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_jem);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(103);
			match(T__10);
			setState(104);
			match(WORD);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class JeContext extends ParserRuleContext {
		public TerminalNode WORD() { return getToken(nanParser.WORD, 0); }
		public JeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_je; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).enterJe(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).exitJe(this);
		}
	}

	public final JeContext je() throws RecognitionException {
		JeContext _localctx = new JeContext(_ctx, getState());
		enterRule(_localctx, 28, RULE_je);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(106);
			match(T__11);
			setState(107);
			match(WORD);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class JlContext extends ParserRuleContext {
		public TerminalNode WORD() { return getToken(nanParser.WORD, 0); }
		public JlContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_jl; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).enterJl(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).exitJl(this);
		}
	}

	public final JlContext jl() throws RecognitionException {
		JlContext _localctx = new JlContext(_ctx, getState());
		enterRule(_localctx, 30, RULE_jl);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(109);
			match(T__12);
			setState(110);
			match(WORD);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class JmContext extends ParserRuleContext {
		public TerminalNode WORD() { return getToken(nanParser.WORD, 0); }
		public JmContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_jm; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).enterJm(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).exitJm(this);
		}
	}

	public final JmContext jm() throws RecognitionException {
		JmContext _localctx = new JmContext(_ctx, getState());
		enterRule(_localctx, 32, RULE_jm);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(112);
			match(T__13);
			setState(113);
			match(WORD);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class JneContext extends ParserRuleContext {
		public TerminalNode WORD() { return getToken(nanParser.WORD, 0); }
		public JneContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_jne; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).enterJne(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).exitJne(this);
		}
	}

	public final JneContext jne() throws RecognitionException {
		JneContext _localctx = new JneContext(_ctx, getState());
		enterRule(_localctx, 34, RULE_jne);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(115);
			match(T__14);
			setState(116);
			match(WORD);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class JmpContext extends ParserRuleContext {
		public TerminalNode WORD() { return getToken(nanParser.WORD, 0); }
		public JmpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_jmp; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).enterJmp(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).exitJmp(this);
		}
	}

	public final JmpContext jmp() throws RecognitionException {
		JmpContext _localctx = new JmpContext(_ctx, getState());
		enterRule(_localctx, 36, RULE_jmp);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(118);
			match(T__15);
			setState(119);
			match(WORD);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class RetContext extends ParserRuleContext {
		public RetContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_ret; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).enterRet(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).exitRet(this);
		}
	}

	public final RetContext ret() throws RecognitionException {
		RetContext _localctx = new RetContext(_ctx, getState());
		enterRule(_localctx, 38, RULE_ret);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(121);
			match(T__16);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Rdi_offsetContext extends ParserRuleContext {
		public TerminalNode NUMBER() { return getToken(nanParser.NUMBER, 0); }
		public Rdi_offsetContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_rdi_offset; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).enterRdi_offset(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof nanListener ) ((nanListener)listener).exitRdi_offset(this);
		}
	}

	public final Rdi_offsetContext rdi_offset() throws RecognitionException {
		Rdi_offsetContext _localctx = new Rdi_offsetContext(_ctx, getState());
		enterRule(_localctx, 40, RULE_rdi_offset);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(123);
			match(T__17);
			setState(124);
			match(T__18);
			setState(125);
			match(NUMBER);
			setState(126);
			match(T__19);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static final String _serializedATN =
		"\u0004\u0001\u001d\u0081\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001"+
		"\u0002\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004\u0007\u0004"+
		"\u0002\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002\u0007\u0007\u0007"+
		"\u0002\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002\u000b\u0007\u000b"+
		"\u0002\f\u0007\f\u0002\r\u0007\r\u0002\u000e\u0007\u000e\u0002\u000f\u0007"+
		"\u000f\u0002\u0010\u0007\u0010\u0002\u0011\u0007\u0011\u0002\u0012\u0007"+
		"\u0012\u0002\u0013\u0007\u0013\u0002\u0014\u0007\u0014\u0001\u0000\u0005"+
		"\u0000,\b\u0000\n\u0000\f\u0000/\t\u0000\u0001\u0001\u0001\u0001\u0001"+
		"\u0001\u0001\u0001\u0003\u00015\b\u0001\u0001\u0002\u0001\u0002\u0001"+
		"\u0002\u0001\u0002\u0001\u0002\u0001\u0003\u0001\u0003\u0001\u0003\u0001"+
		"\u0004\u0001\u0004\u0001\u0004\u0001\u0005\u0001\u0005\u0001\u0005\u0001"+
		"\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001"+
		"\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0003\u0005P\b"+
		"\u0005\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0007\u0001\u0007\u0001"+
		"\u0007\u0001\b\u0001\b\u0001\b\u0001\t\u0001\t\u0001\t\u0003\t^\b\t\u0001"+
		"\n\u0001\n\u0001\n\u0001\u000b\u0001\u000b\u0001\f\u0001\f\u0001\f\u0001"+
		"\r\u0001\r\u0001\r\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000f\u0001"+
		"\u000f\u0001\u000f\u0001\u0010\u0001\u0010\u0001\u0010\u0001\u0011\u0001"+
		"\u0011\u0001\u0011\u0001\u0012\u0001\u0012\u0001\u0012\u0001\u0013\u0001"+
		"\u0013\u0001\u0014\u0001\u0014\u0001\u0014\u0001\u0014\u0001\u0014\u0001"+
		"\u0014\u0000\u0000\u0015\u0000\u0002\u0004\u0006\b\n\f\u000e\u0010\u0012"+
		"\u0014\u0016\u0018\u001a\u001c\u001e \"$&(\u0000\u0000}\u0000-\u0001\u0000"+
		"\u0000\u0000\u00024\u0001\u0000\u0000\u0000\u00046\u0001\u0000\u0000\u0000"+
		"\u0006;\u0001\u0000\u0000\u0000\b>\u0001\u0000\u0000\u0000\nO\u0001\u0000"+
		"\u0000\u0000\fQ\u0001\u0000\u0000\u0000\u000eT\u0001\u0000\u0000\u0000"+
		"\u0010W\u0001\u0000\u0000\u0000\u0012Z\u0001\u0000\u0000\u0000\u0014_"+
		"\u0001\u0000\u0000\u0000\u0016b\u0001\u0000\u0000\u0000\u0018d\u0001\u0000"+
		"\u0000\u0000\u001ag\u0001\u0000\u0000\u0000\u001cj\u0001\u0000\u0000\u0000"+
		"\u001em\u0001\u0000\u0000\u0000 p\u0001\u0000\u0000\u0000\"s\u0001\u0000"+
		"\u0000\u0000$v\u0001\u0000\u0000\u0000&y\u0001\u0000\u0000\u0000({\u0001"+
		"\u0000\u0000\u0000*,\u0003\u0002\u0001\u0000+*\u0001\u0000\u0000\u0000"+
		",/\u0001\u0000\u0000\u0000-+\u0001\u0000\u0000\u0000-.\u0001\u0000\u0000"+
		"\u0000.\u0001\u0001\u0000\u0000\u0000/-\u0001\u0000\u0000\u000005\u0003"+
		"\u0006\u0003\u000015\u0003\u0004\u0002\u000025\u0003\b\u0004\u000035\u0003"+
		"\n\u0005\u000040\u0001\u0000\u0000\u000041\u0001\u0000\u0000\u000042\u0001"+
		"\u0000\u0000\u000043\u0001\u0000\u0000\u00005\u0003\u0001\u0000\u0000"+
		"\u000067\u0005\u0001\u0000\u000078\u0005\u0016\u0000\u000089\u0005\u0018"+
		"\u0000\u00009:\u0005\u001c\u0000\u0000:\u0005\u0001\u0000\u0000\u0000"+
		";<\u0005\u0002\u0000\u0000<=\u0005\u0018\u0000\u0000=\u0007\u0001\u0000"+
		"\u0000\u0000>?\u0005\u0018\u0000\u0000?@\u0005\u0003\u0000\u0000@\t\u0001"+
		"\u0000\u0000\u0000AP\u0003\u000e\u0007\u0000BP\u0003\u0010\b\u0000CP\u0003"+
		"\u0012\t\u0000DP\u0003\u0014\n\u0000EP\u0003\u0016\u000b\u0000FP\u0003"+
		"\u0018\f\u0000GP\u0003\u001a\r\u0000HP\u0003\u001c\u000e\u0000IP\u0003"+
		"\u001e\u000f\u0000JP\u0003 \u0010\u0000KP\u0003\"\u0011\u0000LP\u0003"+
		"$\u0012\u0000MP\u0003&\u0013\u0000NP\u0003\f\u0006\u0000OA\u0001\u0000"+
		"\u0000\u0000OB\u0001\u0000\u0000\u0000OC\u0001\u0000\u0000\u0000OD\u0001"+
		"\u0000\u0000\u0000OE\u0001\u0000\u0000\u0000OF\u0001\u0000\u0000\u0000"+
		"OG\u0001\u0000\u0000\u0000OH\u0001\u0000\u0000\u0000OI\u0001\u0000\u0000"+
		"\u0000OJ\u0001\u0000\u0000\u0000OK\u0001\u0000\u0000\u0000OL\u0001\u0000"+
		"\u0000\u0000OM\u0001\u0000\u0000\u0000ON\u0001\u0000\u0000\u0000P\u000b"+
		"\u0001\u0000\u0000\u0000QR\u0005\u0004\u0000\u0000RS\u0005\u0018\u0000"+
		"\u0000S\r\u0001\u0000\u0000\u0000TU\u0005\u0005\u0000\u0000UV\u0005\u0018"+
		"\u0000\u0000V\u000f\u0001\u0000\u0000\u0000WX\u0005\u0006\u0000\u0000"+
		"XY\u0003(\u0014\u0000Y\u0011\u0001\u0000\u0000\u0000Z]\u0005\u0007\u0000"+
		"\u0000[^\u0005\u0017\u0000\u0000\\^\u0003(\u0014\u0000][\u0001\u0000\u0000"+
		"\u0000]\\\u0001\u0000\u0000\u0000^\u0013\u0001\u0000\u0000\u0000_`\u0005"+
		"\b\u0000\u0000`a\u0003(\u0014\u0000a\u0015\u0001\u0000\u0000\u0000bc\u0005"+
		"\t\u0000\u0000c\u0017\u0001\u0000\u0000\u0000de\u0005\n\u0000\u0000ef"+
		"\u0005\u0018\u0000\u0000f\u0019\u0001\u0000\u0000\u0000gh\u0005\u000b"+
		"\u0000\u0000hi\u0005\u0018\u0000\u0000i\u001b\u0001\u0000\u0000\u0000"+
		"jk\u0005\f\u0000\u0000kl\u0005\u0018\u0000\u0000l\u001d\u0001\u0000\u0000"+
		"\u0000mn\u0005\r\u0000\u0000no\u0005\u0018\u0000\u0000o\u001f\u0001\u0000"+
		"\u0000\u0000pq\u0005\u000e\u0000\u0000qr\u0005\u0018\u0000\u0000r!\u0001"+
		"\u0000\u0000\u0000st\u0005\u000f\u0000\u0000tu\u0005\u0018\u0000\u0000"+
		"u#\u0001\u0000\u0000\u0000vw\u0005\u0010\u0000\u0000wx\u0005\u0018\u0000"+
		"\u0000x%\u0001\u0000\u0000\u0000yz\u0005\u0011\u0000\u0000z\'\u0001\u0000"+
		"\u0000\u0000{|\u0005\u0012\u0000\u0000|}\u0005\u0013\u0000\u0000}~\u0005"+
		"\u0017\u0000\u0000~\u007f\u0005\u0014\u0000\u0000\u007f)\u0001\u0000\u0000"+
		"\u0000\u0004-4O]";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}