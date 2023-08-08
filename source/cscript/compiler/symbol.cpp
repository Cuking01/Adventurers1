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
    s2 p=1;
    char c;
    for(s2 i=0;c=symbol.s[i];i++)
    {
        p=symbol_dfa.node[p].next[(s2)c];
    }
    return symbol_dfa.node[p].id;
}

template<Symbol_Str symbol>
consteval s2 symbol_map()
{
    constexpr s2 ret=symbol_map_helper<symbol>();
    static_assert(ret>0,"symbol don't exist.");
    return ret;
}

Symbol_Trie_Status Symbol_Trie::init_status() const noexcept
{
    return {1,this};
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

s2 Symbol_Trie_Status::id() const noexcept
{
    return trie->node[p].id;
}
