#pragma once

template<typename T>
struct Set_Node
{
    const T ele;
    Set_Node*f,*l,*r;
    void rotate();
};

template<typename T>
struct Set
{
    using Node=Set_Node<T>;
    using A=Mem::Pool<Node,31>;
    A&allocator;
    Node*root;
    u3 sz;

    struct iterator
    {
        Node*t;
        iterator& operator++();
        int operator!=(iterator b) const;
        int operator==(iterator b) const;
        const T& operator*() const;
        const T* operator->() const;
    }_begin;

    Set(A&allocator);
    Set(const Set&set);
    ~Set();
    void destroy(Node*p);
    void splay(Node*p);
    iterator insert(const T&e);
    iterator find(const T&e) noexcept;
    void erase(const T&e);
    iterator begin() const noexcept;
    iterator end() const noexcept;
    u3 size() const noexcept;
};
