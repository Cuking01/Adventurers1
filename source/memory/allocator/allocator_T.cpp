#pragma once

//一般内存分配器，线程不安全版本，可以用于STL容器使用

template<typename T,typename SA,typename TS>
struct Allocator
{
	

	typedef SA source_type;
	static constexpr s2 thread_safe=0;

	SA*source_allocator;
	u3 in_use;

	Allocator(SA&sa) noexcept :source_allocator(&sa),in_use(0){}
	Allocator(const Allocator& o):source_allocator(o.source_allocator),in_use(0){}
	Allocator(Allocator&& o):source_allocator(o.source_allocator),in_use(o.in_use){o.in_use=0;}
	Allocator& operator=(const Allocator& o)
	{
		//if(in_use)Warning("fuzhi:xie lou!%llu\n",in_use);
		source_allocator=o.source_allocator;
		in_use=0;
		return *this;
	}
	Allocator& operator=(Allocator&& o)
	{
		//if(in_use)Warning("fuzhi:xie lou!%llu\n",in_use);
		source_allocator=o.source_allocator;
		in_use=o.in_use;
		o.in_use=0;
		return *this;
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
