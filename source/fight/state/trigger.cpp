#pragma once

template<typename T>
struct Trigger
{
	DS::Map<u2,T> map;
	using A=DS::Map<u2,T>::A;
	
	Trigger(A&a):map(a){}
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
	void operator()(Arg&...arg)
	{
		for(auto&[k,v]:map)
			if(v(arg...))break;
	}
};

