#pragma once

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

std::wstring Char_Literal::what([[maybe_unused]] const Compiler&compiler) const
{
	if(type==Char_T::Wchar)
	{
		return std::format(L"char_literal: wchar {:c}",wc);
	}
	else
	{
		return std::format(L"char_literal: char {:c}",c);
	}
	
}
