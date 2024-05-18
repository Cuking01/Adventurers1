#pragma once

struct Literal:Production<Literal>
{
	::Cscript::Literal* literal;
	Literal(Compiler&compiler);
	~Literal();
	void print_ast(u2 dep,std::wostream&o);
};


