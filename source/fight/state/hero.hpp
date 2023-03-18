#pragma once

struct Sp_State_A
{
    Attribute_A attribute_a;
    Trigger_A<Event> trigger_a;
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
    Attribute 霸体;

    Sp_State(Sp_State_A&a);

    #define t_sp(name) Trigger<Event> t_##name;    //进入某状态时触发
    #define tq_sp(name) Trigger<Event> tq_##name;  //状态消失时触发
    PP_FOR_EACH(t_sp,眩晕,沉默,致盲,潜行,嘲讽,重伤,霸体)
    PP_FOR_EACH(tq_sp,眩晕,沉默,致盲,潜行,嘲讽,重伤,霸体)
    #undef t_sp
    #undef tq_sp
};

struct Hero_A
{
    Attribute_Table_A attribute_table_a;
    Sp_State_A sp_state_a;
    Skill_A skill_a;
    Equipment_A equipment_a;
    Trigger_A<Event> trigger_event_a;
    Trigger_A<Damage_Handler> trigger_damage_handler_a;
    Trigger_A<Skill_Handler> trigger_skill_handler_a;
    Damage_A damage_a;
    Timed_Val_Buff_Table_A timed_val_buff_table_a;
    Hero_A(Mem::SA&sa);
};

struct Hero:Attribute_Table,Sp_State
{
    State&state;
    Arg_t_7 st;
    s2 id;
    Hid hid;
    s2 alive;
    s2 level;
    f3 HP,MP,AP;
    Skill skill[5];
    Equipment equipment[3];
    Trigger<Damage_Handler> t_damage;
    Trigger<Damage_Handler> t_before_damaged;
    Trigger<Damage_Handler> t_damaged;
    Trigger<Skill_Handler> t_use_skill;
    Trigger<Event> t_die;
    Timed_Val_Buff_Table timed_val_buff_table;


    Hero(State&state,Hid hid,const Player_Config::Hero&hero,Hero_A&a);

    Hero(const Hero&)=delete;
    Hero& operator=(const Hero&)=delete;
    Hero& operator=(Hero&&)=delete;

    #define en_sp(name) u2 en_##name(s2 t,BT::驱散等级_t=BT::中驱散);
    #define cls_sp(name) void cls_##name(BT::驱散等级_t=BT::强驱散);
    #define del_sp(name) void del_##name(u2 id);
    

    PP_FOR_EACH(en_sp,眩晕,沉默,致盲,潜行,嘲讽,霸体)
    u2 en_重伤(s2 t,f3 p,BT::驱散等级_t=BT::中驱散);
    PP_FOR_EACH(cls_sp,眩晕,沉默,致盲,潜行,嘲讽,重伤,霸体)
    PP_FOR_EACH(del_sp,眩晕,沉默,致盲,潜行,嘲讽,重伤,霸体)
    
    #undef en_sp
    #undef cls_sp
    #undef del_sp

    void init();

    std::wstring report_name() const;

    //仅：对应值增加，并且判断是否超过上限
    void HP_add(f3 x);
    void MP_add(f3 x);
    void AP_add(f3 x);

    //每帧的自动回复
    void HP_recover(f3 x);
    void MP_recover(f3 x);
    void AP_recover(f3 x);
    void recover();

    s2 die();
    s2 damaged(Damage&damage);
    s2 healed();
    Damage& make_damage(Hid to,f3 x,Damage::Tag tag);
    s2 cause_damage(Hid to,f3 x,Damage::Tag tag);

    //0:正常释放,正数:技能内部检查不通过,负数:其他
    //id参数，0~4表示英雄技能，5~7表示装备技能
    s2 use_skill(s2 id,const Arg_t_6&arg);
};
