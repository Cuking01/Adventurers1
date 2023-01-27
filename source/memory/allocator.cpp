#pragma once


#include<atomic>

namespace Mem
{

struct Source_T{};
struct Thread_Safe_T{};

//根据是否线程安全选择atomic还是非atomic
template<typename T,typename U>
struct TS_helper{typedef U Type;};
template<typename U>
struct TS_helper<Thread_Safe_T,U>{typedef std::atomic<U> Type;};

template<typename TS,typename SA>
struct Allocator<Source_T,TS,SA>
{
	void*alloc(u3 sz){return Resource::alloc(sz);}
	void free(void*p){Resource::free(p);}
};

//根内存分配器类型与根内存分配器
RA ra;

template<typename T,typename TS,typename SA>
struct Allocator
{
	typedef T value_type;
	typedef u3 size_type;
	typedef s3 difference_type;
	typedef std::true_type propagate_on_container_move_assignment;
	typedef std::true_type propagate_on_container_copy_assignment;

	SA*source_allocator;
	TS_helper<TS,u3>::Type in_use;

	Allocator(SA&sa) noexcept :source_allocator(&sa),in_use(0){}
	Allocator(const Allocator& o):source_allocator(o.source_allocator),in_use(0){}
	Allocator(Allocator&& o):source_allocator(o.source_allocator),in_use(o.in_use){o.in_use=0;}
	Allocator& operator=(const Allocator& o)
	{
		//if(in_use)Warning("fuzhi:xie lou!%llu\n",in_use);
		source_allocator=o.source_allocator;
		in_use=0;
	}
	Allocator& operator=(Allocator&& o)
	{
		//if(in_use)Warning("fuzhi:xie lou!%llu\n",in_use);
		source_allocator=o.source_allocator;
		in_use=o.in_use;
		o.in_use=0;
	}
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

	T* allocate(u3 n)
	{
		void*p=alloc(n*sizeof(T));
		return (T*)((char*)p+al);
	}

	T* allocate_at_least(u3 n)
	{
		return allocate(n);
	}

	void deallocate(T*p,u3 n)
	{
		free((void*)((char*)p-al));
	}
};


};