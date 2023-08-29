#pragma once

Unit::Unit(Unit_T type,s2 line,s2 col,s2 id) noexcept
	:type(type),line(line),col(col),id(id)
{}

#include "unit/symbol.cpp"
#include "unit/literal.cpp"
//#include "unit/word.cpp"
