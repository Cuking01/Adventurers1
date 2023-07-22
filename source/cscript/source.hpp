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
	s2 pre_process();
	s2 split();
	s2 compile();
};

