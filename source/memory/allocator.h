#pragma once

namespace Mem
{
	struct Source_T;
	struct Thread_Safe_T;

	//类型，源分配器类型,线程安全标志
	template<typename T,typename SA,typename TS=void>
	struct Allocator;

	typedef Allocator<Source_T,Source_T,Thread_Safe_T> RA;

	extern RA ra;

};
