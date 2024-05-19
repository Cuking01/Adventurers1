#pragma once

enum class Value_Category:u2
{
	LValue,
	RValue,
	Func
};

struct Exp_Base
{
	s2 type;
	Value_Category value_category;
	bool is_const=false;
	bool is_uneval=false;

};

template<>
struct Exp_Config<3>
{
	using Op=Symbol_Set<"*","/","%">;
};

template<>
struct Exp_Config<4>
{
	using Op=Symbol_Set<"+","-">;
};
template<>
struct Exp_Config<5>
{
	using Op=Symbol_Set<"<<",">>">;
};

template<>
struct Exp_Config<6>
{
	using Op=Symbol_Set<"<","<=",">",">=">;
};

template<>
struct Exp_Config<7>
{
	using Op=Symbol_Set<"==","!=">;
};

template<>
struct Exp_Config<8>
{
	using Op=Symbol_Set<"&">;
};

template<>
struct Exp_Config<9>
{
	using Op=Symbol_Set<"^">;
};

template<>
struct Exp_Config<10>
{
	using Op=Symbol_Set<"|">;
};

template<>
struct Exp_Config<11>
{
	using Op=Symbol_Set<"&&">;
};

template<>
struct Exp_Config<12>
{
	using Op=Symbol_Set<"||">;
};

template<>
struct Exp_Config<15>
{
	using Op=Symbol_Set<",">;
};

template<u2 k>
using Operator=typename Exp_Config<k>::Op;

template<>
struct Expk<0>:Production<Primary_Exp>,Exp_Base
{
	static constexpr Name_Str name="primary expression";

	using T1=Literal;
	using T2=Idt;
	using T3=Combination<Symbol_Set<"(">,Exp,Symbol_Set<")">>;
	using Me=Any<T1,T2,T3>;

	Me::Handler handler;

	Expk(Compiler&compiler):Production(compiler)
	{
		is_matched=handler=Me::match(compiler);
	}

	void print_ast(u2 dep,std::wostream&o)
	{
		print_tree(dep,o);
		o<<name<<'\n';
		handler->print_ast(dep+1,o);
	}
};

template<>
struct Expk<1>:Production<Expk<1>>,Exp_Base
{
	static constexpr Name_Str name="expression 1";
	using Arg_List=Combination<Expk<14>,Repeat<Any<Symbol_Set<",">,Expk<14>>>>;

	using Op=Any
	<
		Symbol_Set<"++">,
		Symbol_Set<"--">,
		Combination<Symbol_Set<"(">,Opt<Arg_List>,Symbol_Set<")">>,
		Combination<Symbol_Set<"[">,Exp,Symbol_Set<"]">>,
		Combination<Symbol_Set<".">,Idt>,
		Combination<Symbol_Set<"->">,Idt>
	>;

	using Me=Combination<Primary_Exp,Repeat<Op>>;

	Me::Handler handler;
	Expk(Compiler&compiler):Production(compiler)
	{
		is_matched=handler=Me::match(compiler);
	}

	void print_ast(u2 dep,std::wostream&o)
	{
		if(handler->template get<1>().size()==0)
		{
			handler->template get<0>().print_ast(dep,o);
			return;
		}
		print_tree(dep,o);
		o<<name<<'\n';
		handler->print_ast(dep+1,o);
	}
};

template<>
struct Expk<2>:Production<Expk<2>>,Exp_Base
{
	static constexpr Name_Str name="expression 2";
	using Op=Any
	<
		Symbol_Set<"++">,
		Symbol_Set<"--">,
		Symbol_Set<"+">,
		Symbol_Set<"-">,
		Symbol_Set<"!">,
		Symbol_Set<"~">,
		Combination<Symbol_Set<"(">,Idt,Symbol_Set<")">>,
		Symbol_Set<"*">,
		Symbol_Set<"&">,
		Combination<Symbol_Set<"sizeof">,Symbol_Set<"(">,Idt,Symbol_Set<")">>,
		Symbol_Set<"sizeof">
	>;

