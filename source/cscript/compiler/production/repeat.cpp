#pragma once

template<typename Item>
void Repeat<Item>::print_ast(u2 dep,std::wostream&o)
{
	for(auto&item:items)
		item->print_ast(dep,o);
}

template<typename Item>
void Repeat_1<Item>::print_ast(u2 dep,std::wostream&o)
{
	for(auto&item:items)
		item->print_ast(dep,o);
}
