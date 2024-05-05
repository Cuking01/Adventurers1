#pragma once

enum class Integer_T:u2
{
	Int16,Int32,Int64,
	Uint16,Uint32,Uint64
};

struct Integer_Literal:Literal
{
	Integer_T type;
	u3 x;
	Integer_Literal(const Code_Char* begin,const Code_Char* end,Compiler&compiler);
	virtual std::wstring what(const Compiler&compiler) const;
};
