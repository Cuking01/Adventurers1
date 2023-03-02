#pragma once

namespace Buff_Tag
{
    enum T1:u0{正面=1,负面=2};
    enum T2:u0{弱驱散,中驱散,强驱散,不可驱散};
};

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
        //1正面,2负面,0非正非负,3不合法
        u2 pn:2;
        u2 驱散等级:2;
    };
    Arg_t_5 st;
    Tag tag;
    Hid hid;
    const wchar_t*name;
};


struct Buff:Buff_Base
{
    s2 (*fun)(Attribute&,Buff_Helper&,const Arg_t_5&);
    s2 operator()(Attribute&attr,Buff_Helper&bh);
};

struct Event:Buff_Base
{
    s2 (*fun)(State&state,const Arg_t_5&);
    s2 operator()(State&state);
};

struct Damage_Handler:Buff_Base
{
    s2 (*fun)(State&,Damage&,const Arg_t_5&);
    s2 operator()(State&state,Damage&damage);
};
