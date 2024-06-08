#pragma once

template<typename Item>
struct Opt:Production<Opt<Item>>
{
	Production<Item>::Handler item;
	Opt(Compiler&compiler):Production<Opt<Item>>(compiler)
	{
		multi_match(compiler,item);
		Production<Opt<Item>>::is_matched=true;
	}

	template<typename Callback>
	void try_run(Callback&&callback)
	{
		if(item)
			callback(*item);
	}

	void print_ast(u2 dep,std::wostream&o);

};

