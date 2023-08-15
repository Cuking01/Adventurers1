#pragma once

template<typename T,u3 bs>
Pool<T,bs>::Pool(SA&sa):allocor(sa){}


template<typename T,u3 bs>
T* Pool<T,bs>::allocate()
{
	return (T*)allocor.allocate();
}

template<typename T,u3 bs>
void Pool<T,bs>::deallocate(T*p)
{
	allocor.deallocate(p);
}

template<typename T,u3 bs>
template<typename... Args>
T*Pool<T,bs>::operator()(Args&&... args)
{
	T*p=(T*)allocate();
	return new(p) T(std::forward<Args&&>(args)...);
}

template<typename T,u3 bs>
void Pool<T,bs>::operator<<(T*p)
{
	p->~T();
	deallocate(p);
}
