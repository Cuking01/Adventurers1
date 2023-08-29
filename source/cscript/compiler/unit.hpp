#pragma once

enum class Unit_T:u2
{
	Symbol,      //各种特殊符号，括号，逗号，运算符等,以及标识符(关键字，类型名，变量名，函数名，结构体名，跳转标签名)
	Literal      //字面量(字符串，字符，浮点数，整数)
};

enum class Unit_T2:u2
{
	Integer_Literal,
	Float_Literal,
	String_Literal,
	Char_Literal,
	Key,             //关键字和符号
	Identifier       //标识符 
};

struct Unit
{
	Unit_T type;
	Unit_T2 type2;
	s2 line;
	s2 col;
	s2 id;         //如果是标识符，则为大于等于1000的正整数，表示标识符的id，如果是-1，是字面量，否则如果是非负整数，是关键字和标点符号
	Unit(Unit_T type,s2 line,s2 col,s2 id) noexcept;
};

#include "unit/symbol.hpp"
#include "unit/literal.hpp"
//#include "unit/word.hpp"
