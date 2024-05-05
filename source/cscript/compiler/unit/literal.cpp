#pragma once

Unit_T2 literal_to_unit_t2(Literal_T literal)
{
	if(literal==Literal_T::Integer)
		return Unit_T2::Integer_Literal;
	if(literal==Literal_T::Float)
		return Unit_T2::Float_Literal;
	if(literal==Literal_T::String)
		return Unit_T2::String_Literal;
	if(literal==Literal_T::Char)
		return Unit_T2::Char_Literal;

}

Literal::Literal(Literal_T type,s2 line,s2 col) noexcept
	:Unit(Unit_T::Literal,literal_to_unit_t2(type),line,col,-1),type(type)
{}

#include "literal/string_literal.cpp"
#include "literal/char_literal.cpp"
#include "literal/integer_literal.cpp"
#include "literal/float_literal.cpp"
