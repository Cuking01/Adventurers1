#pragma once

//一般内存分配器，线程安全版本，无法用于STL容器

template<typename T,typename SA>
struct Allocator<T,SA,Thread_Safe_T>
{
	typedef SA source_type;
	static constexpr s2 thread_safe=1;
	static_assert(SA::thread_safe,"线程安全版本的内存分配器其源分配器也必须线程安全");

	SA*source_allocator;
	std::atomic<u3> in_use;

	char ____[64];  //防伪共享

	Allocator(SA&sa) noexcept :source_allocator(&sa),in_use(0){}
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

	//析构并释放
	void operator<<(T*p)
	{
		u3 n=*(u3*)((char*)p-al);
		for(u3 i=0;i<n;i+=sizeof(T))
			((T*)((char*)p+i))->~T();
		deallocate(p);
	}
};
