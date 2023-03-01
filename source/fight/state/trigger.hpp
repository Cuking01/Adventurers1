#pragma once

template<typename T>
struct Trigger_A
{
    DS::Map<u2,T>::A map_a;
    Trigger_A(Mem::SA&sa);
};

template<typename T>
struct Trigger
{
    DS::Map<u2,T> map;
    using A=Trigger_A<T>;
    
    Trigger(A&a);
    void add(u2 key,const T&e);
    void erase(u2 key);
    T* find(u2 key);
    
    template<typename...Arg>
    s2 operator()(Arg&...arg);
};

