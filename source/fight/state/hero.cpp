#pragma once

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

	Sp_State(Attribute_A&a):
		眩晕(a),沉默(a),致盲(a),潜行(a),嘲讽(a),重伤(a),免疫(a),霸体(a)
	{}
};

struct Hero:Attribute_Table,Sp_State
{
	s2 alive;
	s2 level;
	f3 HP,MP,AP;
	Skill skill[5];
	Equipment equipment[3];

	Hero(State&state,Hid hid,const Player_Config::Hero&hero,Attribute_A&a):
		Attribute_Table(hero,a),
		Sp_State(a),
		alive(1),
		level(hero.level),
		skill
		{
			{state,hid,Base_Config::hero[hero.id].skill[0],hero.skill[0].level,a},
			{state,hid,Base_Config::hero[hero.id].skill[1],hero.skill[1].level,a},
			{state,hid,Base_Config::hero[hero.id].skill[2],hero.skill[2].level,a},
			{state,hid,Base_Config::hero[hero.id].skill[3],hero.skill[3].level,a},
			{state,hid,Base_Config::hero[hero.id].skill[4],hero.skill[4].level,a},
		},
		equipment
		{
			{state,hid,hero.equipment[0],a},
			{state,hid,hero.equipment[1],a},
			{state,hid,hero.equipment[2],a},
		}
	{}

	void init()
	{

		HP=HP_lim();
		MP=MP_init();
		AP=AP_init();
	}
};
