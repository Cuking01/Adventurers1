#pragma once

struct Sp_State_A
{
    Attribute_A attribute_a;
    Sp_State_A(Mem::SA&sa);
};

struct Sp_State
{
    Attribute 眩晕;
    Attribute 沉默;
    Attribute 致盲;
    Attribute 潜行;
    Attribute 嘲讽;
    Attribute 重伤;
    Attribute 免疫;
    Attribute 霸体;

    Sp_State(Sp_State_A&a);
};

struct Hero_A
{
    Attribute_Table_A attribute_table_a;
    Sp_State_A sp_state_a;
    Skill_A skill_a;
    Equipment_A equipment_a;
    Trigger_A<Event> trigger_event_a;
    Trigger_A<Damage_Handler> trigger_damage_handler_a;

    Hero_A(Mem::SA&sa);
};

struct Hero:Attribute_Table,Sp_State
{
    State&state;
    Hid hid;
    s2 alive;
    s2 level;
    f3 HP,MP,AP;
    Skill skill[5];
    Equipment equipment[3];
    Trigger<Damage_Handler> t_damaged;
    Trigger<Event> t_die;


    Hero(State&state,Hid hid,const Player_Config::Hero&hero,Hero_A&a);

    void init();
    auto die();
    void damaged(f3 x);
    void cause_damage(Hid to,f3 x,Damage::Tag tag);

    //0:正常释放,正数:技能内部检查不通过,负数:其他
    //id参数，0~4表示英雄技能，5~7表示装备技能
    s2 use_skill(s2 id,const Arg_t_6&arg);
};
