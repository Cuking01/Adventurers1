#pragma once

//

template<template<typename...> typename TT,typename T>
struct is_template_ins_impl:std::false_type{};

template<template<typename...> typename TT,typename... Ts>
struct is_template_ins_impl<TT,TT<Ts...>>:std::true_type{};

template<template<typename...> typename TT,typename T>
concept is_template_ins=is_template_ins_impl<TT,T>::value;
