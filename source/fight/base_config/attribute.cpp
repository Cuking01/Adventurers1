#pragma once

struct Attribute
{
	f3 a,b;
	constexpr Attribute(f3 a,f3 b):a(a),b(b){}
	constexpr Attribute(){a=b=0.0;}
	constexpr f3 operator()(s2 level) const
	{
		return a+b*level;
	}
};