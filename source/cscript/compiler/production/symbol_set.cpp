#pragma once


template<Symbol_Str... symbols>
Symbol_Set<symbols...>::Symbol_Set(Compiler&compiler):Production<Symbol_Set<symbols...>>(compiler)
{
	auto*p=compiler.match_symbol<symbols...>();
	if(p)
	{
		Production<Symbol_Set<symbols...>>::is_matched=true;
		symbol=p->id;
	}
}

template<Symbol_Str... symbols>
Symbol_Set<symbols...>::~Symbol_Set()
{
	if(Production<Symbol_Set<symbols...>>::is_matched)
		Production<Symbol_Set<symbols...>>::compiler->unmatch_symbol();
}
