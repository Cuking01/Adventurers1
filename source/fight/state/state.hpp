#pragma once

struct State_A
{
	Group_A group_a;
	Damage_A damage_a;
	Event_Queue_A event_queue_a;
	Report_A report_a;
	Mem::Pool<Damage,31> damage_pool;
	State_A(Mem::SA&sa);
};

struct Resource
{
	u2 count;
	std::mt19937_64 rnd;

	Resource(u3 seed);
};

struct State:State_A,Resource
{
	Event_Queue event_queue;
	Report report;
	Group group[2];
	s2 time;

	State(const Player_Config::Group&ga,const Player_Config::Group&gb,u3 seed,Mem::SA&sa);

	void init();

	Group& operator[](s1 gid);
	Hero& operator[](Hid hid);
	Hero& hero(Hid hid);
	u2 gen_bool(f3 p);

	s2 check_win();

	//每帧的回复效果。
	void recover();

	//0,1表示对应队伍获胜，2表示平局.
	s2 start();
};
