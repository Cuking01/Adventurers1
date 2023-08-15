#pragma once

template<u3 sz,u3 bs>
Basic_Allocor<sz,bs>::Basic_Allocor(SA&sa) noexcept:source_allocator(&sa),block_list(nullptr),node_list(nullptr){}
template<u3 sz,u3 bs>
Basic_Allocor<sz,bs>::~Basic_Allocor()
{
	Block*nxt;
	for(Block*p=block_list;p;p=nxt)
	{
		nxt=p->next;
		source_allocator->free((void*)((char*)p-al));
	}
}
template<u3 sz,u3 bs>
void Basic_Allocor<sz,bs>::alloc()
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

template<u3 sz,u3 bs>
void* Basic_Allocor<sz,bs>::allocate()
{
	if(node_list==nullptr)
		alloc();
	char*p=node_list->mem;
	node_list=node_list->next;
	return (void*)p;
}

template<u3 sz,u3 bs>
void Basic_Allocor<sz,bs>::deallocate(void*p)
{
	Node*n=(Node*)p;
	n->next=node_list;
	node_list=n;
}
