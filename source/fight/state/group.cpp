#pragma once

struct Group_A
{
	Hero_A hero_a;
	Group_A(Mem::SA&sa):
		hero_a(sa)
	{}
};

struct Group
{
	Hero hero[5];
	Script script;

	
	Group(State&state,s1 gid,const Player_Config::Group&group,Group_A&a):
		hero
		{
			{state,{gid,0},group.hero[0],a.hero_a},
			{state,{gid,1},group.hero[1],a.hero_a},
			{state,{gid,2},group.hero[2],a.hero_a},
			{state,{gid,3},group.hero[3],a.hero_a},
			{state,{gid,4},group.hero[4],a.hero_a}
		}
	{}

	Hero& operator[](s2 pos) noexcept
	{
		return hero[pos];
	}
};
