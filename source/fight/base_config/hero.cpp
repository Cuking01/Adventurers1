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

	#define report_A使用了X(A,X) \
		state.report.write(fmt::format(L"[第{:4.1f}秒] {:s} 使用了 {:s}\n",skill.state.time*0.1,skill.state[A].report_name(),X));

	#define report_A于位置B使用了X(A,B,X) \
		state.report.write(fmt::format(L"[第{:4.1f}秒] {:s} 于位置 {:d} 使用了 {:s}\n",skill.state.time*0.1,skill.state[A].report_name(),B,X));

	#define report_X(X) \
		state.report.write(X);
	
	using ::Fight::State::Hid;

	#include "hero/0x011_test1.cpp"
	#include "hero/0x012_test2.cpp"
	#include "hero/0x101.cpp"	//王者铜
	#include "hero/0x102.cpp"	//冰棍


	#undef report_A对B使用了X
	#undef report_A使用了X
	#undef report_A于位置B使用了X
	#undef report_X

	return 0;
}

s2 hero_init_helper=hero_init();
