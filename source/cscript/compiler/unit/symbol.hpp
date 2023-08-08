#pragma once

struct Symbol:Unit
{
	s2 x;        //存储具体符号
	Symbol(const Code_Char*begin,const Code_Char* end,Compiler&compiler);
};

