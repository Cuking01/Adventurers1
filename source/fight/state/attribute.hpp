#pragma once

struct Attribute_A
{
    Trigger_A<Buff> trigger_a;
    Attribute_A(Mem::SA&sa);
};

struct Attribute
{
    f3 x;
    f3 min,max;
    Trigger<Buff> trigger;
    using A=Attribute_A;

    Attribute(A&a);
    Attribute(f3 x,A&a);
    Attribute(f3 x,f3 min,f3 max,A&a);
    void add(u2 key,const Buff&buff);
    void erase(u2 key);
    Buff* find(u2 key);
    f3 operator()();

};

