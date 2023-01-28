#pragma once

//根内存分配器

template<>
struct Allocator<Source_T,Source_T,Thread_Safe_T>
{
	typedef Source_T source_type;
	static constexpr s2 thread_safe=1;

	void*alloc(u3 sz){return Resource::alloc(sz);}
	void free(void*p){Resource::free(p);}
};

//唯一实例
RA ra;
