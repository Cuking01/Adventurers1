#pragma once

template<u3 sz,u3 bs>
struct Basic_Allocor
{
    static_assert(sz>0&&bs>0);
    union Node
    {
        char mem[sz];
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

    Basic_Allocor(SA&sa) noexcept;
    ~Basic_Allocor();
    void alloc();

    void* allocate();

    void deallocate(void*p);

};
