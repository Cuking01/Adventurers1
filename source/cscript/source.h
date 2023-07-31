#pragma once

constexpr s2 max_code_length=65536;
constexpr s2 max_mem_size=1<<20;//1MiB
/*
	内存结构，总共1MiB，从小到大为：
	1KiB保留区，禁止用户读写
	不定长代码区
	不定长常量区
	不定长全局（静态）区
	不定长自由区（堆区）
	64KiB栈区

*/


enum class Unit_T:u2;
enum class Literal_T:u2;
enum class String_T:u2;
enum class Char_T:u2;
enum class Integer_T:u2;
enum class Float_T:u2;
enum class Word_T:u2;

struct Unit;
struct Symbol;
struct Literal;
struct String_Literal;
struct Char_Literal;
struct Integer_Literal;
struct Float_Literal;
struct Word;

struct Code_Char_Reader;
struct Code_Char;
struct Mem_Seg;
struct Compiler_A;
struct Compiler;
