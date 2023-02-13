#pragma once

template<typename T>
struct Allocator_STL
{
	typedef T value_type;
	typedef u3 size_type;
	typedef s3 difference_type;
	typedef std::true_type propagate_on_container_move_assignment;
	typedef std::true_type propagate_on_container_copy_assignment;

	using SA=Allocator<T>;

	static constexpr s2 thread_safe=0;

	SA*source_allocator;
	Allocator_STL(SA&p): source_allocator(&p){}

	T* allocate(u3 n)
	{
		return source_allocator->allocate(n);
	}

	T* allocate_at_least(u3 n)
	{
		return allocate(n);
	}

	void deallocate(T*p,[[maybe_unused]]u3 n=0)
	{
		source_allocator->deallocate(p);
	}
};