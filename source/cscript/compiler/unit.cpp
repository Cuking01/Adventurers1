#pragma once

Unit::Unit(Unit_T type,Unit_T2 type2,s2 line,s2 col,s2 id) noexcept
	:type(type),type2(type2),line(line),col(col),id(id)
{}

#include "unit/symbol.cpp"
#include "unit/literal.cpp"
//#include "unit/word.cpp"
