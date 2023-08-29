#pragma once

s2 Compiler::extract()         //翻译阶段1，提取合法字符，不考虑三标符
{
	s2 len=code.size();
	s2 j=0;

	for(s2 i=0;i<len;i++)
	{
		auto c=code[i];
		if(cscript_char_set(c))code[j++]=c;
		else {report_error(code[i].line,code[i].col,L"非法字符");};
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
		s2 err_line=code[i].line;
		s2 err_col=code[i].col;
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
				report_error(err_line,err_col,L"注释符号不匹配");
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
				report_error(err_line,err_col,L"双引号不匹配");
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
				report_error(err_line,err_col,L"单引号不匹配");
				return 1;
			}

			code[j++]=code[i++];
		}
		else
		{
			code[j++]=code[i++];
		}
	}
	return 0;
}

s2 Compiler::empty_char()
{
	s2 len=code.size();
	s2 i=0;
	while(i<len)
	{
		if(code[i]==L'\"')
		{
			i++;
			while(i<len&&!(code[i-1]!=L'\\'&&code[i]==L'\"'))i++;
			i++;
		}
		else if(code[i]==L'\'')
		{
			i++;
			while(i<len&&!(code[i-1]!=L'\\'&&code[i]==L'\''))i++;
			i++;
		}
		else if(blank(code[i]))
		{
			code[i++].c=32;
		}
		else i++;
	}
	return 0;
}


s2 Compiler::split()
{
	//拆分成单元
	s2 len=code.size();

	auto scan_word=[this,len](s2 i)
	{
		if(word_char(code[i])&&!digit(code[i]))i++;
		else return i;

		while(i<len&&word_char(code[i]))i++;
		return i;
	};
	auto scan_string_literal=[this,len](s2 i)
	{
		s2 err_line=code[i].line;
		s2 err_col=code[i].col;
		if(!(code[i]==L'\"'||i+1<len&&code[i]==L'L'&&code[i+1]=='\"'))return i;

		if(code[i]==L'L')i+=2;
		else i++;

		while(i<len&&!(code[i-1]!=L'\\'&&code[i]==L'\"'))i++;
		
		if(code[i]!=L'\"'){report_error(err_line,err_col,L"双引号不匹配");};
		return i+1;
	};
	auto scan_char_literal=[this,len](s2 i)
	{
		s2 err_line=code[i].line;
		s2 err_col=code[i].col;
		if(!(code[i]==L'\''||i+1<len&&code[i]==L'L'&&code[i+1]=='\''))return i;

		if(code[i]==L'L')i+=2;
		else i++;

		while(i<len&&!(code[i-1]!=L'\\'&&code[i]==L'\''))i++;
		if(code[i]!=L'\''){report_error(err_line,err_col,L"单引号不匹配");};
		return i+1;
	};
	auto scan_integer_literal=[this,len](s2 i)
	{
		s2 ti=i;

		if(!digit(code[i]))return i;

		i++;
		while(i<len)
		{
			if(word_char(code[i]))
				i++;
			else if(code[i]==L'.')
				return ti;
			else break;
		}

		return i;
	};
	auto scan_float_literal=[this,len](s2 i)
	{
		static constexpr Char_Set check=word_char|Char_Set{'.'};

		if(!(digit(code[i])||code[i]==L'.'))return i;

		i++;
		while(i<len&&check(code[i]))i++;

		return i;
	};
	auto scan_symbol=[this,len](s2 i)
	{
		
		auto dfa_status=symbol_dfa.init_status();

		s2 max_i=i;

		while(punctuation(code[i])&&dfa_status(code[i]))
		{

			dfa_status=dfa_status(code[i]);
			if(dfa_status.id())max_i=i;
			i++;
		}

		return max_i+1;
	};

	s2 i=0;
	auto scan=[this,&i](auto scaner,auto constructor)->s2
	{
		s2 j=scaner(i);
		if(j>i)
		{
			units.push_back(constructor(&code[i],&code[j],*this));
			i=j;
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
		scan(scan_string_literal,a.get_constructor<String_Literal>())||
		scan(scan_char_literal,a.get_constructor<Char_Literal>())||
		scan(scan_word,a.get_constructor<Symbol>())||
		scan(scan_integer_literal,a.get_constructor<Integer_Literal>())||
		scan(scan_float_literal,a.get_constructor<Float_Literal>())||
		scan(scan_symbol,a.get_constructor<Symbol>())||
		(report_error(code[i].line,code[i].col,L"未知错误"),i++);
	}
	return 0;
}

s2 Compiler::merge_string()
{
	
	return 0;
}

s2 Compiler::lex()
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
	//合并字符串字面量
	merge_string();

	return 0;
}
