#pragma once


template<s2 N>
constexpr Symbol_Str<N>::Symbol_Str(const char (&str)[N])
{
    for(s2 i=0;i<N;i++)
        s[i]=str[i];
}

template<s2 N>
constexpr s2 Symbol_Str<N>::operator==(const char*b) const
{
    const char*a=s;
    while(*a||*b)
    {
        if(*a!=*b)return 0;
        a++;b++;
    }
    return 1;
}



template<Symbol_Str symbol>
consteval s2 symbol_map_helper()
{
    constexpr s2 start=__COUNTER__;

    if constexpr(symbol=="+")return __COUNTER__-start;
    if constexpr(symbol=="-")return __COUNTER__-start;
    if constexpr(symbol=="*")return __COUNTER__-start;
    if constexpr(symbol=="/")return __COUNTER__-start;
    
    
    return 0;
}

template<Symbol_Str symbol>
consteval s2 symbol_map()
{
    static_assert(symbol_map_helper<symbol>()>0,"symbol don't exist.");
    return symbol_map_helper<symbol>();
}

Symbol_Trie_Status Symbol_Trie::init_status() const noexcept
{
    return {0,this};
}

Symbol_Trie_Status::operator bool() const noexcept
{
    return p!=0;
}


Symbol_Trie_Status Symbol_Trie_Status::operator()(wchar_t c) const noexcept
{
    s2 np;
    if(c>=0&&c<=127)
        np=trie->node[p].next[(s2)c];
    else
        np=0;
    return {np,trie};
}

s2 Symbol_Trie_Status::ok() const noexcept
{
    return trie->node[p].ok;
}
