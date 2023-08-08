#pragma once

struct Char_Set
{
    struct wc_flag_t{};
    static constexpr wc_flag_t wc_flag{};

    u4 set;
    s2 flag_wc;    //所有非ASCII字符
    constexpr Char_Set():set(0),flag_wc(0){}

    constexpr Char_Set(wc_flag_t):set(0),flag_wc(1){}

    constexpr Char_Set(char l,char r):set(0),flag_wc(0)
    {
        for(char c=l;c<=r;c++)
            set|=u4(1)<<c;
    }
    constexpr Char_Set(std::initializer_list<char> list):set(0),flag_wc(0)
    {
        for(char c:list)
            set|=u4(1)<<c;
    }

    constexpr s2 operator()(wchar_t c) const
    {
        if(c>=0&&c<=127)
            return set>>c&1;
        return flag_wc;
    }
};

constexpr Char_Set operator|(Char_Set a,Char_Set b)
{
    Char_Set ans;
    ans.set=a.set|b.set;
    ans.flag_wc=a.flag_wc|b.flag_wc;
    return ans;
}

constexpr Char_Set operator&(Char_Set a,Char_Set b)
{
    Char_Set ans;
    ans.set=a.set&b.set;
    ans.flag_wc=a.flag_wc&b.flag_wc;
    return ans;
}

constexpr Char_Set operator~(Char_Set a)
{
    Char_Set ans;
    ans.set=~a.set;
    ans.flag_wc=!a.flag_wc;
    return ans;
}

constexpr Char_Set punctuation{'_','{','}','[',']','#','(',')','<','>','%',':',';','.','?','*','+','-','/','^','&','|','~','!','=',',','\\','\"','\''};
constexpr Char_Set symbol_punctuation=punctuation&~Char_Set{'\\','\"','\''};

constexpr Char_Set bdigit('0','1');
constexpr Char_Set digit('0','9');
constexpr Char_Set odigit('0','7');
constexpr Char_Set hexdigit=digit|Char_Set('a','f')|Char_Set('A','F');

constexpr Char_Set lower_letter('a','z');
constexpr Char_Set capital_letter('A','Z');
constexpr Char_Set letter=lower_letter|capital_letter;

constexpr Char_Set other_char(Char_Set::wc_flag);
constexpr Char_Set word_char=letter|digit|other_char|Char_Set{'_'};

constexpr Char_Set blank{'\t','\v','\n','\r',' '};

constexpr Char_Set cscript_char_set=punctuation|digit|letter|blank;

