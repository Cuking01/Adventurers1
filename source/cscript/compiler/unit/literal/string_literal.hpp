#pragma once

enum class String_T:u2
{
	Wstring,
	String
};

struct String_Literal:Literal
{
	String_T type;
	u0*p;
	s2 len;
	String_Literal(const Code_Char* begin,const Code_Char* end,Compiler&compiler);

	virtual std::wstring what(const Compiler&compiler) const;
};
