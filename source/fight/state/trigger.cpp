#pragma once

template<typename T>
struct Trigger_Node
{
	T ele;
	Trigger_Node*f,*l,*r;

	void rotate()
	{
		auto*p=f;
		if(p->l==this)
		{
			p->l=r;
			if(r)r->f=p;
			r=p;
		}
		else
		{
			p->r=l;
			if(l)l->f=p;
			l=p;
		}
		if(p->f)
			(p->f->l==p?p->f->l:p->f->r)=this;
		f=p->f;
		p->f=this;
	}
};

template<typename T,typename A>
struct Trigger
{
	using Node=Trigger_Node<T>;
	//using A=Mem::Pool<Node,SA,bs>;
	
	A&allocator;
	//State&g_state;

	Node*root;
	

	struct iterator
	{
		Node*t;
		iterator& operator++()
		{
			Node*p=t;
			if(!p)return *this;
			if(p->r)
			{
				p=p->r;
				while(p->l)p=p->l;
			}
			else
			{
				while(p)
				{
					Node*tp=p;
					p=p->f;
					if(p&&p->l==tp)break;
				}
			}
			t=p;
			return *this;
		}

		int operator!=(iterator b) const
		{
			return t!=b.t;
		}

		const T& operator*() const
		{
			return t->ele;
		}
	}_begin;
	Trigger(A&allocator):allocator(allocator)
	{
		root=nullptr;
		_begin.t=nullptr;
	}

	void splay(Node*p)
	{
		while(p->f)
		{
			if(p->f->f)
				p->f->rotate();
			p->rotate();
		}
		root=p;
	}

	void insert(const T&e)
	{
		if(root==nullptr)
		{
			root=new (allocator.allocate()) Node{e,nullptr,nullptr,nullptr};
			_begin.t=root;
			return;
		}
		Node*p=root;
		while(p->ele<e||e<p->ele)
		{
			if(e<p->ele)
			{
				if(p->l)
					p=p->l;
				else
				{
					p->l=new (allocator.allocate()) Node{e,p,nullptr,nullptr};
					if(p==_begin.t)_begin.t=p->l;
					p=p->l;
					break;
				}
			}
			else
			{
				if(p->r)
					p=p->r;
				else
				{
					p->r=new (allocator.allocate()) Node{e,p,nullptr,nullptr};
					p=p->r;
					break;
				}
			}
		}
		splay(p);

	}



	void erase()
	{

	}
	iterator begin() const noexcept
	{
		return _begin;
	}
	iterator end() const noexcept
	{
		return iterator{nullptr};
	}
};
