#pragma once

enum class Unit_T:u2
{
	Symbol,      //各种特殊符号，括号，逗号，运算符等
	Literal,     //字面量(字符串，字符，浮点数，整数)
	Identifier   //标识符(关键字，类型名，变量名，函数名，结构体名，跳转标签名)
};

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

struct Unit
{
	Unit_T type;
	s2 line;
	s2 col;

};

struct Symbol:Unit
{
	s2 x;        //存储具体符号
};

struct Literal:Unit
{
	Literal_T type;
};

struct String_Literal:Literal
{
	String_T type;
	union Data
	{
		std::string str;
		std::wstring wstr;
		Data(){}
		~Data(){}
	}x;

};

struct Char_Literal:Literal
{
	Char_T type;
	union Data
	{
		char c;
		wchar_t wc;
	}x;
};

struct Integer_Literal:Literal
{
	Integer_T type;
	union Data
	{
		u3 u;
		s3 s;
	}x;
};

struct Float_Literal:Literal
{
	Float_T type;
	union Data
	{
		f3 df;
		f2 f;
	}x;
};

struct Identifier:Unit
{

};


//记录位置信息的特殊字符类型
struct Code_Char
{
	wchar_t c;
	s2 line;
	s2 col;

	operator wchar_t () const noexcept;
};

struct Compiler_A
{

};

struct Compiler
{
	Compiler_A*a;
	std::vector<Code_Char> code;
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

