#pragma once

void Declarator::analyze(u2 type)
{
	
	// auto& pointers=handler->get<0>();
	// pointers.for_each([&type](Pointer&pointer){});
	auto& arrays=handler->get<2>();
	arrays.for_each_r([this,&type](Alpha&alpha)
	{
		alpha.dispatch_call
		(
			[](T4&t4){t4.get<1>().try_run([](auto&exp){exp.analyze();});},
			[](auto&){}
		);
		type=compiler->type_tree.get_child_by_array(type,0);
	});
	this->t=type;

	auto& beta=handler->get<1>();
	puts("Declator");
	beta.dispatch_call
	(
		[this,type](T1&t1)
		{
			t1.analyze();
			printf("add:%u %u\n",t1.id,type);
			compiler->add_variable(t1.id,{type});
		},
		[this,type](T2&t2)
		{
			puts("BB");
			t2.get<1>().analyze(type);
		}
	);
}

void Declarator::print_ast(u2 dep,std::wostream&o)
{
	print_tree(dep,o);
	auto&beta=handler->get<1>();
	o<<name;
	
	if(beta.is<T1>())
	{
		o<<std::format(L"  define a variable:{}",compiler->type_tree.get_type_name(t));
	}
	o<<'\n';
	handler->print_ast(dep+1,o);
}

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

void Declaration::analyze()
{
	type->analyze();
	declarators->get<0>().for_each([this](auto&item){item.template get<0>().template get<0>().analyze(type->t);});
	declarators->get<1>().get<0>().analyze(type->t);
}

void Function_Arg_Decl::analyze()
{
	handler->get<0>().dispatch_call
	(
		[this](T1&t1)
		{
			t1.get<0>().analyze();
			type=t1.get<0>().t;
		},
		[this](T2&t2)
		{
			t2.get<1>().analyze();
			type=t2.get<1>().t;
		},
		[this](T3&t3)
		{
			t3.analyze();
			type=t3.t;
		}
	);
	handler->get<1>().analyze(type);
}
