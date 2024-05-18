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

void Idt::print_ast(u2 dep,std::wostream&o)
{
	print_tree(dep,o);
	o<<L"Identifier: "<<compiler->identifier_name(id)<<'\n';	
}

