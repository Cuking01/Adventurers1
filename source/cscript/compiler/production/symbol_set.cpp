#pragma once


template<Symbol_Str... symbols>
Symbol_Set<symbols...>::Symbol_Set(Compiler&compiler):Base(compiler)
{
	auto*p=compiler.match_symbol<symbols...>();
	if(p)
	{
		Base::is_matched=true;
		symbol=p->id;
	}
}

template<Symbol_Str... symbols>
Symbol_Set<symbols...>::~Symbol_Set()
{
	if(Base::is_matched)
		Base::compiler->unmatch_symbol();
}

template<Symbol_Str... symbols>
void Symbol_Set<symbols...>::print_ast(u2 dep,std::wostream&o)
{
	Base::print_tree(dep,o);
	o<<L"keyword: "<<::Cscript::symbol_table[symbol]<<'\n';
}
