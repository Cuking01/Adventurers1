#pragma once

struct Skill
{
    const wchar_t* name;
    const wchar_t* description;
    Attribute_Table attribute_table;
    Attribute cd,cd_init;
    Attribute AP_use,MP_use;

    struct Tag
    {
        u2 consumption_check:1=1;  //默认消耗资源检查（MP AP cd）
        u2 sp_state_check:1=1;     //默认特殊状态检查（自身眩晕，致盲，致盲）
        u2 target_check:1=0;         //默认目标检查（参数值是否合法，是否符合阵营限制，是否被嘲讽保护）
        u2 group_restrict:1;       //默认目标检查-是否有阵营限制
        u2 target_group:1;         //默认目标检查-阵营限制
        u2 auto_consume:1=1;       //是否自动消耗AP MP，计算cd
        u2 cancel_潜行:1=1;        //自动取消潜行
    };
    Tag tag;

    void(*fun_init)([[maybe_unused]] ::Fight::State::Skill&skill);
    s2  (*fun_check)([[maybe_unused]] ::Fight::State::Skill&skill,[[maybe_unused]] const Arg_t_6&arg);
    void(*fun_use)([[maybe_unused]] ::Fight::State::Skill&skill,[[maybe_unused]] const Arg_t_6&arg);
    
};
