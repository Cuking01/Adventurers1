#pragma once

struct Equipment_A
{
	Skill_A skill_a;
	Equipment_A(Mem::SA&sa):
		skill_a(sa)
	{}
};

struct Equipment:Skill
{
	Equipment(State&state,Hid hid,const Player_Config::Equipment &equipment,Equipment_A&a):
		Skill(state,hid,Base_Config::equipment[equipment.id].skill,equipment.level,a.skill_a)
	{}
};
