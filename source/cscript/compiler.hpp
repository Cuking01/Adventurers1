#pragma once

#include "compiler/char_set.hpp"
#include "compiler/symbol.hpp"
#include "compiler/code_char.hpp"
#include "compiler/mem_seg.hpp"
#include "compiler/unit.hpp"
#include "compiler/lexer.hpp"


struct Compiler_A
{
	Mem::Pool<Symbol,32> symbol_a;
	Mem::Pool<Integer_Literal,32> integer_a;
	Mem::Pool<Float_Literal,32> float_a;
	Mem::Pool<String_Literal,32> string_a;
	Mem::Pool<Char_Literal,32> char_a;
	Mem::Pool<Word,32> word_a;
	Compiler_A(Mem::SA&sa);
};

struct Compiler
{
	Compiler_A*a;
	std::vector<Code_Char> code;
	std::vector<Unit*> units;

	std::map<std::wstring,s2> identifier_map;
	std::vector<std::wstring> identifier_name;

	std::vector<std::wstring> error;
	void report_error(s2 line,s2 col,std::wstring err);
	void report_error(std::wstring err);

	Mem_Seg mem_code,mem_const,mem_static;



	Compiler(std::wstring code,Compiler_A&a);

	s2 compile_init();

	s2 extract();        //翻译阶段1，提取合法字符
	s2 merge_line();     //翻译阶段2，合并斜杠和换行符号为空

	s2 remove_note();    //去注释    翻译阶段3
	s2 empty_char();     //把所有空白字符变成空格 翻译阶段3 
	s2 split();          //拆分      翻译阶段3
	
	s2 pre_process();

	s2 compile();
};



