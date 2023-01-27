#pragma once

namespace Mem
{
	struct Source_T;
	struct Thread_Safe_T;

	//类型，线程安全标志，源分配器类型
	template<typename T,typename TS,typename SA>
	struct Allocator;

	typedef Allocator<Source_T,Thread_Safe_T,Source_T> RA;

	extern RA ra;

};
