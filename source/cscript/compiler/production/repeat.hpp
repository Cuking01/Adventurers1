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

	auto size() const
	{
		return items.size();
	}

	Item& operator[](u2 i)
	{
		return items[i];
	}

	template<typename Callback>
	void for_each(Callback&& callback)
	{
		for(auto&item:items)
			callback(*item);
	}

	template<typename Callback>
	void for_each_r(Callback&& callback)
	{
		for(auto it=items.rbegin();it!=items.rend();it++)
			callback(**it);
	}

	void print_ast(u2 dep,std::wostream&o);
};

template<typename Item>
struct Repeat_1:Production<Repeat_1<Item>>
{
	std::vector<typename Production<Item>::Handler> items;
	using Base=Production<Repeat_1<Item>>;

	Repeat_1(Compiler&compiler):Base(compiler)
	{
		
		while(1)
		{
			auto handler=Item::match(compiler);
			if(handler)
			{
				items.push_back(std::move(handler));
				Base::is_matched=true;
			}
			else
			{
				break;
			}
		}
	}

	~Repeat_1()
	{
		for(auto it=items.rbegin();it!=items.rend();it++)
			it->destroy();
	}

	auto size() const
	{
		return items.size();
	}

	Item& operator[](u2 i)
	{
		return items[i];
	}

	template<typename Callback>
	void for_each(Callback&& callback)
	{
		for(auto&item:items)
			callback(*item);
	}

	template<typename Callback>
	void for_each_r(Callback&& callback)
	{
		for(auto it=items.rbegin();it!=items.rend();it++)
			callback(**it);
	}

	void print_ast(u2 dep,std::wostream&o);
};

