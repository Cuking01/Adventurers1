#pragma once

struct Group_A
{
	Hero_A hero_a;
	Group_A(Mem::SA&sa);
};

struct Group
{
	Hero hero[5];
	Script script;

	Group(State&state,s1 gid,const Player_Config::Group&group,Group_A&a);
	void init();
	Hero& operator[](s1 pos) noexcept;
};
