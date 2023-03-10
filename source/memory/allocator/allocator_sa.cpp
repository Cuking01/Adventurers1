#pragma once

//源内存分配器，支持内部内存分配与解分配，线程不安全版本

Allocator<Source_T>::~Allocator()
{
	//if(in_use)Warning("xigou:xie lou!%llu\n",in_use);
}

void*Allocator<Source_T>::alloc(u3 sz)
{
	void*p=source_allocator->alloc(sz);
	in_use+=*(u3*)p;
	return p;
}

void Allocator<Source_T>::free(void*p)
{
	in_use-=*(u3*)p;
	source_allocator->free(p);
}

