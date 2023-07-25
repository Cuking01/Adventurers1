#pragma once



Code_Char::operator wchar_t () const noexcept
{
	return c;
}

Compiler_A::Compiler_A(Mem::SA&sa):
	symbol_a(sa),
	integer_a(sa),
	float_a(sa),
	string_a(sa),
	char_a(sa)
{}

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


s2 Compiler::split()
{
	//拆分成单元
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

	//拆分成单元
	split();

	return 0;
}
catch(...)
{
	return 0;
}

