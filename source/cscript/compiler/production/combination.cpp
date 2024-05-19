#pragma once


template<typename... Items>
template<std::size_t... I>
void Combination<Items...>::print_ast_impl(u2 dep,std::wostream&o,std::index_sequence<I...>)
{
	((get<I>().print_ast(dep,o)),...);
}

template<typename... Items>
void Combination<Items...>::print_ast(u2 dep,std::wostream&o)
{
	print_ast_impl(dep,o,std::make_index_sequence<sizeof...(Items)>());
}
