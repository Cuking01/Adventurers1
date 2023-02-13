#pragma once

struct Source_T;
struct Root_Source_T;
struct Thread_Safe_T;

//类型，源分配器类型,线程安全标志
template<typename T>
struct Allocator;

using RA=Allocator<Root_Source_T>;
using SA=Allocator<Source_T>;

extern RA ra;
