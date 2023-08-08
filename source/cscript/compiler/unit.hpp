#pragma once

enum class Unit_T:u2
{
	Symbol,      //各种特殊符号，括号，逗号，运算符等
	Literal,     //字面量(字符串，字符，浮点数，整数)
	Word   //标识符(关键字，类型名，变量名，函数名，结构体名，跳转标签名)
};


struct Unit
{
	Unit_T type;
	s2 line;
	s2 col;
	Unit(Unit_T type,s2 line,s2 col) noexcept;
};

#include "unit/symbol.hpp"
#include "unit/literal.hpp"
#include "unit/word.hpp"


