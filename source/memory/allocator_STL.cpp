#pragma once

template<typename T>
Allocator_STL<T>::Allocator_STL(SA&p):
	source_allocator(&p)
{}

template<typename T>
T* Allocator_STL<T>::allocate(u3 n)
{
    void*p=source_allocator->alloc(n*sizeof(T));
    in_use+=*(u3*)p;
    return (T*)((char*)p+al);
}

template<typename T>
T* Allocator_STL<T>::allocate_at_least(u3 n)
{
    return allocate(n);
}

template<typename T>
void Allocator_STL<T>::deallocate(T*p,[[maybe_unused]]u3 n)
{
    char*t=(char*)p-al;
    in_use-=*(u3*)t;
    source_allocator->free(t);
}
