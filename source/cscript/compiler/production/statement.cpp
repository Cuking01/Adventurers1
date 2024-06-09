#pragma once

void Stat::analyze()
{
	handler->get<1>().dispatch_call
	(
		[](Compound_Stat&stat){stat.analyze();},
		[](Exp_Stat&stat){stat.analyze();},
		[](Select_Stat&stat){stat.analyze();},
		[](Loop_Stat&stat){stat.analyze();},
		[](Jump_Stat&stat){stat.analyze();},
		[](auto&){}
	);
}

void Compound_Stat::analyze()
{
	compiler->dep_inc();

	handler->get<1>().for_each([](auto&t)
	{
		t.dispatch_call
		(
			[](auto&t){t.template get<0>().analyze();},
			[](auto&t){t.analyze();}
		);
	});

	compiler->dep_dec();
}

void Exp_Stat::analyze()
{
	handler->get<0>().analyze();
}

void Select_Stat::analyze()
{
	handler->dispatch_call
	(
		[](auto&t1)
		{
			t1.template get<0>().template get<2>().analyze();
			t1.template get<0>().template get<4>().analyze();
			t1.template get<1>().try_run([](ELSE&e){e.get<1>().analyze();});
		},
		[](auto&){}
	);
}

void Jump_Stat::analyze()
{
	handler->dispatch_call
	(
		[](auto&){},
		[](auto&){},
		[](auto&t){t.template get<1>().analyze();},
		[](auto&){}
	);
}
