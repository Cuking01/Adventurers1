#pragma once

//源内存分配器，支持内部内存分配与解分配，线程不安全版本

template<>
struct Allocator<Source_T>
{
    static constexpr s2 thread_safe=1;

    RA*source_allocator;
    std::atomic<u3> in_use;

    Allocator(RA&sa) noexcept :source_allocator(&sa),in_use(0){}
    Allocator(const Allocator& o)=delete;
    Allocator(Allocator&& o)=delete;
    Allocator& operator=(const Allocator& o)=delete;
    Allocator& operator=(Allocator&& o)=delete;
    ~Allocator();
    void*alloc(u3 sz);
    void free(void*p);
};

