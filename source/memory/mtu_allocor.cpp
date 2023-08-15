#pragma once

namespace mtu_allocor_detail
{

template<typename Base,typename Derived>
Derived* lower_cast(Base*p) noexcept
{
    return lower_cast_impl<Base,Derived,
                                        std::is_polymorphic_v<Base>&&
                                        std::is_polymorphic_v<Derived>&&
                                        std::is_base_of_v<Base,Derived>&&
                                        !std::is_same_v<Base,Derived>>::cast(p);
}

};