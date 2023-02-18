#pragma once

template<typename T,u3 bs>
Pool<T,bs>::Pool(SA&sa):source_allocator(&sa),block_list(nullptr),node_list(nullptr){}
template<typename T,u3 bs>
Pool<T,bs>::~Pool()
{
	Block*nxt;
	for(Block*p=block_list;p;p=nxt)
	{
		nxt=p->next;
		source_allocator->free((void*)((char*)p-al));
	}
}
template<typename T,u3 bs>
void Pool<T,bs>::alloc()
{
	void*p=source_allocator->alloc(sizeof(Block));
	Block*b=(Block*)((char*)p+al);
	
	b->next=block_list;
	block_list=b;

	for(u3 i=0;i<bs;i++)
	{
		b->node[i].next=node_list;
		node_list=b->node+i;
	}
}

template<typename T,u3 bs>
T* Pool<T,bs>::allocate()
{
	if(node_list==nullptr)
		alloc();
	T*p=&node_list->obj;
	node_list=node_list->next;
	return p;
}

template<typename T,u3 bs>
void Pool<T,bs>::deallocate(T*p)
{
	Node*n=(Node*)p;
	n->next=node_list;
	node_list=n;
}

template<typename T,u3 bs>
template<typename... Arg>
T*Pool<T,bs>::operator()(Arg&&... arg)
{
	T*p=allocate();
	return new(p) T(std::forward<Arg>(arg)...);
}

template<typename T,u3 bs>
void Pool<T,bs>::operator<<(T*p)
{
	p->~T();
	deallocate(p);
}