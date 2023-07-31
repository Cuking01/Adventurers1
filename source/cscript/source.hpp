#pragma once

enum class Unit_T:u2
{
	Symbol,      //各种特殊符号，括号，逗号，运算符等
	Literal,     //字面量(字符串，字符，浮点数，整数)
	Word   //标识符(关键字，类型名，变量名，函数名，结构体名，跳转标签名)
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

enum class Word_T:u2
{
	Key,
	Indentifer
};

struct Code_Char_Reader
{
	const Code_Char*begin;
	const Code_Char*end;

	Code_Char_Reader(const Code_Char*begin,const Code_Char* end) noexcept;

	s2 empty() const noexcept;

	wchar_t operator()();

};

struct Unit
{
	Unit_T type;
	s2 line;
	s2 col;
	Unit(Unit_T type,s2 line,s2 col) noexcept;
};

struct Symbol:Unit
{
	s2 x;        //存储具体符号
	Symbol(const Code_Char*begin,const Code_Char* end);
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
	String_Literal(const Code_Char* begin,const Code_Char* end,Mem_Seg& mem_const);
};

struct Char_Literal:Literal
{
	Char_T type;
	union
	{
		char c;
		wchar_t wc;
	};
	Char_Literal(const Code_Char* begin,const Code_Char* end);
};

struct Integer_Literal:Literal
{
	Integer_T type;
	union
	{
		u3 u;
		s3 s;
	};
	Integer_Literal(const Code_Char* begin,const Code_Char* end);
};

struct Float_Literal:Literal
{
	Float_T type;
	union Data
	{
		f3 df;
		f2 f;
	}x;
	Float_Literal(const Code_Char* begin,const Code_Char* end);
};

struct Word:Unit
{
	Word_T type;
	s2 x;
	Word(const Code_Char* begin,const Code_Char* end);
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
	Mem::Pool<Symbol,32> symbol_a;
	Mem::Pool<Integer_Literal,32> integer_a;
	Mem::Pool<Float_Literal,32> float_a;
	Mem::Pool<String_Literal,32> string_a;
	Mem::Pool<Char_Literal,32> char_a;
	Mem::Pool<Word,32> word_a;
	Compiler_A(Mem::SA&sa);
};


s2 isdigit(wchar_t c);
s2 isodigit(wchar_t c);
s2 ishexdigit(wchar_t c);
s2 hextox(wchar_t c);


struct Mem_Seg
{
	alignas(std::max_align_t) u0 mem[max_mem_size];
	s2 p_mem;

	Mem_Seg() noexcept;

	template<s2 align>
	u0* alloc(s2 sz);
};

struct Compiler
{
	Compiler_A*a;
	std::vector<Code_Char> code;
	std::vector<Unit*> units;

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

