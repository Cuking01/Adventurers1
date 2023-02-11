#pragma once

struct Attribute
{
	f3 x;
	f3 min,max;
	Trigger<Buff> trigger;
	using A=Attribute_A;

	Attribute(f3 x,A&a):x(x),min(0),max(inf),trigger(a){}
	Attribute(f3 x,f3 min,f3 max,A&a):x(x),min(min),max(max),trigger(a){}
	void add(u2 key,const Buff&buff)
	{
		trigger.insert(key,buff);
	}
	void erase(u2 key)
	{
		trigger.erase(key);
	}
	Buff* find(u2 key)
	{
		return trigger.find(key);
	}

	f3 operator()()
	{
		Buff_Helper bh;
		trigger(*this,bh);
		f3 tmp=bh(x);
		return std::max(std::min(tmp,max),min);
	}

};

