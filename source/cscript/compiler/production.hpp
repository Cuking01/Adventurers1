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

		operator bool() noexcept
		{
			return *production;
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

		Handler& operator=(Handler&&handler)=default;

		Handler(){}

		Handler(Compiler&compiler):production(new Production_Derived(compiler))
		{

		}

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



namespace Productions
{
	#include"production/declaration.hpp"

};

