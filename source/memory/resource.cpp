#pragma once

namespace Resource
{
	void*alloc(u3 sz)
	{
		sz+=al;
		void*p=malloc(sz);

		if(p==nullptr)
			exit(0);

		*(u3*)p=sz;
		in_use+=sz;

		return p;
	}
	void free(void*p)
	{
		in_use-=*(u3*)p;
		::free(p);
	}
};
