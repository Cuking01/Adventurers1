#pragma once

enum class Symbol_T:u2
{
	Key,
	Identifier
};

struct Symbol:Unit
{
	Symbol(const Code_Char*begin,const Code_Char* end,Compiler&compiler);
};

