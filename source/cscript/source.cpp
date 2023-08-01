#pragma once


Code_Char_Reader::Code_Char_Reader(const Code_Char*begin,const Code_Char* end) noexcept
	:begin(begin),end(end)
{}

s2 Code_Char_Reader::empty() const noexcept
{
	return begin==end;
}

wchar_t Code_Char_Reader::operator()() 
{
	if(!empty())
		throw std::runtime_error("Code_Char_Reader:empty.");
	//非转义字符
	if(*begin!=L'\\')
		return *begin;

	begin++;
	if(begin==end)
	{
		/*报错*/
		return 0;
	}
	//特定含义转义
	wchar_t c=0;
	switch(begin->c)
	{
	case L'\'':c=0x27;break;
	case L'\"':c=0x22;break;
	case L'?':c=0x3f;break;
	case L'a':c=0x07;break;
	case L'b':c=0x08;break;
	case L'f':c=0x0c;break;
	case L'n':c=0x0a;break;
	case L'r':c=0x0d;break;
	case L't':c=0x09;break;
	case L'v':c=0x0b;break;
	}

	if(c)
	{
		begin++;
		return c;
	}

	//到这里一定非空
	if(*begin==L'x')
	{
		begin++;
		if(begin==end||!ishexdigit(*begin))
		{
			/*报错*/
			return 0;
		}
		for(s2 i=0;i<2;i++)
		{
			if(begin<end&&ishexdigit(*begin))
				c=c<<4|hextox(*begin++);
			else
				return c;
		}
		return c;
	}
	else if(isodigit(*begin))
	{
		for(s2 i=0;i<3;i++)
		{
			if(begin<end&&isodigit(*begin)&&c<16)
				c=c<<3|(*begin++ -L'0');
			else
				return c;
		}
		return c;
	}
	else
	{
		/*报转义非法错误*/
		return 0;
	}
	
}

Unit::Unit(Unit_T type,s2 line,s2 col) noexcept
	:type(type),line(line),col(col)
{}

Symbol::Symbol(const Code_Char* begin,const Code_Char* end,Compiler&compiler)
	:Unit(Unit_T::Symbol,begin->line,begin->col)
{
	
}


Literal::Literal(Literal_T type,s2 line,s2 col) noexcept
	:Unit(Unit_T::Literal,line,col),type(type)
{}


