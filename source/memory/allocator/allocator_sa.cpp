#pragma once

//源内存分配器，支持内部内存分配与解分配，线程不安全版本

template<>
struct Allocator<Source_T>
{
	static constexpr s2 thread_safe=0;

	RA*source_allocator;
	std::atomic<u3> in_use;

	Allocator(RA&sa) noexcept :source_allocator(&sa),in_use(0){}
	Allocator(const Allocator& o)=delete;
	Allocator(Allocator&& o)=delete;
	Allocator& operator=(const Allocator& o)=delete;
	Allocator& operator=(Allocator&& o)=delete;
	~Allocator()
	{
		//if(in_use)Warning("xigou:xie lou!%llu\n",in_use);
	}
	void*alloc(u3 sz)
	{
		void*p=source_allocator->alloc(sz);
		in_use+=*(u3*)p;
		return p;
	}

	void free(void*p)
	{
		in_use-=*(u3*)p;
		source_allocator->free(p);
	}
};

