#pragma once

struct Attribute
{
    f3 a,b;
    constexpr Attribute(f3 a,f3 b);
    constexpr Attribute();
    constexpr f3 operator()(s2 level) const;
};
