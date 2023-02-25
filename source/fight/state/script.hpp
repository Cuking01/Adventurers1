#pragma once

struct Skill_ID
{
    s1 pos;
    s2 id;
    Arg_t_6 arg;
    s2 check()
    {
        return pos>=0&&pos<5&&id>=0&&id<8;
    }
};

struct Script
{
    State&state;
    s1 gid;

    //暂定实现，测试使用---

    Arg_t_7 st;
    s2 (*fun_init)(State&state,s1 gid,Arg_t_7&st);
    s2 (*fun_act)(State&state,s1 gid,Arg_t_7&st,Skill_ID&skill_id);

    //---暂定实现，测试使用



    Script(State&state,s1 gid,[[maybe_unused]]const Player_Config::Script&script);

    s2 init();
    s2 act();

};
