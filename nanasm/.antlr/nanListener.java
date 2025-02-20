// Generated from f:/so2u/GITHUB/cuba/nan/nanasm/nan.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link nanParser}.
 */
public interface nanListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link nanParser#program}.
	 * @param ctx the parse tree
	 */
	void enterProgram(nanParser.ProgramContext ctx);
	/**
	 * Exit a parse tree produced by {@link nanParser#program}.
	 * @param ctx the parse tree
	 */
	void exitProgram(nanParser.ProgramContext ctx);
	/**
	 * Enter a parse tree produced by {@link nanParser#line}.
	 * @param ctx the parse tree
	 */
	void enterLine(nanParser.LineContext ctx);
	/**
	 * Exit a parse tree produced by {@link nanParser#line}.
	 * @param ctx the parse tree
	 */
	void exitLine(nanParser.LineContext ctx);
	/**
	 * Enter a parse tree produced by {@link nanParser#data}.
	 * @param ctx the parse tree
	 */
	void enterData(nanParser.DataContext ctx);
	/**
	 * Exit a parse tree produced by {@link nanParser#data}.
	 * @param ctx the parse tree
	 */
	void exitData(nanParser.DataContext ctx);
	/**
	 * Enter a parse tree produced by {@link nanParser#entry}.
	 * @param ctx the parse tree
	 */
	void enterEntry(nanParser.EntryContext ctx);
	/**
	 * Exit a parse tree produced by {@link nanParser#entry}.
	 * @param ctx the parse tree
	 */
	void exitEntry(nanParser.EntryContext ctx);
	/**
	 * Enter a parse tree produced by {@link nanParser#label}.
	 * @param ctx the parse tree
	 */
	void enterLabel(nanParser.LabelContext ctx);
	/**
	 * Exit a parse tree produced by {@link nanParser#label}.
	 * @param ctx the parse tree
	 */
	void exitLabel(nanParser.LabelContext ctx);
	/**
	 * Enter a parse tree produced by {@link nanParser#instr}.
	 * @param ctx the parse tree
	 */
	void enterInstr(nanParser.InstrContext ctx);
	/**
	 * Exit a parse tree produced by {@link nanParser#instr}.
	 * @param ctx the parse tree
	 */
	void exitInstr(nanParser.InstrContext ctx);
	/**
	 * Enter a parse tree produced by {@link nanParser#call}.
	 * @param ctx the parse tree
	 */
	void enterCall(nanParser.CallContext ctx);
	/**
	 * Exit a parse tree produced by {@link nanParser#call}.
	 * @param ctx the parse tree
	 */
	void exitCall(nanParser.CallContext ctx);
	/**
	 * Enter a parse tree produced by {@link nanParser#puts}.
	 * @param ctx the parse tree
	 */
	void enterPuts(nanParser.PutsContext ctx);
	/**
	 * Exit a parse tree produced by {@link nanParser#puts}.
	 * @param ctx the parse tree
	 */
	void exitPuts(nanParser.PutsContext ctx);
	/**
	 * Enter a parse tree produced by {@link nanParser#puti}.
	 * @param ctx the parse tree
	 */
	void enterPuti(nanParser.PutiContext ctx);
	/**
	 * Exit a parse tree produced by {@link nanParser#puti}.
	 * @param ctx the parse tree
	 */
	void exitPuti(nanParser.PutiContext ctx);
	/**
	 * Enter a parse tree produced by {@link nanParser#push}.
	 * @param ctx the parse tree
	 */
	void enterPush(nanParser.PushContext ctx);
	/**
	 * Exit a parse tree produced by {@link nanParser#push}.
	 * @param ctx the parse tree
	 */
	void exitPush(nanParser.PushContext ctx);
	/**
	 * Enter a parse tree produced by {@link nanParser#inc}.
	 * @param ctx the parse tree
	 */
	void enterInc(nanParser.IncContext ctx);
	/**
	 * Exit a parse tree produced by {@link nanParser#inc}.
	 * @param ctx the parse tree
	 */
	void exitInc(nanParser.IncContext ctx);
	/**
	 * Enter a parse tree produced by {@link nanParser#test}.
	 * @param ctx the parse tree
	 */
	void enterTest(nanParser.TestContext ctx);
	/**
	 * Exit a parse tree produced by {@link nanParser#test}.
	 * @param ctx the parse tree
	 */
	void exitTest(nanParser.TestContext ctx);
	/**
	 * Enter a parse tree produced by {@link nanParser#jel}.
	 * @param ctx the parse tree
	 */
	void enterJel(nanParser.JelContext ctx);
	/**
	 * Exit a parse tree produced by {@link nanParser#jel}.
	 * @param ctx the parse tree
	 */
	void exitJel(nanParser.JelContext ctx);
	/**
	 * Enter a parse tree produced by {@link nanParser#jem}.
	 * @param ctx the parse tree
	 */
	void enterJem(nanParser.JemContext ctx);
	/**
	 * Exit a parse tree produced by {@link nanParser#jem}.
	 * @param ctx the parse tree
	 */
	void exitJem(nanParser.JemContext ctx);
	/**
	 * Enter a parse tree produced by {@link nanParser#je}.
	 * @param ctx the parse tree
	 */
	void enterJe(nanParser.JeContext ctx);
	/**
	 * Exit a parse tree produced by {@link nanParser#je}.
	 * @param ctx the parse tree
	 */
	void exitJe(nanParser.JeContext ctx);
	/**
	 * Enter a parse tree produced by {@link nanParser#jl}.
	 * @param ctx the parse tree
	 */
	void enterJl(nanParser.JlContext ctx);
	/**
	 * Exit a parse tree produced by {@link nanParser#jl}.
	 * @param ctx the parse tree
	 */
	void exitJl(nanParser.JlContext ctx);
	/**
	 * Enter a parse tree produced by {@link nanParser#jm}.
	 * @param ctx the parse tree
	 */
	void enterJm(nanParser.JmContext ctx);
	/**
	 * Exit a parse tree produced by {@link nanParser#jm}.
	 * @param ctx the parse tree
	 */
	void exitJm(nanParser.JmContext ctx);
	/**
	 * Enter a parse tree produced by {@link nanParser#jne}.
	 * @param ctx the parse tree
	 */
	void enterJne(nanParser.JneContext ctx);
	/**
	 * Exit a parse tree produced by {@link nanParser#jne}.
	 * @param ctx the parse tree
	 */
	void exitJne(nanParser.JneContext ctx);
	/**
	 * Enter a parse tree produced by {@link nanParser#jmp}.
	 * @param ctx the parse tree
	 */
	void enterJmp(nanParser.JmpContext ctx);
	/**
	 * Exit a parse tree produced by {@link nanParser#jmp}.
	 * @param ctx the parse tree
	 */
	void exitJmp(nanParser.JmpContext ctx);
	/**
	 * Enter a parse tree produced by {@link nanParser#ret}.
	 * @param ctx the parse tree
	 */
	void enterRet(nanParser.RetContext ctx);
	/**
	 * Exit a parse tree produced by {@link nanParser#ret}.
	 * @param ctx the parse tree
	 */
	void exitRet(nanParser.RetContext ctx);
	/**
	 * Enter a parse tree produced by {@link nanParser#rdi_offset}.
	 * @param ctx the parse tree
	 */
	void enterRdi_offset(nanParser.Rdi_offsetContext ctx);
	/**
	 * Exit a parse tree produced by {@link nanParser#rdi_offset}.
	 * @param ctx the parse tree
	 */
	void exitRdi_offset(nanParser.Rdi_offsetContext ctx);
}