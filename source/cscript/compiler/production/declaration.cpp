#pragma once

Storage_Spec::Storage_Spec(Compiler&compiler):Production(compiler)
{
	is_matched=compiler.match_symbol
		<"static","typedef">
	(
		[this](){type=Type::Static;},
		[this](){type=Type::Typedef;}
	);
}

Storage_Spec::~Storage_Spec()
{
	if(is_matched)
		compiler->unmatch_symbol();
}

Type_Qualifier::Type_Qualifier(Compiler&compiler):Production(compiler)
{
	is_matched=compiler.match_symbol<"const">([this](){type=Type::Const;});
}

Type_Qualifier::~Type_Qualifier()
{
	if(is_matched)
		compiler->unmatch_symbol();
}

Type::Type(Compiler&compiler):Production(compiler)
{
	is_matched=compiler.match_symbol<"uint8","uint16","uint32","uint64","int8","int16","int32","int64">
	(
		[](){},
		[](){},
		[](){},
		[](){},
		[](){},
		[](){},
		[](){},
		[](){}
	);
}

Type::~Type()
{
	if(is_matched)
		compiler->unmatch_symbol();
}

Declarator::Declarator(Compiler&compiler):Production(compiler)
{
	auto*p=compiler.match_idt();
	if(p)
	{
		is_matched=true;
		idt=p->id;
	}
}

Declarator::~Declarator()
{
	if(is_matched)
		compiler->unmatch_idt();
}

Declaration::Declaration(Compiler&compiler):Production(compiler)
{
	for(s2 i=0;i<3;i++)
		try_match(i);

	if(!type)return;

	declarator=Declarator::match(compiler);

	if(!declarator)return;

	idt=declarator->idt;
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
	for(s2 i=0;i<3;i++)
		try_unmatch(i);
}
