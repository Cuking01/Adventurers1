#pragma once

struct Hid
{
    s1 gid;
    s1 pos;
    Hid(s2 x);
    Hid(s1 gid,s1 pos);
    Hid(const Arg_t_5&arg);
    Hid(const Arg_t_6&arg);
    Hid(const Arg_t_7&arg);
    explicit operator s2() const;
    s2 check() const;
};

