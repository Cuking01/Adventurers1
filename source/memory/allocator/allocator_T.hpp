#pragma once

//一般内存分配器，线程不安全版本，可以用于STL容器使用

template<typename T>
struct Allocator
{
    static constexpr s2 thread_safe=0;
    using SA=Allocator<Source_T>;

    SA*source_allocator;
    u3 in_use;

    Allocator(SA&sa) noexcept;
    Allocator(const Allocator& o)=delete;
    Allocator(Allocator&& o)=delete;
    Allocator& operator=(const Allocator& o)=delete;
    Allocator& operator=(Allocator&& o)=delete;
    ~Allocator();

    void*alloc(u3 sz);
    void free(void*p);
    T* allocate(u3 n);
    void deallocate(T*p);

    //析构并释放
    void operator<<(T*p);
};
