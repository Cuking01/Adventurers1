#pragma once

struct Literal:Production<Literal>
{
	::Cscript::Literal* literal;
	Literal(Compiler&compiler);
	~Literal();
};


