#pragma once

template<typename T,typename A>
struct Trigger
{
	DS::Set<T,A> set;
	Trigger(A&a):set(a){}
	void insert(const T&e){set.insert(e);}
	void erase(const T&e){set.erase(e);}
	
};
