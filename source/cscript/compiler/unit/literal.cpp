#pragma once

Literal::Literal(Literal_T type,s2 line,s2 col) noexcept
	:Unit(Unit_T::Literal,line,col,-1),type(type)
{}

#include "literal/string_literal.cpp"
#include "literal/char_literal.cpp"
#include "literal/integer_literal.cpp"
#include "literal/float_literal.cpp"
