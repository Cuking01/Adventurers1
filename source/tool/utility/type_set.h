#pragma once

namespace type_set_detail
{

template<u3 x>
using Int_T=std::integral_constant<u3,x>;

template<typename... Ts>
struct Type_Set;

template<typename T>
concept Type_Set_Ins=is_template_ins<Type_Set,T>;

template<Type_Set_Ins... Ts>
using merge=std::remove_reference_t<decltype((Ts{}|...))>;

};

using type_set_detail::Type_Set;
using type_set_detail::Type_Set_Ins;
template<Type_Set_Ins... Ts>
using type_set_merge=type_set_detail::merge<Ts...>;
