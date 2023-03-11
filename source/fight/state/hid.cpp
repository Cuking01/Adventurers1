#pragma once
Hid::Hid():Hid(-1,-1)
{}
Hid::Hid(s2 x)
{
    *(s2*)this=x;
}
Hid::Hid(s1 gid,s1 pos):
    gid(gid),pos(pos)
{}
Hid::Hid(const Arg_t_5&arg):
    Hid(arg.SH0,arg.SH2)
{}
Hid::Hid(const Arg_t_6&arg):
    Hid(arg.SH0,arg.SH2)
{}
Hid::Hid(const Arg_t_7&arg):
    Hid(arg.SH0,arg.SH2)
{}

Hid::operator s2() const
{
    return *(int*)this;
}
s2 Hid::check() const
{
    return gid>=0&&gid<=1&&pos>=0&&pos<=4;
}

