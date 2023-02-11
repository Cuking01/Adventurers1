#pragma once

template<typename TK,typename TV>
struct Map_T
{
	TK key;
	mutable TV value;
	int operator<(const Map_T&b) const
	{
		return key<b.key;
	}
};


template<typename TK,typename TV>
struct Map
{
	using T=Map_T<TK,TV>;
	using A=Mem::Pool<Set_Node<T>,32>;
	Set<T> set;

	Map(A&a):set(a){}

	TV& operator[](const TK&key)
	{
		auto it=set.insert({key,TV()});
		return it->value;
	}
	template<typename TKp,typename TVp>
	void insert(TKp&&key,TVp&&value)
	{
		set.insert({std::forward<TKp>(key),std::forward<TVp>(value)});
	}
	void erase(const TK&key)
	{
		set.erase({key,TV()});
	}


	auto find(const TK&key)
	{
		return set.find({key,TV()});
	}

	auto begin() const noexcept
	{
		return set.begin();
	}

	auto end() const noexcept
	{
		return set.end();
	}
};
