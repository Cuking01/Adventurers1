#pragma once

Mem_Seg::Mem_Seg(Compiler*compiler) noexcept
	:compiler(compiler),p_mem(0)
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
		compiler->report_error(L"内存超限");
		return mem;
	}
}


