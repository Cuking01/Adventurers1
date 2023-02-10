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


template<typename TK,typename TV,typename A>
struct Map
{
	using T=Map_T<TK,TV>;
	Set<T,A> set;

	Map(A&a):set(a){}

	TV& operator[](const TK&key)
	{
		auto it=set.insert({key,TV()});
		return it->value;
	}
	template<typename TKp,typename TVp>
	void insert(TKp&&key,TVp&&value)
	{
		static_assert(std::is_same_v<std::remove_reference<TKp>::type,std::remove_reference<TVp>::type>);
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
