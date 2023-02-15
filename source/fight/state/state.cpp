#pragma once

State_A::State_A(Mem::SA&sa):
	group_a(sa),
	damage_a(sa)
{}

struct Resource
{
	u2 count;
	std::mt19937_64 rnd;
	Damage_A&damage_a;

	Resource(u3 seed,Damage_A&damage_a):
		count(0),
		rnd(seed),
		damage_a(damage_a)
	{}
};

struct State:Resource
{
	State_A&a;
	Group group[2];
	s2 time;

	State(const Player_Config::Group&ga,const Player_Config::Group&gb,u3 seed,State_A&a):
		Resource(seed,a.damage_a),
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

	Group& operator[](s1 gid){return group[gid];}
	Hero& operator[](Hid hid){return group[hid.gid][hid.pos];}
	Hero& hero(Hid hid){return (*this)[hid];}

	s2 check_win()
	{
		s2 cnt[2]={0,0};
		for(s1 gid=0;gid<2;gid++)
			for(s1 pos=0;pos<5;pos++)
				cnt[gid]+=hero({gid,pos}).alive;
		//双方都有存活就是-1，继续战斗
		//如果一方存活则此方获胜并返回gid
		//双方均不存活则平手，返回2
		if(cnt[0]&&cnt[1])return -1;
		if(cnt[0])return 0;
		if(cnt[1])return 1;
		return 2;
	}

	// void cause_damage(Damage damage)
	// {
		

	// }

	//0,1表示对应队伍获胜，2表示平局.
	s2 start()
	{
		init();
		for(s1 gid=0;gid<2;gid++)
			if(auto ret=group[gid].script.init();ret)
				return gid^1;
		

		for(time=0;time<1000;time++)
		{
			


			if(auto ret=check_win();~ret)
				return ret;
		}
		return 2;
	}

};
