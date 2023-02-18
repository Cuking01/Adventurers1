#pragma once

//根内存分配器

void* Allocator<Root_Source_T>::alloc(u3 sz){return Resource::alloc(sz);}

void Allocator<Root_Source_T>::free(void*p){Resource::free(p);}
