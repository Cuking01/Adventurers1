#pragma once

enum class Float_T:u2
{
	F32,F64
};

struct Float_Literal:Literal
{
	Float_T type;
	union
	{
		f3 f64;
		f2 f32;
	};
	Float_Literal(const Code_Char* begin,const Code_Char* end,Compiler&compiler);
	virtual std::wstring what(const Compiler&compiler) const;
};
