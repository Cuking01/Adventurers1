#pragma once

//根内存分配器

template<>
struct Allocator<Root_Source_T>
{
    typedef Source_T SA;
    static constexpr s2 thread_safe=1;

    void*alloc(u3 sz);
    void free(void*p);
};

//唯一实例
RA ra;
