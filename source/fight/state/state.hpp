#pragma once

struct State_A
{
	Group_A group_a;
	Damage_A damage_a;
	State_A(Mem::SA&sa);
};

struct Resource
{
	u2 count;
	std::mt19937_64 rnd;
	Damage_A&damage_a;

	Resource(u3 seed,Damage_A&damage_a);
};

struct State:Resource
{
	State_A&a;
	Group group[2];
	s2 time;

	State(const Player_Config::Group&ga,const Player_Config::Group&gb,u3 seed,State_A&a);

	void init();

	Group& operator[](s1 gid);
	Hero& operator[](Hid hid);
	Hero& hero(Hid hid);
	u2 gen_bool(f3 p);
	s2 check_win();

	//0,1表示对应队伍获胜，2表示平局.
	s2 start();
};
