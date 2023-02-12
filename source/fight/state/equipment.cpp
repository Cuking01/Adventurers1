#pragma once

struct Equipment:Skill
{
	Equipment(State&state,Hid hid,const Player_Config::Equipment &equipment,Attribute_A&a):
		Skill(state,hid,Base_Config::equipment[equipment.id].skill,equipment.level,a)
	{}
};
