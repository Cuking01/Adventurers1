#pragma once

constexpr wchar_t symbol_table[][20]=
{
    L"",   //仅占位，无实际作用
    L"=",
    L"+=",
    L"-=",
    L"*=",
    L"/=",
    L"%=",
    L"&=",
    L"|=",
    L"^="
    L"<<=",
    L">>=",
    L"++",
    L"--",
    L"+",
    L"-",
    L"*",
    L"/",
    L"%",
    L"~",
    L"&",
    L"|",
    L"^",
    L"<<",
    L">>",
    L"!",
    L"&&",
    L"||",
    L"==",
    L"!=",
    L"<",
    L">",
    L"<=",
    L">=",
    L"[",
    L"]",
    L"->",
    L".",
    L"(",
    L")",
    L",",
    L"?",
    L":",
    L"{",
    L"}",
    L";",
    L"break",
    L"case",
    L"char",
    L"const",
    L"continue",
    L"default",
    L"do",
    L"else",
    L"float",
    L"double",
    L"for",
    L"goto",
    L"if",
    L"int8",
    L"int16",
    L"int32",
    L"int64",
    L"return",
    L"sizeof",
    L"static",
    L"struct",
    L"switch",
    L"typedef",
    L"uint8",
    L"uint16",
    L"uint32",
    L"uint64",
    L"union",
    L"void",
    L"wchar",
    L"while"
};


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

struct Symbol_Trie
{
    struct Node
    {
        s2 id;
        s2 next[128];
    };
    Node node[600];
    s2 cnt;


    constexpr Symbol_Trie() noexcept
        :node{},cnt(2)
    {
        s2 id_cnt=0;
        for(const wchar_t*str:symbol_table)
        {
            s2 p=1;
            for(int j=0;str[j];j++)
            {
                auto&pt=node[p].next[(s2)str[j]];
                if(!pt)pt=cnt++;
                p=pt;
            }
            node[p].id=id_cnt++;
        }
    }

    Symbol_Trie_Status init_status() const noexcept;
};

constexpr Symbol_Trie symbol_dfa;

struct Symbol_Trie_Status
{
    s2 p;
    const Symbol_Trie*trie;

    operator bool() const noexcept;

    Symbol_Trie_Status operator()(wchar_t c) const noexcept;

    s2 id() const noexcept;
};


template<Symbol_Str symbol_str>
constexpr s2 symbol=symbol_map<symbol_str>();

