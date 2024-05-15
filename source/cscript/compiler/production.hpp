#pragma once


template<typename Production_Derived>
struct Production
{
	Compiler*compiler;
	bool is_matched;

	Production(Compiler&compiler):compiler(&compiler),is_matched(false){}

	operator bool() const noexcept
	{
		return is_matched;
	}


	struct Handler
	{
		std::unique_ptr<Production_Derived> production;
		using Production_T=Production_Derived;

		operator bool() noexcept
		{
			return production.get()&&*production;
		}

		Production_Derived* operator->()
		{
			return production.get();
		}

		Production_Derived& operator*()
		{
			return *production;
		}

		operator Production_Derived*()
		{
			return production.get();
		}

		void destroy()
		{
			production=nullptr;
		}

		Handler& operator=(Handler&&handler) noexcept =default;

		Handler(){}

		Handler(Compiler&compiler):production(new Production_Derived(compiler))
		{
			if(!*production)
				destroy();
		}

		Handler(Handler&&) noexcept =default;

		~Handler()
		{

		}
	};


	static Handler match(Compiler&compiler)
	{
		return {compiler};
	}

	static Handler match(Compiler*compiler)
	{
		return match(*compiler);
	}

};


template<typename... Handlers>
bool multi_match(Compiler&compiler,Handlers&... handlers)
{
	if(((handlers=Handlers::Production_T::match(compiler))&&...))
		return true;
	return false;
}

namespace Productions
{
	#include"production/any.hpp"
	#include"production/repeat.hpp"
	#include"production/combination.hpp"
	#include"production/opt.hpp"
	#include"production/symbol_set.hpp"
	#include"production/idt.hpp"
	#include"production/literal.hpp"
	#include"production/declaration.hpp"
	#include"production/expression.hpp"
};

