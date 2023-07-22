#pragma once

template<s2 N>
struct Symbol_Str
{
    char s[N];
    constexpr Symbol_Str(const char (&str)[N]);
    constexpr s2 operator==(const char*b) const;
};

template<Symbol_Str symbol>
consteval s2 symbol_map_helper();

template<Symbol_Str symbol>
consteval s2 symbol_map();

template<Symbol_Str symbol_str>
constexpr s2 symbol=symbol_map<symbol_str>();



