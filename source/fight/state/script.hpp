#pragma once


struct Script
{
    State&state;
    const s1 gid;

    //暂定实现，测试使用---

    Arg_t_7 st;
    s2 (*fun_init)(State&state,s1 gid,Arg_t_7&st);
    s2 (*fun_act)(State&state,s1 gid,Arg_t_7&st);

    //---暂定实现，测试使用



    Script(State&state,s1 gid,[[maybe_unused]]const Player_Config::Script&script);

    s2 init();
};
