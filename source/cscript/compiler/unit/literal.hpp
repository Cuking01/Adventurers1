#pragma once

enum class Literal_T:u2
{
	Integer,
	Float,
	String,
	Char
};


struct Literal:Unit
{
	Literal_T type;
	Literal(Literal_T type,s2 line,s2 col) noexcept;

	virtual std::wstring what(const Compiler&compiler) const =0;
};


#include "literal/string_literal.hpp"
#include "literal/char_literal.hpp"
#include "literal/integer_literal.hpp"
#include "literal/float_literal.hpp"
