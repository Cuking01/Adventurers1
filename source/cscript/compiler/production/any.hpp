#pragma once

template<typename... Items>
struct Any:Production<Any<Items...>>
{ 
	std::variant<typename Production<Items>::Handler...> handler;

	using Base=Production<Any<Items...>>;

	Any(Compiler&compiler):Base(compiler)
	{
		auto helper=[this](auto&&handler)
		{
			bool ret=handler;
			this->handler=std::move(handler);
			return ret;
		};
		Base::is_matched=((helper(Items::match(compiler)))||...);
	}

	template<typename... Callbacks>
	void dispatch_call(Callbacks&&...callbacks)
	{
		((is<Items>()&&(callbacks(get<Items>()),true))||...);
	}

	template<typename T>
	bool is() const noexcept
	{
		return holds_alternative<typename T::Handler>(handler);
	}

	template<typename T>
	T& get()
	{
		return *std::get<typename T::Handler>(handler);
	}

	void print_ast(u2 dep,std::wostream&o);
};


