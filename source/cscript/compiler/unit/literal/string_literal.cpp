#pragma once

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
		*mem=0;
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
		*(u1*)mem=0;
	}
}

std::wstring String_Literal::what([[maybe_unused]] const Compiler&compiler) const
{
	return std::format(L"string literal: {:s}",(wchar_t*)p);
}