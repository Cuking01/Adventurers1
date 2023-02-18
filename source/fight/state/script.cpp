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

