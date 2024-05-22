#pragma once

Declaration::Declaration(Compiler&compiler):Production(compiler)
{
	for(s2 i=0;i<3;i++)
		try_match(i);

	if(!type)return;

	declarators=Declarators::match(compiler);

	if(!declarators)return;

	is_matched=true;
}

void Declaration::try_match(s2 order)
{
	try_flag[order]=-1;
	if(!storage_spec)
		if(storage_spec=Storage_Spec::match(compiler))
		{
			try_flag[order]=0;
			return;
		}
	if(!type_qualifier)
		if(type_qualifier=Type_Qualifier::match(compiler))
		{
			try_flag[order]=1;
			return;
		}
	if(!type)
		if(type=Type::match(compiler))
		{
			try_flag[order]=2;
			return;
		} 
}

void Declaration::try_unmatch(s2 order)
{
	s2 flag=try_flag[order];
	if(flag==0)storage_spec.destroy();
	if(flag==1)type_qualifier.destroy();
	if(flag==2)type.destroy();
}

Declaration::~Declaration()
{
	declarators.destroy();
	for(s2 i=3;i--;)
		try_unmatch(i);
}

void Declaration::try_print_ast(u2 dep,std::wostream&o,s2 order)
{
	s2 flag=try_flag[order];
	if(flag==0)storage_spec->print_ast(dep+1,o);
	if(flag==1)type_qualifier->print_ast(dep+1,o);
	if(flag==2)type->print_ast(dep+1,o);
}

void Declaration::print_ast(u2 dep,std::wostream&o)
{
	print_tree(dep,o);
	o<<name<<'\n';
	for(s2 i=0;i<3;i++)
		try_print_ast(dep,o,i);
	declarators->print_ast(dep+1,o);
}
