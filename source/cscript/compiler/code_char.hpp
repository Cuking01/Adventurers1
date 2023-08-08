#pragma once

struct Code_Char_Reader
{
	const Code_Char*begin;
	const Code_Char*end;
	Compiler*compiler;

	Code_Char_Reader(const Code_Char*begin,const Code_Char* end,Compiler&compiler) noexcept;

	s2 empty() const noexcept;

	wchar_t operator()();

};

//记录位置信息的特殊字符类型
struct Code_Char
{
	wchar_t c;
	s2 line;
	s2 col;

	operator wchar_t () const noexcept;
};

