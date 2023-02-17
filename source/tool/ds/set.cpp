#pragma once

template<typename T>
Set_Node<T>::void rotate()
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

template<typename T>
Set<T>::iterator& Set<T>::iterator::operator++()
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
template<typename T>
int Set<T>::iterator::operator!=(iterator b) const
{
	return t!=b.t;
}

template<typename T>
int Set<T>::iterator::operator==(iterator b) const
{
	return t==b.t;
}
template<typename T>
const T& Set<T>::iterator::operator*() const
{
	return t->ele;
}
template<typename T>
const T* Set<T>::iterator::operator->() const
{
	return &t->ele;
}

template<typename T>
Set<T>::Set(A&allocator):allocator(allocator)
{
	root=nullptr;
	_begin.t=nullptr;
	sz=0;
}

template<typename T>
void Set<T>::destroy(Node*p)
{
	if(!p)return;

	destroy(p->l);
	destroy(p->r);
	allocator<<p;
}

template<typename T>
Set<T>::~Set()
{
	destroy(root);
	root=nullptr;
	sz=0;
}
template<typename T>
void Set<T>::splay(Node*p)
{
	while(p->f)
	{
		if(p->f->f)
			p->f->rotate();
		p->rotate();
	}
	root=p;
}

template<typename T>
Set<T>::iterator Set<T>::insert(const T&e)
{
	if(root==nullptr)
	{
		root=new (allocator.allocate()) Node{e,nullptr,nullptr,nullptr};
		_begin.t=root;
		sz++;
		return {root};
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
				sz++;
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
				sz++;
				break;
			}
		}
	}
	splay(p);
	return {p};
}

template<typename T>
Set<T>::iterator Set<T>::find(const T&e) noexcept
{
	Node*p=root;
	Node*t=nullptr;
	while(p&&(e<p->ele||p->ele<e))
	{
		t=p;
		if(e<p->ele)p=p->l;
		else p=p->r;
	}
	if(p)
	{
		splay(p);
		return {p};
	}
	if(t)splay(t);
	return {nullptr};
}
template<typename T>
void Set<T>::erase(const T&e)
{
	Node*p=find(e).t;
	if(!p)return;
	if(p->l&&p->r)
	{
		Node*t=p->l;
		root=t;
		while(t->r)t=t->r;
		splay(t);
		t->r=p->r;
		p->r->f=t;
	}
	else if(p->l)
	{
		root=p->l;
		p->l->f=nullptr;
	}
	else if(p->r)
	{
		root=p->r;
		p->r->f=nullptr;

		Node*t=root;
		while(t->l)t=t->l;
		_begin.t=t;
	}
	else
	{
		root=nullptr;
		_begin.t=nullptr;
	}
	sz--;
	allocator<<p;
}
template<typename T>
Set<T>::iterator Set<T>::begin() const noexcept
{
	return _begin;
}
template<typename T>
Set<T>::iterator Set<T>::end() const noexcept
{
	return iterator{nullptr};
}
