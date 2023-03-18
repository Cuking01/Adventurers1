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
        //0非buff,1正面,2负面,3中性（非正非负）
        u0 正负面=0;

        //0弱驱散，1中驱散，2强驱散，3不可驱散
        u0 驱散等级=3;

        struct Initer
        {
            u0 val;
            void operator()(Tag&tag)=delete;
        };

        struct 正负面_t:Initer
        {
            void operator()(Tag&tag){tag.正负面=val;}
        };
        struct 驱散等级_t:Initer
        {
            void operator()(Tag&tag){tag.驱散等级=val;}
        };

        s2 operator()(正负面_t x){return 正负面==x.val;}
        s2 operator()(驱散等级_t x){return 驱散等级==x.val;}

        static constexpr 正负面_t 非buff{0u},正面{1u},负面{2u},中性{3u};
        static constexpr 驱散等级_t 弱驱散{0u},中驱散{1u},强驱散{2u},不可驱散{3u};

        template<typename... Initers>
        Tag(Initers... initers)
        {
            static_assert((std::is_base_of_v<Initer,Initers>&&...));
            ((initers(*this)),...);
        }
    };

    Arg_t_5 st={};
    Tag tag;
    Hid hid=Hid();
    const wchar_t*name=nullptr;
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

struct Skill_Handler:Buff_Base
{
    s2 (*fun)(State&,Hid,s2,const Arg_t_6&,const Arg_t_5&);
    s2 operator()(State&state,Hid hid,s2 sid,const Arg_t_6&arg);
};

struct Timed_Val_Buff:Buff_Base
{
    State&state;
    Timed_Val_Buff();
    Timed_Val_Buff(State&state,Buff_Base base,s2 t,s2 max_x);

    void add(s2 x);
    void cls(BT::驱散等级_t 驱散等级);

    s2& operator()() noexcept;
};
