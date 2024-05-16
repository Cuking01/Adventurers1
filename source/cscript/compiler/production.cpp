#pragma once


template<typename Production_Derived>
Production<Production_Derived>::Production(Compiler&compiler):compiler(&compiler),is_matched(false)
{
	cnt++;
	cnt_g++;
	fprintf(stderr,"%4u %4d %4d %s\n",compiler.unit_p,cnt_g,cnt,typeid(Production_Derived*).name());
}

namespace Productions
{
	#include"production/any.cpp"
	#include"production/repeat.cpp"
	#include"production/combination.cpp"
	#include"production/opt.cpp"
	#include"production/symbol_set.cpp"
	#include"production/idt.cpp"
	#include"production/literal.cpp"
	#include"production/declaration.cpp"
	#include"production/expression.cpp"
	#include"production/statement.cpp"
};