String_Literal::String_Literal(const Code_Char* begin,const Code_Char* end,Compiler&compiler)
	:Literal(Literal_T::String,begin->line,begin->col)
{
	String_T type=String_T::String;
	if(*begin==L'L')type=String_T::Wstring,begin++;

	s2 len=0;

	for(Code_Char_Reader reader{begin+1,end-1};!reader.empty();)
	{
		wchar_t c=reader();
		if(c>=0&&c<=127||type==String_T::Wstring)
			len++;
		else
			len+=2;
	}

	Code_Char_Reader reader{begin+1,end-1};

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
	for(Code_Char_Reader reader{begin+1,end-1};!reader.empty();)
	{
		c=reader();
		if(c>=0&&c<=127||type==Char_T::Wchar)
			len++;
		else
			len+=2;
		if(len>=2)break;
	}

	if(len!=1){/*报错*/}


	this->type=type;
	if(type==Char_T::Char)
	{
		if(c>=0&&c<=127)
			this->c=c;
		else
			/*报错*/;
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

	auto read_val=[this,&compiler](const Code_Char*&begin,const Code_Char*end)->__uint128_t
	{

		__uint128_t x=0;

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
			while(begin<end&&isbdigit(*begin))
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
			while(begin<end&&ishexdigit(*begin))
			{
				if((x>>64)==0)
					x=x*16+hextox(*begin);
				begin++;
			}
		}
		//八进制
		else
		{
			while(begin<end&&isodigit(*begin))
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
			/*报错*/
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

		/*报错*/

		return Integer_T::Int16;
	};

	auto auto_type=[this,&compiler](__uint128_t x)->Integer_T
	{
		if((x>>31)==0)return Integer_T::Int32;
		if((x>>63)==0)return Integer_T::Int64;
		return Integer_T::Uint64;
	};

	__uint128_t x=read_val(begin,end);

	if(x>>64)
	{
		/*数值过大，报错*/
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

}
Word::Word(const Code_Char* begin,const Code_Char* end,Compiler&compiler)
	:Unit(Unit_T::Word,begin->line,begin->col)
{

}

Code_Char::operator wchar_t () const noexcept
{
	return c;
}

Compiler_A::Compiler_A(Mem::SA&sa):
	symbol_a(sa),
	integer_a(sa),
	float_a(sa),
	string_a(sa),
	char_a(sa),
	word_a(sa)
{}

s2 isdigit(wchar_t c)
{
	return c>=L'0'&&c<=L'9';
}

s2 isbdigit(wchar_t c)
{
	return c>=L'0'&&c<=L'1';
}

s2 isodigit(wchar_t c)
{
	return c>=L'0'&&c<=L'7';
}

s2 ishexdigit(wchar_t c)
{
	return isdigit(c)||c>=L'a'&&c<=L'f'||c>=L'A'||c>=L'F';
}

s2 hextox(wchar_t c)
{
	if(c>=L'0'&&c<=L'9')return c-L'0';
	if(c>=L'a'&&c<=L'f')return c-L'a'+10;
	return c-L'A'+10;
}


Mem_Seg::Mem_Seg() noexcept
	:p_mem(0)
{
	memset(mem,0,sizeof mem);
}

template<s2 align>
u0* Mem_Seg::alloc(s2 sz)
{
	static_assert(align==1||align==2||align==4||align==8);

	p_mem=(p_mem+align-1)/align;
	s2 res=max_mem_size-p_mem;
	if(res>=sz)
	{
		p_mem+=sz;
		return mem+p_mem-sz;
	}
	else
	{
		/*报错：内存超限*/
		return mem;
	}
}

Compiler::Compiler(std::wstring code_,Compiler_A&a):
	a(&a)
{
	code.reserve(code_.length());
	s2 line=1;
	s2 col=1;
	for(wchar_t c:code_)
	{
		code.emplace_back(c,line,col);
		if(c==L'\n')line++,col=1;
		else col++;
	}
}

s2 Compiler::compile_init()
{
	//清空各种辅助
	return 0;
}

s2 Compiler::extract()         //翻译阶段1，提取合法字符，不考虑三标符
{
	struct Check
	{
		s0 ok[128];
		constexpr Check()
		{
			//清空表
			for(s2 i=0;i<128;i++)ok[i]=0;  

			//数字，字母
			for(s2 i='0';i<='9';i++)
				ok[i]=1;
			for(s2 i='a';i<='z';i++)
				ok[i]=1;
			for(s2 i='A';i<='Z';i++)
				ok[i]=1;

			//空白字符：空格，水平制表符，垂直制表符，换行，换页
			ok[32]=ok[9]=ok[11]=ok[10]=ok[12]=1;

			//其他：_{}[]#()<>%:;.?*+-/^&|~!=,\"'
			ok['_']=ok['{']=ok['}']=ok['[']=ok[']']=
			ok['#']=ok['(']=ok[')']=ok['<']=ok['>']=
			ok['%']=ok[':']=ok[';']=ok['.']=ok['?']=
			ok['*']=ok['+']=ok['-']=ok['/']=ok['^']=
			ok['&']=ok['|']=ok['~']=ok['!']=ok['=']=
			ok[',']=ok['\\']=ok['\"']=ok['\'']=1;

		}

		//检查是否是合法字符
		s2 operator()(wchar_t c) const
		{
			if(c>=0&&c<=127)return ok[c];
			//非ASCII字符一律合法
			else return 1;
		}
	};
	static constexpr Check check;

	s2 len=code.size();
	s2 j=0;

	for(s2 i=0;i<len;i++)
	{
		auto c=code[i];
		if(check(c))code[j++]=c;
		else {/*报警告*/};
	}

	code.resize(j);
	return 0;
}

s2 Compiler::merge_line()     //翻译阶段2，合并斜杠和换行符号为空
{
	s2 len=code.size();
	s2 j=0;
	for(s2 i=0;i<len;i++)
	{
		//删掉斜杠换行组合
		if(i+1<len&&code[i]==L'\\'&&code[i+1]==L'\n')
			i++;
		else
			code[j++]=code[i];
	}

	code.resize(j);

	return 0;
}

s2 Compiler::remove_note()    //去注释    翻译阶段3
{
	s2 len=code.size();
	s2 j=0,i=0;
	while(i<len)
	{
		if(i<len-1&&code[i]==L'/'&&code[i+1]==L'/')
		{
			code[j++]={L' ',0,0};
			i+=2;
			while(i<len&&code[i]!=L'\n')
				i++;
		}
		else if(i<len-1&&code[i]==L'/'&&code[i+1]==L'*')
		{
			code[j++]={L' ',0,0};
			i+=2;
			while(i<len-1&&!(code[i]==L'*'&&code[i+1]==L'/'))
				i++;
			if(i==len-1)     //错误，注释符号没有匹配
			{
				/*报错*/
				return 1;
			}

			i+=2;
		}
		else if(code[i]==L'\"')
		{
			code[j++]=code[i++];
			while(i<len&&!(code[i-1]!=L'\\'&&code[i]==L'\"'))
				code[j++]=code[i++];
			if(i==len)   //错误，双引号不匹配
			{
				/*报错*/
				return 1;
			}

			code[j++]=code[i++];
		}
		else if(code[i]==L'\'')
		{
			code[j++]=code[i++];
			while(i<len&&!(code[i-1]!=L'\\'&&code[i]==L'\''))
				code[j++]=code[i++];
			if(i==len)   //错误，单引号不匹配
			{
				/*报错*/
				return 1;
			}

			code[j++]=code[i++];
		}
	}
	return 0;
}

s2 Compiler::empty_char()
{
	for(auto& c:code)
		if(c>=9&&c<=12)c.c=32;
	return 0;
}


s2 Compiler::split()
{
	//拆分成单元
	s2 len=code.size();

	auto scan_word=[this,len](s2 i)
	{
		struct Check
		{
			s0 ok[128];
			constexpr Check()
			{
				//清空表
				for(s2 i=0;i<128;i++)ok[i]=0;  

				//数字，字母
				for(s2 i='0';i<='9';i++)
					ok[i]=1;
				for(s2 i='a';i<='z';i++)
					ok[i]=1;
				for(s2 i='A';i<='Z';i++)
					ok[i]=1;
				ok['_']=1;

			}

			//检查是否是合法字符
			s2 operator()(wchar_t c) const
			{
				if(c>=0&&c<=127)return ok[c];
				//非ASCII字符一律合法
				else return 1;
			}
		};
		static constexpr Check check;

		if(check(code[i])&&!isdigit(code[i]))i++;
		else return i;

		while(i<len&&check(code[i]))i++;
		return i;
	};
	auto scan_string_literal=[this,len](s2 i)
	{
		if(!(code[i]==L'\"'||i+1<len&&code[i]==L'L'&&code[i+1]=='\"'))return i;

		if(code[i]==L'L')i+=2;
		else i++;

		while(i<len&&code[i]!=L'\"')i++;
		if(code[i]!=L'\"'){/*报错*/};
		return i;
	};
	auto scan_char_literal=[this,len](s2 i)
	{
		if(!(code[i]==L'\''||i+1<len&&code[i]==L'L'&&code[i+1]=='\''))return i;

		if(code[i]==L'L')i+=2;
		else i++;

		while(i<len&&code[i]!=L'\'')i++;
		if(code[i]!=L'\''){/*报错*/};
		return i;
	};
	auto scan_integer_literal=[this,len](s2 i)
	{
		struct Check
		{
			s0 ok[128];
			constexpr Check()
			{
				//清空表
				for(s2 i=0;i<128;i++)ok[i]=0;  

				//数字，字母
				for(s2 i='0';i<='9';i++)
					ok[i]=1;
				for(s2 i='a';i<='z';i++)
					ok[i]=1;
				for(s2 i='A';i<='Z';i++)
					ok[i]=1;
				ok['_']=1;

			}

			//检查是否是合法字符
			s2 operator()(wchar_t c) const
			{
				if(c>=0&&c<=127)return ok[c];
				//非ASCII字符一律合法
				else return 1;
			}
		};
		static constexpr Check check;

		s2 ti=i;

		if(!isdigit(code[i]))return i;

		i++;
		while(i<len&&check(code[i]))
		{
			if(check(code[i]))
				i++;
			else if(code[i]==L'.')
				return ti;
			else break;
		}

		return i;
	};
	auto scan_float_literal=[this,len](s2 i)
	{
		struct Check
		{
			s0 ok[128];
			constexpr Check()
			{
				//清空表
				for(s2 i=0;i<128;i++)ok[i]=0;  

				//数字，字母
				for(s2 i='0';i<='9';i++)
					ok[i]=1;
				for(s2 i='a';i<='z';i++)
					ok[i]=1;
				for(s2 i='A';i<='Z';i++)
					ok[i]=1;
				ok['_']=1;
				ok['.']=1;
			}

			//检查是否是合法字符
			s2 operator()(wchar_t c) const
			{
				if(c>=0&&c<=127)return ok[c];
				//非ASCII字符一律合法
				else return 1;
			}
		};
		static constexpr Check check;

		if(!(isdigit(code[i])||code[i]==L'.'))return i;

		i++;
		while(i<len&&check(code[i]))i++;

		return i;
	};
	auto scan_symbol=[this,len](s2 i)
	{
		struct Check
		{
			s0 ok[128];
			constexpr Check()
			{
				//清空表
				for(s2 i=0;i<128;i++)ok[i]=0;  

				//数字，字母
				for(s2 i='0';i<='9';i++)
					ok[i]=1;
				for(s2 i='a';i<='z';i++)
					ok[i]=1;
				for(s2 i='A';i<='Z';i++)
					ok[i]=1;

				//空白字符：空格，水平制表符，垂直制表符，换行，换页
				ok[32]=ok[9]=ok[11]=ok[10]=ok[12]=1;

				//其他：_{}[]#()<>%:;.?*+-/^&|~!=,\"'
				ok['_']=ok['{']=ok['}']=ok['[']=ok[']']=
				ok['(']=ok[')']=ok['<']=ok['>']=ok['%']=
				ok[':']=ok[';']=ok['.']=ok['?']=ok['*']=
				ok['+']=ok['-']=ok['/']=ok['^']=ok['&']=
				ok['|']=ok['~']=ok['!']=ok['=']=ok[',']=1;

			}

			//检查是否是合法字符
			s2 operator()(wchar_t c) const
			{
				if(c>=0&&c<=127)return ok[c];
				//非ASCII字符一律非法
				else return 0;
			}
		};
		static constexpr Check check;
		auto dfa_status=symbol_dfa.init_status();

		while(check(code[i])&&dfa_status(code[i]))
		{
			dfa_status=dfa_status(code[i]);
			i++;
		}

		return i;
	};

	s2 i=0;
	auto scan=[this,&i](auto&scaner,auto&allocor)->s2
	{
		s2 j=scaner(i);
		if(j>i)
		{
			units.push_back(allocor(&code[i],&code[j],*this));
			return 1;
		}
		return 0;
	};
	while(i<len)
	{

		if(code[i]==L' ')
		{
			i++;
			continue;
		}

		scan(scan_word,a->word_a)||
		scan(scan_string_literal,a->string_a)||
		scan(scan_char_literal,a->char_a)||
		scan(scan_integer_literal,a->integer_a)||
		scan(scan_float_literal,a->float_a)||
		scan(scan_symbol,a->symbol_a)||
		(/*报错*/ i++);

	}

	return 0;
}


s2 Compiler::compile() try
{

	//初始化
	compile_init();

	//提取合法字符
	extract();

	//去注释
	remove_note();

	//空白字符变空格
	empty_char();

	//拆分成单元
	split();

	return 0;
}
catch(...)
{
	return 0;
}

