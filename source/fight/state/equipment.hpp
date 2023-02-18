#pragma once

struct Equipment_A
{
    Skill_A skill_a;
    Equipment_A(Mem::SA&sa);
};

struct Equipment:Skill
{
    Equipment(State&state,Hid hid,const Player_Config::Equipment &equipment,Equipment_A&a);
    void init();
    
};
