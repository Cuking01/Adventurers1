#pragma once

Integer_Literal::Integer_Literal(const Code_Char* begin,const Code_Char* end,Compiler&compiler)
	:Literal(Literal_T::Integer,begin->line,begin->col)
{
	//可以假设第一个字符一定是十进制数字

	auto read_val=[this,&compiler](const Code_Char*&begin,const Code_Char*end)->u4
	{

		u4 x=0;

		//普通十进制
		if(*begin!=L'0')
		{
			while(begin<end&&isdigit(*begin))
			{
				if((x>>64)==0)
					x=x*10+begin->c-L'0';
				begin++;
			}
			return x;
		}

		//到此*begin一定是'0'

		begin++;
		//0的情况
		if(begin==end)
			return 0;

		//二进制
		if(*begin==L'b'||*begin==L'B')
		{
			begin++;
			if(begin==end)
			{
				/*报错*/
				return 0;
			}
			while(begin<end&&bdigit(*begin))
			{
				if((x>>64)==0)
					x=x*2+begin->c-L'0';
				begin++;
			}
		}
		//十六进制
		else if(*begin==L'x'||*begin==L'X')
		{
			begin++;
			if(begin==end)
			{
				/*报错*/
				return 0;
			}
			while(begin<end&&hexdigit(*begin))
			{
				if((x>>64)==0)
					x=x*16+hextox(*begin);
				begin++;
			}
		}
		//八进制
		else
		{
			while(begin<end&&odigit(*begin))
			{
				if((x>>64)==0)
					x=x*8+begin->c-L'0';;
				begin++;
			}
		}
		return x;
	};

	auto read_type=[this,&compiler](const Code_Char*begin,const Code_Char*end)->Integer_T
	{
		if(end-begin!=3)
		{
			compiler.report_error(line,col,L"整数字面量后缀格式错误");
			return Integer_T::Int16;
		}

		auto cmp=[begin](const wchar_t*str)->s2
		{
			for(s2 i=0;i<3;i++)
				if(begin[i]!=str[i])
					return 0;
			return 1;
		};

		if(cmp(L"s16"))return Integer_T::Int16;
		if(cmp(L"s32"))return Integer_T::Int32;
		if(cmp(L"s64"))return Integer_T::Int64;
		if(cmp(L"u16"))return Integer_T::Uint16;
		if(cmp(L"u32"))return Integer_T::Uint32;
		if(cmp(L"u64"))return Integer_T::Uint64;

		compiler.report_error(line,col,L"整数字面量后缀格式错误");

		return Integer_T::Int16;
	};

	auto auto_type=[this,&compiler](u4 x)->Integer_T
	{
		if((x>>31)==0)return Integer_T::Int32;
		if((x>>63)==0)return Integer_T::Int64;
		return Integer_T::Uint64;
	};

	u4 x=read_val(begin,end);

	if(x>>64)
	{
		compiler.report_error(line,col,L"整数字面量数值过大");
		x=0;
	}

	if(begin==end)
		this->type=auto_type(x);
	else
		this->type=read_type(begin,end);
	this->x=x;
}

std::wstring Integer_Literal::what([[maybe_unused]] const Compiler&compiler) const
{
	const wchar_t* t=L"NULL";
	if(type==Integer_T::Int16)t=L"Int16";
	if(type==Integer_T::Int32)t=L"Int32";
	if(type==Integer_T::Int64)t=L"Int64";

	if(type==Integer_T::Uint16)t=L"Uint16";
	if(type==Integer_T::Uint32)t=L"Uint32";
	if(type==Integer_T::Uint64)t=L"Uint64";

	return std::format(L"integer_literal: {:s} {} {:d}",t,x,(s3)x);
}
	