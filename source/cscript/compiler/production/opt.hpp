#pragma once

template<typename Item>
struct Opt:Production<Opt<Item>>
{
	Item::Handler item;
	Opt(Compiler&compiler):Production<Opt<Item>>(compiler)
	{
		multi_match(compiler,item);
		Production<Opt<Item>>::is_matched=true;
	}

	void print_ast(u2 dep,std::wostream&o);

};

