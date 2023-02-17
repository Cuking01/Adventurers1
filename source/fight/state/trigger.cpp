#pragma once

template<typename T>
Trigger_A<T>::Trigger_A(Mem::SA&sa):
	map_a(sa)
{}

template<typename T>
Trigger<T>::Trigger(A&a):map(a.map_a){}
template<typename T>
Trigger<T>::void insert(u2 key,const T&e){map.insert(key,e);}
template<typename T>
Trigger<T>::void erase(u2 key){map.erase(key);}
template<typename T>
Trigger<T>::T* find(u2 key)
{
	auto it=map.find(key);
	if(it==map.end())
		return nullptr;
	return &it->value;
}
	

template<typename T>
template<typename...Arg>
Trigger<T>::
s2 operator()(Arg&...arg)
{
	for(auto&[k,v]:map)
		if(s2 ret=v(arg...);ret)
			return ret;
	return 0;
}
