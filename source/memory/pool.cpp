#pragma once

template<typename T,u3 bs>
struct Pool
{
	static_assert(bs>0);
	union Node
	{
		T obj;
		Node*next;
	};
	struct Block
	{
		Node node[bs];
		Block*next;
	};
	using SA=Mem::SA;

	SA* source_allocator;
	Block*block_list;
	Node*node_list;

	Pool(SA&sa):source_allocator(&sa),block_list(nullptr),node_list(nullptr){}
	~Pool()
	{
		Block*nxt;
		for(Block*p=block_list;p;p=nxt)
		{
			nxt=p->next;
			source_allocator->free((void*)((char*)p-al));
		}
	}
	void alloc()
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

	T* allocate()
	{
		if(node_list==nullptr)
			alloc();
		T*p=&node_list->obj;
		node_list=node_list->next;
		return p;
	}

	void deallocate(T*p)
	{
		Node*n=(Node*)p;
		n->next=node_list;
		node_list=n;
	}

	template<typename... Arg>
	T*operator()(Arg&&... arg)
	{
		T*p=allocate();
		return new(p) T(std::forward<Arg>(arg)...);
	}

	void operator<<(T*p)
	{
		p->~T();
		deallocate(p);
	}
};
