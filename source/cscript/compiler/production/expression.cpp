#pragma once

void Function::analyze()
{
	auto&arg_list=handler->get<2>();
	arg_list.try_run([](Arg_List&arg_list)
	{
		arg_list.get<0>().for_each([](auto&t)
		{
			t.template get<0>().analyze();
		});
		arg_list.get<1>().analyze();
	});

	handler->get<4>().analyze();
}


void Expk<0>::analyze()
{
	handler->dispatch_call
	(
		[this](T1&t1){puts("*1*");t1.analyze();this->type=t1.t;},
		[this](T2&t2){puts("*2*");t2.analyze();auto*var_info=compiler->get_variable(t2.id);if(var_info)this->type=var_info->type;else puts("error"),compiler->report_error(L"undefined variable.");},
		[this](T3&t3){puts("*3*");t3.get<1>().analyze();this->type=t3.get<1>().type;},
		[this](T4&t4){puts("*4*");t4.analyze();this->type=1;}
	);

	printf("debug:%s %u\n",(const char*)name,this->type);
}

void Expk<1>::analyze()
{
	handler->get<0>().analyze();
	this->type=handler->get<0>().type;
	handler->get<1>().for_each
	(
		[this](auto&t)
		{
			t.dispatch_call
			(
				[](auto&){},
				[](auto&){},
				[this](auto&t)
				{
					this->type=4;
					auto&args=t.template get<1>();
					args.try_run(
						[](auto&args)
						{
							args.template get<0>().analyze();
							args.template get<1>().for_each([](auto&t)
							{
								t.template get<1>().analyze();
							});
						}
					);
				},
				[this](auto&t){t.template get<1>().analyze();this->type=compiler->type_tree.get_father(this->type);},
				[](auto&){},
				[](auto&){}
			);
		}
	);

	printf("debug:%s %u\n",(const char*)name,this->type);
}

void Exp::print_ast(u2 dep,std::wostream&o)
{
	print_tree(dep,o);
	o<<name<<L" type "<<compiler->type_tree.get_type_name(type)<<'\n';
	handler->print_ast(dep+1,o);
}

