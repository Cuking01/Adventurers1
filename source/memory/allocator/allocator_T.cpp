#pragma once

//一般内存分配器，线程不安全版本，可以用于STL容器使用


template<typename T>
Allocator<T>::Allocator(SA&sa) noexcept :source_allocator(&sa),in_use(0){}

template<typename T>
Allocator<T>::~Allocator()
{
	//if(in_use)Warning("xigou:xie lou!%llu\n",in_use);
}
template<typename T>
void*Allocator<T>::alloc(u3 sz)
{
	void*p=source_allocator->alloc(sz);
	in_use+=*(u3*)p;
	return p;
}

template<typename T>
void Allocator<T>::free(void*p)
{
	in_use-=*(u3*)p;
	source_allocator->free(p);
}

template<typename T>
T* Allocator<T>::allocate(u3 n)
{
	void*p=alloc(n*sizeof(T));
	return (T*)((char*)p+al);
}

template<typename T>
void Allocator<T>::deallocate(T*p)
{
	free((void*)((char*)p-al));
}

template<typename T>
void Allocator<T>::operator<<(T*p)
{
	u3 n=*(u3*)((char*)p-al);
	for(u3 i=0;i<n;i+=sizeof(T))
		((T*)((char*)p+i))->~T();
	deallocate(p);
}

