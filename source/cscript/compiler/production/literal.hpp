#pragma once

struct Literal:Production<Literal>
{
	::Cscript::Literal* literal;
	u2 t;
	Literal(Compiler&compiler);
	~Literal();
	void analyze();
	void print_ast(u2 dep,std::wostream&o);
};


