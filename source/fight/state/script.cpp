#pragma once

Script::Script(State&state,s1 gid,[[maybe_unused]]const Player_Config::Script&script):
	state(state),
	gid(gid),
	st{},
	fun_init(script.fun_init),
	fun_act(script.fun_act)
{}

s2 Script::init()
{
	return 0;
}

s2 Script::act()
{
	Skill_ID sid;
	fun_act(state,gid,st,sid);
	if(sid.check())
	{
		[[maybe_unused]]s2 ret=state[gid][sid.pos].use_skill(sid.id,sid.arg);
		return ret;
	}
	else
	{
		return -1;
	}
}
