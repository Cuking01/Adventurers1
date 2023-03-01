#pragma once

s2 Hero::id() const
{
	return this-hero;
}

s2 Hero::check() const
{
	return name!=nullptr;
}

Hero hero[0x300];



s2 hero_init()
{
	#define report_A对B使用了X(A,B,X) \
		state.report.write(fmt::format(L"[第{:4.1f}秒] {:s} 对 {:s} 使用了 {:s}\n",skill.state.time*0.1,skill.state[A].report_name(),skill.state[B].report_name(),X))

	#include "hero/!pattern.cpp"
	#include "hero/0x011_test1.cpp"
	#include "hero/0x012_test2.cpp"

	return 0;

	#undef report_A对B使用了X
}

s2 hero_init_helper=hero_init();
