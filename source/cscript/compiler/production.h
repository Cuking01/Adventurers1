#pragma once

template<typename Production_Derived>
struct Production;

template<u2 k>
struct Name_Str;

namespace Productions
{
	#include"production/any.h"
	#include"production/repeat.h"
	#include"production/combination.h"
	#include"production/opt.h"
	#include"production/symbol_set.h"
	#include"production/idt.h"
	#include"production/literal.h"
	#include"production/declaration.h"
	#include"production/expression.h"
	#include"production/statement.h"
	
};
