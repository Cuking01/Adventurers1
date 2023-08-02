#pragma once

constexpr char symbol_table[][20]=
{
    "=",
    "+=",
    "-=",
    "*=",
    "/=",
    "%=",
    "&=",
    "|=",
    "^="
    "<<=",
    ">>=",
    "++",
    "--",
    "+",
    "-",
    "*",
    "/",
    "%",
    "~",
    "&",
    "|",
    "^",
    "<<",
    ">>",
    "!",
    "&&",
    "||",
    "==",
    "!=",
    "<",
    ">",
    "<=",
    ">=",
    "[",
    "]",
    "->",
    ".",
    "(",
    ")",
    ",",
    "?",
    ":",
    "{",
    "}",
    ";",
    "break",
    "case",
    "char",
    "const",
    "continue",
    "default",
    "do",
    "else",
    "float",
    "double",
    "for",
    "goto",
    "if",
    "int8",
    "int16",
    "int32",
    "int64",
    "return",
    "sizeof",
    "static",
    "struct",
    "switch",
    "typedef",
    "uint8",
    "uint16",
    "uint32",
    "uint64",
    "union",
    "void",
    "wchar",
    "while"
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
        for(const char*str:symbol_table)
        {
            s2 p=1;
            for(int j=0;str[j];j++)
            {
                auto&pt=node[p].next[(s2)str[j]];
                if(!pt)pt=cnt++;
                p=pt;
            }
            node[p].id=++id_cnt;
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

