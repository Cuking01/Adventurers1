#pragma once

struct State_A
{
	Group_A group_a;
	State_A(Mem::SA&sa):
		group_a(sa)
	{}
};

struct State
{
	Group group[2];
	s2 time;
	State(const Player_Config::Group&ga,const Player_Config::Group&gb,State_A&a):
		group
		{
			{*this,0,ga,a.group_a},
			{*this,1,gb,a.group_a}
		}
	{}

	void init()
	{

	}
};
