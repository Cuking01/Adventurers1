#pragma once

template<typename T,typename SA>
struct Allocator_STL
{
	typedef T value_type;
	typedef u3 size_type;
	typedef s3 difference_type;
	typedef std::true_type propagate_on_container_move_assignment;
	typedef std::true_type propagate_on_container_copy_assignment;

	typedef Allocator<T,SA,void> source_type;
	static constexpr s2 thread_safe=0;

	Allocator<T,SA,void>*source_allocator;
	Allocator_STL(Allocator<T,SA,void>*p): source_allocator(p){}

	T* allocate(u3 n)
	{
		void*p=source_allocator->alloc(n*sizeof(T));
		return (T*)((char*)p+al);
	}

	T* allocate_at_least(u3 n)
	{
		return allocate(n);
	}

	void deallocate(T*p,u3 n)
	{
		source_allocator->free((void*)((char*)p-al));
	}
};