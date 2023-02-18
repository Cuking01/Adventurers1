#pragma once

template<typename T>
struct Allocator_STL
{
    typedef T value_type;
    typedef u3 size_type;
    typedef s3 difference_type;
    typedef std::true_type propagate_on_container_move_assignment;
    typedef std::true_type propagate_on_container_copy_assignment;

    static constexpr s2 thread_safe=0;

    SA*source_allocator;
    u3 in_use;

    Allocator_STL(SA&p);
    T* allocate(u3 n);
    T* allocate_at_least(u3 n);
    void deallocate(T*p,[[maybe_unused]]u3 n=0);
};