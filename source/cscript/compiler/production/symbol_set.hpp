#pragma once

template<Symbol_Str... symbols>
struct Symbol_Set:Production<Symbol_Set<symbols...>>
{
	s2 symbol;
	Symbol_Set(Compiler&compiler);

	~Symbol_Set();
};

