#pragma once

template<typename T,u3 bs>
struct Pool
{
    static_assert(bs>0);
    union Node
    {
        T obj;
        Node*next;
    };
    struct Block
    {
        Node node[bs];
        Block*next;
    };
    using SA=Mem::SA;

    SA* source_allocator;
    Block*block_list;
    Node*node_list;

    Pool(SA&sa);
    ~Pool();
    void alloc();

    T* allocate();

    void deallocate(T*p);

    template<typename... Arg>
    T*operator()(Arg&&... arg);

    void operator<<(T*p);
};
