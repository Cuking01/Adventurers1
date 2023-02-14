#pragma once

struct State_A
{
	Group_A group_a;
	Damage_A damage_a;
	State_A(Mem::SA&sa):
		group_a(sa),
		damage_a(sa)
	{}
};

struct State
{
	State_A&a;
	Group group[2];
	s2 time;
	State(const Player_Config::Group&ga,const Player_Config::Group&gb,State_A&a):
		a(a),
		group
		{
			{*this,0,ga,a.group_a},
			{*this,1,gb,a.group_a}
		},
		time(0)
	{}

	void init()
	{
		for(s1 i=0;i<2;i++)
			group[i].init();
	}

	Group& operator[](s1 gid)
	{
		return group[gid];
	}
	Hero& operator[](Hid hid)
	{
		return group[hid.gid][hid.pos];
	}



};
