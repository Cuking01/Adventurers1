#pragma once

State_A::State_A(Mem::SA&sa):
	group_a(sa),
	damage_a(sa),
	event_queue_a(sa),
	report_a(sa),
	damage_pool(sa)
{}

Resource::Resource(u3 seed):
	count(0),
	rnd(seed)
{}

State::State(const Player_Config::Group&ga,const Player_Config::Group&gb,u3 seed,Mem::SA&sa):
	State_A(sa),
	Resource(seed),
	event_queue(*this,event_queue_a),
	report(report_a),
	group
	{
		{*this,0,ga,group_a},
		{*this,1,gb,group_a}
	},
	time(0)
{}

void State::init()
{
	for(s1 i=0;i<2;i++)
		group[i].init();
}

Group& State::operator[](s1 gid){return group[gid];}
Hero& State::operator[](Hid hid){return group[hid.gid][hid.pos];}
Hero& State::hero(Hid hid){return (*this)[hid];}

u2 State::gen_bool(f3 p)
{
	return (rnd()&((1u<<31)-1))*(1.0/(1u<<31))<p;
}

s2 State::check_win()
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

//0,1表示对应队伍获胜，2表示平局.

void State::recover()
{
	for(s1 gid=0;gid<2;gid++)
		for(s1 pos=0;pos<5;pos++)
			hero({gid,pos}).recover();
}

void State::log_hero_state()
{
	report.write(fmt::format(L"<------------------------第{:2.1f}秒------------------------>\n\n",time*0.1));
	for(s1 gid=0;gid<2;gid++)
	{
		report.write(fmt::format(L"<------------------------队伍{:c}------------------------>\n\n",(wchar_t)('A'+gid)));

		for(s1 pos=0;pos<5;pos++)
		{
			report.write(fmt::format(
				L"{:s}: HP={:.2f}/{:.2f}  MP:{:.2f}/{:.2f}  AP:{:.2f}/{:.2f}\n",
				Base_Config::hero[hero({gid,pos}).id].name,
				hero({gid,pos}).HP,hero({gid,pos}).HP_lim(),
				hero({gid,pos}).MP,hero({gid,pos}).MP_lim(),
				hero({gid,pos}).AP,hero({gid,pos}).AP_lim()
			));
		}
		report.write(L"\n");
	}
}

s2 State::start()
{
	init();
	for(s1 gid=0;gid<2;gid++)
		if(auto ret=group[gid].script.init();ret)
			return gid^1;
	

	for(time=0;time<1000;time++)
	{
		recover();
		
		while(1)
		{
			s2 ret0=group[0].script.act();
			if(auto ret=check_win();~ret)
				return ret;

			s2 ret1=group[1].script.act();
			if(auto ret=check_win();~ret)
				return ret;

			//都没有正常释放技能则返回.
			if(ret0&&ret1)break;
		}

		event_queue.run(time);
		if(auto ret=check_win();~ret)
			return ret;

		if(time%50==0)
			log_hero_state();
	}
	return 2;
}
