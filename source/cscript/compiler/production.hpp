#pragma once

template<u2 len>
struct Name_Str
{
	char str[len];


	constexpr Name_Str(const char(&s)[len])
	{
		for(u2 i=0;i<len;i++)
			str[i]=s[i];
	}

	constexpr Name_Str(u2 x)
	{
		for(u2 i=0;i<len-1;i++)
		{
			str[len-2-i]=x%10+'0';
			x/=10;
		}
		str[len-1]='\0';
	}

	template<u2 len1,u2 len2>
	constexpr Name_Str(const char(&s1)[len1],const char(&s2)[len2])
	{
		static_assert(len1>=1);
		for(u2 i=0;i<len1;i++)
			str[i]=s1[i];
		for(u2 i=0;i<len2;i++)
			str[i+len1-1]=s2[i];
	}


	operator const char*() const
	{
		return str;
	}
};

template<u2 len1,u2 len2>
constexpr auto operator+(const Name_Str<len1> s1,const Name_Str<len2> s2)->Name_Str<len1+len2-1>
{
	return Name_Str<len1+len2-1>(s1.str,s2.str);
};

constexpr u2 x_len(u2 k)
{
	if(k<10)return 1;
	return x_len(k/10)+1;
}

template<u2 k>
constexpr auto make_name()
{
	return Name_Str<x_len(k)+1>(k);
}

int cnt_g=0;

template<typename Production>
struct Production_Handler
{
	std::unique_ptr<Production> production;
	using Production_T=Production;

	operator bool() noexcept
	{
		return production.get()&&*production;
	}

	Production* operator->()
	{
		return production.get();
	}

	Production& operator*()
	{
		return *production;
	}

	operator Production*()
	{
		return production.get();
	}

	void destroy()
	{
		production=nullptr;
	}

	Production_Handler& operator=(Production_Handler&&handler) noexcept =default;

	Production_Handler(){}

	Production_Handler(Compiler&compiler):production(new Production(compiler))
	{
		if(!*production)
			destroy();
	}

	Production_Handler(Production_Handler&&) noexcept =default;

	~Production_Handler()
	{

	}

};

template<typename Production_Derived>
struct Production
{
	Compiler*compiler;
	bool is_matched;
	static inline int cnt=0;

	Production(Compiler&compiler);

	~Production();

	operator bool() const noexcept
	{
		return is_matched;
	}

	using Handler=Production_Handler<Production_Derived>;

	static Handler match(Compiler&compiler)
	{
		return {compiler};
	}

	static Handler match(Compiler*compiler)
	{
		return match(*compiler);
	}

	void print_tree(u2 dep,std::wostream&o)
	{
		if(dep==0)return;
		for(u2 i=0;i<dep-1;i++)
			o<<"|   ";
		o<<"|---";
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
	#include"production/statement.hpp"
};

