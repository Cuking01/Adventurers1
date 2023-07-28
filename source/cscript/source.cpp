#pragma once

template<typename It_T>
Symbol::Symbol(It_T begin,It_T end)
{

}
template<typename It_T>
String_Literal::String_Literal(It_T begin,It_T end)
{

}
template<typename It_T>
Char_Literal::Char_Literal(It_T begin,It_T end)
{

}
template<typename It_T>
Integer_Literal::Integer_Literal(It_T begin,It_T end)
{

}
template<typename It_T>
Float_Literal::Float_Literal(It_T begin,It_T end)
{

}
template<typename It_T>
Word::Word(It_T begin,It_T end)
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

		if(!isdigit(code[i]))return i;

		i++;
		while(i<len&&check(code[i]))i++;

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

		while(check(code[i]))i++;
		return i;
	};

	s2 i=0;
	auto scan=[this,&i](auto&scaner,auto&allocor)->s2
	{
		s2 j=scaner(i);
		if(j>i)
		{
			units.push_back(allocor(&code[i],&code[j]));
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
		(/*报错*/ 1);

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

