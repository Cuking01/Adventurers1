#pragma once

template<typename TK,typename TV>
struct Map_T;

template<typename TK,typename TV,typename A>
struct Map;

template<typename TK,typename TV>
using Map_Node=Set_Node<Map_T<TK,TV>>;
