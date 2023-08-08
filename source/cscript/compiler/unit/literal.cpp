#pragma once

Literal::Literal(Literal_T type,s2 line,s2 col) noexcept
	:Unit(Unit_T::Literal,line,col),type(type)
{}


String_Literal::String_Literal(const Code_Char* begin,const Code_Char* end,Compiler&compiler)
	:Literal(Literal_T::String,begin->line,begin->col)
{
	String_T type=String_T::String;
	if(*begin==L'L')type=String_T::Wstring,begin++;

	s2 len=0;

	for(Code_Char_Reader reader{begin+1,end-1,compiler};!reader.empty();)
	{
		wchar_t c=reader();
		if(c>=0&&c<=127||type==String_T::Wstring)
			len++;
		else
			len+=2;
	}

	Code_Char_Reader reader{begin+1,end-1,compiler};

	this->type=type;

	if(type==String_T::String)
	{
		u0*mem=compiler.mem_const.alloc<1>(len+1);
		this->p=mem;
		this->len=len+1;
		while(!reader.empty())
		{
			wchar_t c=reader();
			if(c>=0&&c<=127)
				*mem++=c;
			else
				*mem++=c&255u,*mem++=(c>>8)&255u;
		}
	}
	else
	{
		u0*mem=compiler.mem_const.alloc<2>(2*(len+1));
		this->p=mem;
		this->len=len+1;
		while(!reader.empty())
		{
			wchar_t c=reader();
			*(u1*)mem=c&65535u;
			mem+=2;
		}
	}
	

}
Char_Literal::Char_Literal(const Code_Char* begin,const Code_Char* end,Compiler&compiler)
	:Literal(Literal_T::Char,begin->line,begin->col)
{
	Char_T type=Char_T::Char;
	if(*begin==L'L')type=Char_T::Wchar,begin++;

	s2 len=0;
	wchar_t c=0;
	for(Code_Char_Reader reader{begin+1,end-1,compiler};!reader.empty();)
	{
		c=reader();
		if(c>=0&&c<=127||type==Char_T::Wchar)
			len++;
		else
			len+=2;
		if(len>=2)break;
	}

	if(len!=1){compiler.report_error(line,col,L"字符字面量长度错误");}


	this->type=type;
	if(type==Char_T::Char)
	{
		if(c>=0&&c<=127)
			this->c=c;
		else
			compiler.report_error(line,col,L"字符字面量长度错误");
	}
	else
	{
		this->wc=c&65535u;
	}
	
}
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
Float_Literal::Float_Literal(const Code_Char* begin,const Code_Char* end,Compiler&compiler)
	:Literal(Literal_T::Float,begin->line,begin->col)
{
	if(end-begin>1000)
	{
		compiler.report_error(line,col,L"浮点字面量过长");
		this->type=Float_T::F32;
		this->f32=0;
		return;
	}

	auto type=Float_T::F64;
	if(*(end-1)==L'f')
	{
		type=Float_T::F32;
		end--;
	}

	s2 cnt_point=0;
	s2 flag_other=0;
	char tmp[1001];

	for(s2 i=0;begin+i<end;i++)
	{
		if(begin[i]==L'.')cnt_point++;
		else if(!isdigit(begin[i]))flag_other=1;
		tmp[i]=(char)begin[i].c;
	}

	if(flag_other)
	{
		compiler.report_error(line,col,L"浮点字面量格式错误");
	}

	this->type=type;
	if(type==Float_T::F64)
		sscanf(tmp,"%lf",&this->f64);
	else
		sscanf(tmp,"%f",&this->f32);

}
