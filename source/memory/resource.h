#pragma once

extern constexpr u3 al=std::max<u3>(alignof(std::max_align_t),8);

namespace Resource
{
	void*alloc(u3);
	void free(void*);
};
