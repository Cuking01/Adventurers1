#pragma once

template<typename... Items>
struct Combination:Production<Combination<Items...>>
{
	std::tuple<typename Production<Items>::Handler...> items;
	using Production<Combination<Items...>>::is_matched;

	void construct(Compiler&compiler,typename Production<Items>::Handler... tmps)
	{
		is_matched=multi_match(compiler,tmps...);
		this->items=std::tuple<typename Production<Items>::Handler...>{std::move(tmps)...};
	}

	Combination(Compiler&compiler):Production<Combination<Items...>>(compiler)
	{
		construct(compiler,typename Production<Items>::Handler{}...);
	}

	template<u2 idx>
	auto& get()
	{
		return *std::get<idx>(items);
	}

	template<std::size_t... I>
	void destruct(std::index_sequence<I...>)
	{
		static constexpr auto sz=sizeof...(I);
		(std::get<sz-1-I>(items).destroy(),...);
	}

	~Combination()
	{
		destruct(std::make_index_sequence<sizeof...(Items)>());
	}

	void print_ast(u2 dep,std::wostream&o)
	{
		//((print_tree(dep,o),Items->print_ast(dep,o)),...);
	}
};