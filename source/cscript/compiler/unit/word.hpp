#pragma once

enum class Word_T:u2
{
	Key,
	Identifier
};

struct Word:Unit
{
	Word_T type;
	s2 x;
	Word(const Code_Char* begin,const Code_Char* end,Compiler&compiler);
};


