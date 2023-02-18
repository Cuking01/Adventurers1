#pragma once

Equipment_A::Equipment_A(Mem::SA&sa):
	skill_a(sa)
{}

Equipment::Equipment(State&state,Hid hid,const Player_Config::Equipment &equipment,Equipment_A&a):
	Skill(state,hid,Base_Config::equipment[equipment.id].skill,equipment.level,a.skill_a)
{}

void Equipment::init()
{
	Skill::init();
}
