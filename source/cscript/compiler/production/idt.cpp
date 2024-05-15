#pragma once

Idt::Idt(Compiler&compiler):Production(compiler)
{
	auto p=compiler.match_idt();
	if(p)
	{
		is_matched=true;
		id=p->id;
	}
}

Idt::~Idt()
{
	if(is_matched)
		compiler->unmatch_idt();
}

