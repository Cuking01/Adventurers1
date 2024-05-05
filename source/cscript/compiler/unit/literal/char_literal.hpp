#pragma once

enum class Char_T:u2
{
	Wchar,
	Char
};

struct Char_Literal:Literal
{
	Char_T type;
	union
	{
		char c;
		wchar_t wc;
	};
	Char_Literal(const Code_Char* begin,const Code_Char* end,Compiler&compiler);
	virtual std::wstring what(const Compiler&compiler) const;
};


