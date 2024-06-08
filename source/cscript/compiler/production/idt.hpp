#pragma once

struct Idt:Production<Idt>
{
	u2 id;
	Idt(Compiler&compiler);
	~Idt();

	void print_ast(u2 dep,std::wostream&o);

	void analyze(){}
};

