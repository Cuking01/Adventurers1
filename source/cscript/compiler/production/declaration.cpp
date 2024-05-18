#pragma once

Type::Type(Compiler&compiler):Production(compiler)
{
	
	is_matched=multi_match(compiler,basic_type)||multi_match(compiler,named_type);
	if(basic_type)t=basic_type->symbol;
	if(named_type)t=named_type->id;
}

Declarator::Declarator(Compiler&compiler):Production(compiler)
{
	is_matched=handler=Me::match(compiler);
}

Declaration::Declaration(Compiler&compiler):Production(compiler)
{
	for(s2 i=0;i<3;i++)
		try_match(i);

	if(!type)return;

	declarators=Repeat_1<Declarator>::match(compiler);

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
