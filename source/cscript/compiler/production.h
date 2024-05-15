#pragma once

template<typename Production_Derived>
struct Production;

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
};
