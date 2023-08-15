#pragma once

namespace type_set_detail
{

template<u3 i,typename T,typename... Ts>
struct type_set_get_impl
{
    using res=typename type_set_get_impl<i-1,Ts...>::res;
};

template<typename T,typename... Ts>
struct type_set_get_impl<0,T,Ts...>
{
    using res=T;
};

template<typename T,typename...Ts>
struct is_same_ex
{
    static constexpr bool res=(std::is_same_v<T,Ts>||...);
};

template<typename T,typename...Ts>
constexpr bool is_same_ex_v=is_same_ex<T,Ts...>::res;

template<bool x,typename T1,typename T2>
struct if_else
{
    using res=T1;
};

template<typename T1,typename T2>
struct if_else<false,T1,T2>
{
    using res=T2;
};

template<typename T,typename...Ts>
using type_set_add_impl=typename if_else<is_same_ex_v<T,Ts...>,Type_Set<Ts...>,Type_Set<Ts...,T>>::res;

template<Type_Set_Ins T1,Type_Set_Ins T2,u3 cnt>
struct type_set_merge_impl
{
    using res=typename type_set_merge_impl<typename T1::template add<typename T2::template get<cnt>>,T2,cnt+1>::res;
};

template<Type_Set_Ins T1,Type_Set_Ins T2>
struct type_set_merge_impl<T1,T2,T2::size>
{
    using res=T1;
};

template<Type_Set_Ins T1,Type_Set_Ins T2>
constexpr auto operator|(T1 a,T2 b)->typename type_set_merge_impl<T1,T2,0>::res
{
    return {};
}

template<Type_Set_Ins set,Type_Set_Ins subset>
constexpr bool is_subset_impl=false;

template<Type_Set_Ins set,typename... Ts>
constexpr bool is_subset_impl<set,Type_Set<Ts...>> =(set::template has<Ts>&&...);

template<typename T,typename... Ts>
constexpr bool check_repeat_impl=is_same_ex_v<T,Ts...>||check_repeat_impl<Ts...>;

template<typename T>
constexpr bool check_repeat_impl<T> =false;

template<typename... Ts>
constexpr bool check_repeat=check_repeat_impl<Ts...>;

template<>
constexpr bool check_repeat<> =false;

template<bool flag,typename T,typename... Ts>
struct type_set_find_impl
{
    static_assert(flag,"未找到");
    static constexpr u3 res=0;
};

template<bool flag,typename T,typename T1,typename... Ts>
struct type_set_find_impl<flag,T,T1,Ts...>
{
    static constexpr u3 res=std::is_same_v<T,T1>?0:type_set_find_impl<flag||std::is_same_v<T,T1>,T,Ts...>::res+1;
};

template<typename... Ts>
struct Type_Set
{
    static_assert(!check_repeat<Ts...>);

    template<u3 i>
    using get=typename type_set_get_impl<i,Ts...>::res;

    template<typename T>
    using add=type_set_add_impl<T,Ts...>;

    template<typename T>
    static constexpr bool has=is_same_ex_v<T,Ts...>;

    template<Type_Set_Ins T2>
    static constexpr bool is_subset=is_subset_impl<Type_Set,T2>;

    template<typename T>
    static constexpr u3 find=type_set_find_impl<false,T,Ts...>::res;

    static constexpr u3 size=sizeof...(Ts);



    constexpr Type_Set(){}

    static void print()
    {
        ((std::cout<<typeid(Ts).name()<<'\n'),...);
    }
};

};

