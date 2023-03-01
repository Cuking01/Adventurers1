#pragma once

struct Skill_A
{
    Attribute_A attribute_a;
    Skill_A(Mem::SA&sa);
};

struct Skill
{
    State&state;
    Hid hid;
    s2 level;
    Attribute AP_use,MP_use;
    Attribute CD_lim;
    Arg_t_7 st;

    f3 CD;

    struct Tag
    {
        u2 consumption_check:1;
        u2 sp_state_check:1;
        u2 target_check:1;
        u2 group_restrict:1;
        u2 target_group:1;
        u2 auto_consume:1;

        Tag(Base_Config::Skill::Tag tag);
    };
    Tag tag;

    void (*fun_init)(Skill&skill);
    s2   (*fun_check)(Skill&skill,const Arg_t_6&arg);
    void (*fun_use)(Skill&skill,const Arg_t_6&arg);
    
    Skill(State&state,Hid hid,const Base_Config::Skill&skill,s2 level,Skill_A&a);
    void init();
    
    void CD_recover();

    s2 consumption_check();
    s2 sp_state_check();
    s2 target_check(Hid target);
    void auto_consume();
    //0表示正常
    s2 check(const Arg_t_6&arg);
    void use(const Arg_t_6&arg);

};