	using Me=Combination<Repeat<Op>,Expk<1>>;

	Me::Handler handler;

	Expk(Compiler&compiler):Production(compiler)
	{
		is_matched=handler=Me::match(compiler);
	}

	void print_ast(u2 dep,std::wostream&o)
	{
		if(handler->template get<0>().size()==0)
		{
			handler->template get<1>().print_ast(dep,o);
			return;
		}
		print_tree(dep,o);
		o<<name<<'\n';
		handler->print_ast(dep+1,o);
	}
};


template<u2 k>
struct Expk:Production<Expk<k>>,Exp_Base
{
	static constexpr Name_Str name=Name_Str("expression ")+make_name<k>();

	using Base=Production<Expk<k>>;
	using Op=Operator<k>;
	using Me=Combination<Expk<k-1>,Repeat<Combination<Op,Expk<k-1>>>>;

	Me::Handler handler;
	Expk(Compiler&compiler):Base(compiler)
	{
		Base::is_matched=handler=Me::match(compiler);
	}

	void print_ast(u2 dep,std::wostream&o)
	{
		if(handler->template get<1>().size()==0)
		{
			handler->template get<0>().print_ast(dep,o);
			return;
		}
		Base::print_tree(dep,o);
		o<<name<<'\n';
		handler->print_ast(dep+1,o);
	}
};

template<>
struct Expk<13>:Production<Expk<13>>,Exp_Base
{
	static constexpr Name_Str name="expression 13";

	using Me=Combination<Expk<12>,Repeat<Combination<Symbol_Set<"?">,Exp,Symbol_Set<":">,Expk<13>>>>;

	Production<Me>::Handler handler;
	Expk(Compiler&compiler):Production(compiler)
	{
		is_matched=handler=Me::match(compiler);
	}

	void print_ast(u2 dep,std::wostream&o)
	{
		if(handler->template get<1>().size()==0)
		{
			handler->template get<0>().print_ast(dep,o);
			return;
		}
		print_tree(dep,o);
		o<<name<<'\n';
		handler->print_ast(dep+1,o);
	}
};

template<>
struct Expk<14>:Production<Expk<14>>,Exp_Base
{
	static constexpr Name_Str name="expression 14";

	using Op=Symbol_Set<"=","+=","-=","*=","/=","%=","<<=",">>=","&=","^=","|=">;
	using Me=Combination<Repeat<Combination<Expk<13>,Op>>,Expk<13>>;

	Me::Handler handler;

	Expk(Compiler&compiler):Production(compiler)
	{
		is_matched=handler=Me::match(compiler);
	}

	void print_ast(u2 dep,std::wostream&o)
	{
		if(handler->template get<0>().size()==0)
		{
			handler->template get<1>().print_ast(dep,o);
			return;
		}
		print_tree(dep,o);
		o<<name<<'\n';
		handler->print_ast(dep+1,o);
	}
};

template<>
struct Expk<15>:Production<Expk<15>>,Exp_Base
{
	static constexpr Name_Str name="expression 15";

	using Op=Symbol_Set<",">;
	using Me=Combination<Expk<14>,Repeat<Combination<Op,Expk<14>>>>;

	Me::Handler handler;

	Expk(Compiler&compiler):Production(compiler)
	{
		is_matched=handler=Me::match(compiler);
	}

	void print_ast(u2 dep,std::wostream&o)
	{
		if(handler->template get<1>().size()==0)
		{
			handler->template get<0>().print_ast(dep,o);
			return;
		}
		print_tree(dep,o);
		o<<name<<'\n';
		handler->print_ast(dep+1,o);
	}
};

struct Exp:Production<Exp>,Exp_Base
{
	static constexpr Name_Str name="expression";
	using Me=Expk<15>;
	Me::Handler handler;

	Exp(Compiler&compiler):Production(compiler)
	{
		is_matched=handler=Me::match(compiler);
	}

	void print_ast(u2 dep,std::wostream&o)
	{
		print_tree(dep,o);
		o<<name<<'\n';
		handler->print_ast(dep+1,o);
	}
};
