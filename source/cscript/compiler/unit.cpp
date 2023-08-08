#pragma once

Unit::Unit(Unit_T type,s2 line,s2 col) noexcept
	:type(type),line(line),col(col)
{}

#include "unit/symbol.cpp"
#include "unit/literal.cpp"
#include "unit/word.cpp"
