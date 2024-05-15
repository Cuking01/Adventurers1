#pragma once


template<typename Item>
struct Repeat:Production<Repeat<Item>>
{
	std::vector<typename Production<Item>::Handler> items;
	using Base=Production<Repeat<Item>>;

	Repeat(Compiler&compiler):Base(compiler)
	{
		Base::is_matched=true;
		while(1)
		{
			auto handler=Item::match(compiler);
			if(handler)
				items.push_back(std::move(handler));
			else
				break;
		}
	}

	~Repeat()
	{
		for(auto it=items.rbegin();it!=items.rend();it++)
			it->destroy();
	}
};


