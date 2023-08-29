#pragma once

namespace mtu_allocor_detail
{
	constexpr u3 MTU_allocor_size_map(u3 sz)
	{
	    //8字节一组
	    if(sz<=32)
	        return (sz+7)/8*8;
	    //16字节一组
	    else
	        return (sz+15)/16*16;
	}


template<typename... Ts>
struct Basic_Allocor_Set<Type_Set<Ts...>>
{
    using Set=Type_Set<Ts...>;

    std::tuple<Basic_Allocor<Ts::value>...> allocors;

    template<typename T>
    SA& id(SA&sa)
    {
    	return sa;
    }

    Basic_Allocor_Set(SA&sa):
    	allocors{id<Ts>(sa)...}
    {}

    template<u3 sz>
    auto& get()
    {
        return std::get<Set::template find<Int_T<sz>>>(allocors);
    }

    template<typename T>
    auto& find()
    {
        return std::get<Set::template find<Int_T<MTU_allocor_size_map(sizeof(T))>>>(allocors);
    }
};

template<typename... Ts>
struct MTU_Allocor_Source
{
    using Set=Type_Set<Ts...>;

    Basic_Allocor_Set<type_set_merge<Type_Set<Int_T<MTU_allocor_size_map(sizeof(Ts))>>...>> basic_allocor_set;

    
};

template<typename... Ts>
struct MTU_Allocor_Source_Ref<Type_Set<Ts...>>
{
    using Set=Type_Set<Ts...>;

    std::tuple<Basic_Allocor<Ts::value>*...> allocors_ref;

    template<typename... T2s>
    MTU_Allocor_Source_Ref(Basic_Allocor_Set<T2s...>&sa):
        allocors_ref{&sa.template get<Ts::value>()...}
    {}

    template<typename... T2s>
    MTU_Allocor_Source_Ref(const MTU_Allocor_Source_Ref<T2s...>& sar):
        allocors_ref{sar.template get<Ts::value>()...}
    {}

    MTU_Allocor_Source_Ref(const MTU_Allocor_Source_Ref&sar):
        allocors_ref{sar.template get<Ts::value>()...}
    {}

    template<u3 sz>
    auto& get()
    {
        return std::get<Set::template find<Int_T<sz>>>(allocors_ref);
    }

    template<u3 sz>
    const auto& get() const
    {
        return std::get<Set::template find<Int_T<sz>>>(allocors_ref);
    }

    template<typename T>
    auto& find()
    {
        return std::get<Set::template find<Int_T<MTU_allocor_size_map(sizeof(T))> > >(allocors_ref);
    }
    template<typename T>
    const auto& find() const
    {
        return std::get<Set::template find<Int_T<MTU_allocor_size_map(sizeof(T))> > >(allocors_ref);
    }
};

template<typename Base,typename Derived>
struct lower_cast_impl<Base,Derived,true>
{
    static Derived* cast(Base*p) noexcept
    {
        return dynamic_cast<Derived*>(p);
    }
};

template<typename Base,typename Derived>
struct lower_cast_impl<Base,Derived,false>
{
    static Derived* cast([[maybe_unused]]Base*p) noexcept
    {
        return nullptr;
    }
};

template<typename Base,typename Derived>
Derived* lower_cast(Base*p) noexcept;

template<typename... Ts>
struct MTU_Allocor    //Multi_Type_Union_Allocor
{
    using Set=Type_Set<Ts...>;
    using SZ_Set=type_set_merge<Type_Set<Int_T<MTU_allocor_size_map(sizeof(Ts))>>...>;

    MTU_Allocor_Source_Ref<SZ_Set>  source_ref;

    template<typename... T2s>
    MTU_Allocor(MTU_Allocor_Source<T2s...>& sa):
        source_ref{sa.basic_allocor_set}
    {}

    template<typename... T2s>
    MTU_Allocor(const MTU_Allocor<T2s...>& source_allocor):
        source_ref{source_allocor.source_ref}
    {}

    MTU_Allocor(const MTU_Allocor& source_allocor):
        source_ref{source_allocor.source_ref}
    {}

    //获取构造器
    template<typename T>
    auto get_constructor() const noexcept
    {
        return [allocor=source_ref.template find<T>()]<typename... Args>(Args&&... args)
        {
            return new(allocor->allocate()) T{std::forward<Args&&>(args)...};
        };
    }

    //获取分配器
    template<typename T>
    auto get_allocor() const noexcept
    {
        return [allocor=source_ref.template find<T>()]()
        {
            return (T*)allocor->allocate();
        };
    }

    //分配并构造一个T
    template<typename T,typename... Args>
    T* construct(Args&&...args) const
    {
        return new(alloc<T>()) T{std::forward<Args&&>(args)...};
    }

    //只分配，不构造
    template<typename T>
    T* alloc() const
    {
        return (T*)source_ref.template find<T>()->allocate();
    }

    //静态解分配
    template<typename T>
    void dealloc(T*p) const
    {
        source_ref.template find<T>()->deallocate(p);
    }

    //静态销毁
    template<typename T>
    void destruct(T*p) const
    {
        p->~T();
        dealloc(p);
    }

    //多态类型销毁
    template<typename T>
    void virtual_destruct(T*p) const
    {
        if(!((lower_cast<T,Ts>(p)&&(virtual_destruct<Ts>(lower_cast<T,Ts>(p)),true))||...))
            destruct<T>(p);
    }

    //获取解分配器
    template<typename T>
    auto get_deallocor() const noexcept
    {
        return [allocor=source_ref.template find<T>()](T*p)->void
        {
            allocor->deallocate(p);
        };
    }

    //获取销毁器
    template<typename T>
    auto get_destructor(T*p) const noexcept
    {
        return [allocor=source_ref.template find<T>()](T*p)->void
        {
            p->~T();
            allocor->deallocate(p);
        };
    }
};

template<typename... Ts>
struct Make_MTU_Alloc<Type_Set<Ts...>>
{
    using type=MTU_Allocor<Ts...>;
};

};