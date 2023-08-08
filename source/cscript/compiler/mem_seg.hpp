#pragma once

struct Mem_Seg
{
	Compiler*compiler;
	alignas(std::max_align_t) u0 mem[max_mem_size];
	s2 p_mem;

	Mem_Seg(Compiler*compiler) noexcept;

	template<s2 align>
	u0* alloc(s2 sz);
};


