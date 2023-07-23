#pragma once

enum class Unit_T:u2
{
	symbol,      //各种特殊符号，括号，逗号，运算符等
	literal,     //字面量(字符串，字符，浮点数，整数)
	identifier   //标识符(关键字，类型名，变量名，函数名，结构体名，跳转标签名)
};

struct Unit
{
	s2 line;
	s2 col;

	virtual Unit_T type() const noexcept =0;

};

struct Symbol:Unit
{
	s2 x;        //存储具体符号
	Unit_T type() const noexcept;
};

struct Literal:Unit
{
	
	Unit_T type() const noexcept;
};

struct Identifier:Unit
{
	Unit_T type() const noexcept;
};

struct Compiler_A
{

};

struct Compiler
{
	Compiler_A*a;
	std::wstring code;
	std::vector<Unit*> units;

	Compiler(std::wstring code,Compiler_A&a);

	s2 compile_init();

	s2 extract();        //翻译阶段1，提取合法字符
	s2 merge_line();     //翻译阶段2，合并斜杠和换行符号为空

	s2 remove_note();    //去注释    翻译阶段3
	s2 split();          //拆分      翻译阶段3
	
	s2 pre_process();
	
	s2 compile();
};

