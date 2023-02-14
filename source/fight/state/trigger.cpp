#pragma once

template<typename T>
struct Trigger_A
{
	DS::Map<u2,T>::A map_a;
	Trigger_A(Mem::SA&sa):
		map_a(sa)
	{}
};

template<typename T>
struct Trigger
{
	DS::Map<u2,T> map;
	using A=Trigger_A<T>;
	
	Trigger(A&a):map(a.map_a){}
	void insert(u2 key,const T&e){map.insert(key,e);}
	void erase(u2 key){map.erase(key);}
	T* find(u2 key)
	{
		auto it=map.find(key);
		if(it==map.end())
			return nullptr;
		return &it->value;
	}
	

	template<typename...Arg>
	s2 operator()(Arg&...arg)
	{
		for(auto&[k,v]:map)
			if(s2 ret=v(arg...);ret)
				return ret;
		return 0;
	}
};

