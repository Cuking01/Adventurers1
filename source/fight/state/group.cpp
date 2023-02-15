#pragma once

Group_A::Group_A(Mem::SA&sa):
	hero_a(sa)
{}

Group::Group(State&state,s1 gid,const Player_Config::Group&group,Group_A&a):
	hero
	{
		{state,{gid,0},group.hero[0],a.hero_a},
		{state,{gid,1},group.hero[1],a.hero_a},
		{state,{gid,2},group.hero[2],a.hero_a},
		{state,{gid,3},group.hero[3],a.hero_a},
		{state,{gid,4},group.hero[4],a.hero_a}
	},
	script(state,gid,group.script)
{}

void Group::init()
{
	for(int i=0;i<5;i++)
		hero[i].init();
	
	//script.init();//script的初始化放到战前单独执行
}

Hero& Group::operator[](s1 pos) noexcept
{
	return hero[pos];
}
