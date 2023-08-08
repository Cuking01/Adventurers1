#pragma once

Code_Char::operator wchar_t () const noexcept
{
	return c;
}

Code_Char_Reader::Code_Char_Reader(const Code_Char*begin,const Code_Char* end,Compiler&compiler) noexcept
	:begin(begin),end(end),compiler(&compiler)
{}

s2 Code_Char_Reader::empty() const noexcept
{
	return begin==end;
}

wchar_t Code_Char_Reader::operator()() 
{
	if(empty())
		throw std::runtime_error("Code_Char_Reader:empty.");
	//非转义字符
	if(*begin!=L'\\')
		return *begin++;

	s2 line=begin->line,col=begin->col;

	begin++;
	if(begin==end)
	{
		compiler->report_error(line,col,L"转义格式错误");
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
		if(begin==end||!hexdigit(*begin))
		{
			compiler->report_error(line,col,L"转义格式错误");
			return 0;
		}
		for(s2 i=0;i<2;i++)
		{
			if(begin<end&&hexdigit(*begin))
				c=c<<4|hextox(*begin++);
			else
				return c;
		}
		return c;
	}
	else if(odigit(*begin))
	{
		for(s2 i=0;i<3;i++)
		{
			if(begin<end&&odigit(*begin)&&c<16)
				c=c<<3|(*begin++ -L'0');
			else
				return c;
		}
		return c;
	}
	else
	{
		compiler->report_error(line,col,L"转义格式错误");
		return 0;
	}
	
}
