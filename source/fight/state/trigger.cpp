#pragma once

template<typename T>
Trigger_A<T>::Trigger_A(Mem::SA&sa):
	map_a(sa)
{}

template<typename T>
Trigger<T>::Trigger(Trigger_A<T>&a):DS::Map<u2,T>(a.map_a){}

template<typename T>
void Trigger<T>::add(u2 key,const T&e){this->insert(key,e);}

template<typename T>
template<typename...Arg>
s2 Trigger<T>::operator()(Arg&&...arg)
{
	for(auto&[k,v]:*this)
		if(s2 ret=v(std::forward<Arg&&>(arg)...);ret)
			return ret;
	return 0;
}
