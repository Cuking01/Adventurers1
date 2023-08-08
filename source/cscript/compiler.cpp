#pragma once

#include "compiler/symbol.cpp"
#include "compiler/char_set.cpp"
#include "compiler/code_char.cpp"
#include "compiler/mem_seg.cpp"
#include "compiler/unit.cpp"

Compiler_A::Compiler_A(Mem::SA&sa):
	symbol_a(sa),
	integer_a(sa),
	float_a(sa),
	string_a(sa),
	char_a(sa),
	word_a(sa)
{}

Compiler::Compiler(std::wstring code_,Compiler_A&a):
	a(&a),mem_code(this),mem_const(this),mem_static(this)
{
	code.reserve(code_.length());
	s2 line=1;
	s2 col=1;
	for(wchar_t c:code_)
	{
		code.emplace_back(c,line,col);
		if(c==L'\n')line++,col=1;
		else col++;
	}
}

void Compiler::report_error(s2 line,s2 col,std::wstring err)
{
	error.push_back(std::format(L"{}{}{}",line,col,err));
}

void Compiler::report_error(std::wstring err)
{
	error.push_back(err);
}

s2 Compiler::compile_init()
{
	//清空各种辅助
	return 0;
}

#include "compiler/lexer.cpp"


s2 Compiler::compile() try
{
	//初始化
	compile_init();
	//提取合法字符
	extract();
	//去注释
	remove_note();
	//空白字符变空格
	empty_char();
	//拆分成单元
	split();
	return 0;
}
catch(const std::exception&ep)
{
	//报大错
	return 0;
}

