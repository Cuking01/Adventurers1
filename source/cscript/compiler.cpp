#pragma once

#include "compiler/symbol.cpp"
#include "compiler/char_set.cpp"
#include "compiler/code_char.cpp"
#include "compiler/mem_seg.cpp"
#include "compiler/unit.cpp"
#include "compiler/production.cpp"

s2 hextox(wchar_t c)
{
	if(c>=L'0'&&c<=L'9')return c-L'0';
	if(c>=L'a'&&c<=L'f')return c-L'a'+10;
	return c-L'A'+10;
}

Compiler::Compiler(std::wstring code_,Mem::SA&sa):
	mtu_sa(sa),a(mtu_sa),mem_code(this),mem_const(this),mem_static(this)
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

s2 Compiler::add_identifier(std::wstring word)
{
	auto it=identifier_map.find(word);
	if(it==identifier_map.end())
	{
		s2 id=identifier_map.size()+1000;
		identifier_map[word]=id;
		identifier_name_table.push_back(word);
		return id;
	}
	return it->second;
}

std::wstring Compiler::identifier_name(s2 id) const
{
	return identifier_name_table.at(id-1000);
}

#include "compiler/lexer.cpp"
#include "compiler/parser.cpp"

s2 Compiler::compile() try
{
	lex();

	return 0;
}
catch(const std::exception&ep)
{
	//报大错
	return 0;
}

