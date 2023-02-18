#pragma once

template<typename TK,typename TV>
int Map_T<TK,TV>::operator<(const Map_T&b) const
{
	return key<b.key;
}


template<typename TK,typename TV>
Map<TK,TV>::Map(A&a):set(a){}

template<typename TK,typename TV>
TV& Map<TK,TV>::operator[](const TK&key)
{
	auto it=set.insert({key,TV()});
	return it->value;
}

template<typename TK,typename TV>
template<typename TKp,typename TVp>
void Map<TK,TV>::insert(TKp&&key,TVp&&value)
{
	set.insert({std::forward<TKp>(key),std::forward<TVp>(value)});
}
template<typename TK,typename TV>
void Map<TK,TV>::erase(const TK&key) noexcept
{
	set.erase({key,TV()});
}


template<typename TK,typename TV>
Set<typename Map<TK,TV>::T>::iterator Map<TK,TV>::find(const TK&key) noexcept
{
	return set.find({key,TV()});
}

template<typename TK,typename TV>
Set<typename Map<TK,TV>::T>::iterator Map<TK,TV>::begin() const noexcept
{
	return set.begin();
}
template<typename TK,typename TV>
Set<typename Map<TK,TV>::T>::iterator Map<TK,TV>::end() const noexcept
{
	return set.end();
}
