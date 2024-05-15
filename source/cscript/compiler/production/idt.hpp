#pragma once

struct Idt:Production<Idt>
{
	u2 id;
	Idt(Compiler&compiler);
	~Idt();
};

