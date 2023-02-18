#pragma once

constexpr Attribute::Attribute(f3 a,f3 b):a(a),b(b){}
constexpr Attribute::Attribute(){a=b=0.0;}
constexpr f3 Attribute::operator()(s2 level) const
{
	return a+b*level;
}
