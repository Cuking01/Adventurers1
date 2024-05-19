#pragma once

template<typename... Items>
void Any<Items...>::print_ast(u2 dep,std::wostream&o)
{
	((is<Items>()&&(get<Items>().print_ast(dep,o),true))||...);
}
