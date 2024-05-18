#pragma once

struct Label:Production<Label>
{
	static constexpr Name_Str name="label";

	using Me=Combination<Any<Combination<Symbol_Set<"case">,Exp>,Symbol_Set<"default">,Idt>,Symbol_Set<":">>;
	Me::Handler handler;
	Label(Compiler&compiler):Production(compiler)
	{
		is_matched=handler=Me::match(compiler);
	}

};	


struct Stat:Production<Stat>
{
	static constexpr Name_Str name="statement";

	using Me=Combination<Opt<Label>,Any<Compound_Stat,Exp_Stat,Select_Stat,Loop_Stat,Jump_Stat,Symbol_Set<";">>>;
	Me::Handler handler;
	Stat(Compiler&compiler):Production(compiler)
	{
		is_matched=handler=Me::match(compiler);
	}
};

struct Compound_Stat:Production<Compound_Stat>
{
	static constexpr Name_Str name="compound statement";

	using Decl_Stat=Combination<Declaration,Symbol_Set<";">>;//不是语句，但是暂时这么命名
	using Me=Combination<Symbol_Set<"{">,Repeat<Any<Decl_Stat,Stat>>,Symbol_Set<"}">>;
	Me::Handler handler;
	Compound_Stat(Compiler&compiler):Production(compiler)
	{
		is_matched=handler=Me::match(compiler);
	}
};

struct Exp_Stat:Production<Exp_Stat>
{
	static constexpr Name_Str name="expression statement";
	using Me=Combination<Exp,Symbol_Set<";">>;
	Me::Handler handler;
	Exp_Stat(Compiler&compiler):Production(compiler)
	{
		is_matched=handler=Me::match(compiler);
	}
};

struct Select_Stat:Production<Select_Stat>
{
	static constexpr Name_Str name="selection statement";
	using IF=Combination<Symbol_Set<"if">,Symbol_Set<"(">,Exp,Symbol_Set<")">,Stat>;
	using ELSE=Combination<Symbol_Set<"else">,Stat>;
	using SWITCH=Combination<Symbol_Set<"switch">,Symbol_Set<"(">,Exp,Symbol_Set<")">,Stat>;
	using Me=Any<Combination<IF,Opt<ELSE>>,SWITCH>;

	Me::Handler handler;
	Select_Stat(Compiler&compiler):Production(compiler)
	{
		is_matched=handler=Me::match(compiler);
	}
};

struct Loop_Stat:Production<Loop_Stat>
{
	static constexpr Name_Str name="loop statement";
	using DO_WHILE=Combination<Symbol_Set<"do">,Stat,Symbol_Set<"while">,Symbol_Set<"(">,Exp,Symbol_Set<")">,Symbol_Set<";">>;
	using WHILE=Combination<Symbol_Set<"while">,Symbol_Set<"(">,Exp,Symbol_Set<")">,Stat>;
	using FOR=Combination<Symbol_Set<"for">,Symbol_Set<"(">,Opt<Any<Exp,Declaration>>,Symbol_Set<";">,Opt<Exp>,Symbol_Set<";">,Opt<Exp>,Symbol_Set<")">,Stat>;
	using Me=Any<DO_WHILE,WHILE,FOR>;

	Me::Handler handler;
	Loop_Stat(Compiler&compiler):Production(compiler)
	{
		is_matched=handler=Me::match(compiler);
	}
};

struct Jump_Stat:Production<Jump_Stat>
{
	static constexpr Name_Str name="jump statement";
	using BREAK=Combination<Symbol_Set<"break">,Symbol_Set<";">>;
	using CONTINUE=Combination<Symbol_Set<"continue">,Symbol_Set<";">>;
	using RETURN=Combination<Symbol_Set<"return">,Exp_Stat>;
	using GOTO=Combination<Symbol_Set<"goto">,Idt>;

	using Me=Any<BREAK,CONTINUE,RETURN,GOTO>;

	Me::Handler handler;
	Jump_Stat(Compiler&compiler):Production(compiler)
	{
		is_matched=handler=Me::match(compiler);
	}
};


