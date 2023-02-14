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

	void cause_damage(Damage damage)
	{
		[[maybe_unused]] Hid from=damage.from;
		Hid to=damage.to;

		f3 val=damage.x();

		auto type=damage.tag.物理_魔法_真实;
		if(type==DT::物理)
		{
			damage.破甲.x=hero(to).P_res();
			val=val/(1+0.01*damage.破甲());
		}
		else if(type==DT::魔法)
		{
			damage.破魔.x=hero(to).M_res();
			val=val/(1+0.01*damage.破魔());
		}
		else
		{
			//真实伤害啥也不干
		}

		hero(to).damage(val);
		damage.addition(*this,damage);

	}

	void use_skill()
	{

	}

	s2 start()
	{
		for(time=0;time<1000;time++)
		{
			
			if(auto ret=check_win();~ret)
				return ret;
		}
		return 2;
	}

};
