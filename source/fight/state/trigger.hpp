#pragma once

template<typename T>
struct Trigger_A
{
    DS::Map<u2,T>::A map_a;
    Trigger_A(Mem::SA&sa);
};

template<typename T>
struct Trigger:DS::Map<u2,T>
{   
    Trigger(Trigger_A<T>&a);
    void add(u2 key,const T&e);
    template<typename...Arg>
    s2 operator()(Arg&...arg);
};

