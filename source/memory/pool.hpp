#pragma once

template<typename T,u3 bs>
struct Pool
{
    static_assert(bs>0);
    
    Basic_Allocor<sizeof(T),bs> allocor;

    using SA=Mem::SA;

    

    Pool(SA&sa);

    T* allocate();

    void deallocate(T*p);

    template<typename... Args>
    T*operator()(Args&&... args);

    void operator<<(T*p);
};
