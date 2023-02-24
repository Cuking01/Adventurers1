#pragma once

template<typename TK,typename TV>
struct Map_T
{
    TK key;
    mutable TV value;
    int operator<(const Map_T&b) const;
};


template<typename TK,typename TV>
struct Map
{
    using T=Map_T<TK,TV>;
    using A=Mem::Pool<Set_Node<T>,31>;
    Set<T> set;

    Map(A&a);

    TV& operator[](const TK&key);
    template<typename TKp,typename TVp>
    void insert(TKp&&key,TVp&&value);
    void erase(const TK&key) noexcept;

    Set<T>::iterator find(const TK&key) noexcept;
    Set<T>::iterator begin() const noexcept;
    Set<T>::iterator end() const noexcept;

    u3 size() const noexcept;
};
