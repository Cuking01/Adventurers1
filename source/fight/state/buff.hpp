#pragma once

struct Buff_Helper
{
    f3 add;
    f3 sub;
    f3 addp;
    f3 subp;
    Buff_Helper();
    f3 operator()(f3 x) const;
};

struct Buff_Base
{
    struct Tag
    {
        //pn正负面 positive or negative
        u2 pn:2;
        Tag();
    };
    Arg_t_5 st;
    Tag tag;
};


struct Buff:Buff_Base
{
    s2 (*fun)(Attribute&,Buff_Helper&,const Arg_t_5&);
    s2 operator()(Attribute&attr,Buff_Helper&bh);
};

struct Event:Buff_Base
{
    s2 (*fun)(State&state,Hid,const Arg_t_5&);
    s2 operator()(State&state,Hid hid);
};

struct Damage_Handler:Buff_Base
{
    s2 (*fun)(State&,Damage&,const Arg_t_5&);
    s2 operator()(State&state,Damage&damage);
};
