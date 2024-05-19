#pragma once

template<typename Item>
void Opt<Item>::print_ast(u2 dep,std::wostream&o)
{
	if(!item)return;
	item->print_ast(dep,o);
}
