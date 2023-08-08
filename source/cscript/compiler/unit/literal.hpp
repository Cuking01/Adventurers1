#pragma once

enum class Literal_T:u2
{
	Integer,
	Float,
	String,
	Char
};

enum class String_T:u2
{
	Wstring,
	String
};

enum class Char_T:u2
{
	Wchar,
	Char
};

enum class Integer_T:u2
{
	Int16,Int32,Int64,
	Uint16,Uint32,Uint64
};

enum class Float_T:u2
{
	F32,F64
};

struct Literal:Unit
{
	Literal_T type;
	Literal(Literal_T type,s2 line,s2 col) noexcept;
};

struct String_Literal:Literal
{
	String_T type;
	u0*p;
	s2 len;
	String_Literal(const Code_Char* begin,const Code_Char* end,Compiler&compiler);
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
};

struct Integer_Literal:Literal
{
	Integer_T type;
	u3 x;
	Integer_Literal(const Code_Char* begin,const Code_Char* end,Compiler&compiler);
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
};
