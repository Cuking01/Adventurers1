#pragma once


struct Script
{
	State&state;
	const s1 gid;

	Script(State&state,s1 gid,[[maybe_unused]]const Player_Config::Script&script):
		state(state),
		gid(gid)
	{}

	void init()
	{

	}
};
