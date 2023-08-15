#pragma once

namespace mtu_allocor_detail
{

template<u3 x>
using Int_T=std::integral_constant<u3,x>;

//这个type_set是类型转换后大小的对应Int_T的集合
template<Type_Set_Ins T>
struct Basic_Allocor_Set;


//MTU_Allocor_Source包含了分配器的实体。
template<typename... Ts>
struct MTU_Allocor_Source;


//这个type_set是类型转换后大小的对应Int_T的集合
template<Type_Set_Ins T>
struct MTU_Allocor_Source_Ref;

template<typename Base,typename Derived,bool flag>
struct lower_cast_impl;

template<typename... Ts>
struct MTU_Allocor;    //Multi_Type_Union_Allocor

template<typename T>
concept MTU_Allocor_Ins=is_template_ins<MTU_Allocor,T>;

template<Type_Set_Ins T>
struct Make_MTU_Alloc;

template<MTU_Allocor_Ins... Ts>
using MTU_merge=typename Make_MTU_Alloc<type_set_merge<typename Ts::Set ...>>::type;

template<Type_Set_Ins T>
struct Make_MTU_SA;

template<typename... Ts>
struct Make_MTU_SA<Type_Set<Ts...>>
{
    using type=MTU_Allocor_Source<Ts...>;
};

template<MTU_Allocor_Ins T>
using MTU_SA=typename Make_MTU_SA<typename T::Set>::type;

};

using mtu_allocor_detail::MTU_Allocor;
using mtu_allocor_detail::MTU_SA;
using mtu_allocor_detail::MTU_merge;
