#pragma once

struct Source_T{};//此类型表示内部节点
struct Thread_Safe_T{};//线程安全标识，注意仅保证分配和解分配安全，构造，赋值等操作则不


//根内存分配器类型与根内存分配器
#include "allocator/allocator_ra.cpp"

//源内存分配器类型
#include "allocator/allocator_sa.cpp"
#include "allocator/allocator_sa_ts.cpp"

//一般分配器类型
#include "allocator/allocator_T.cpp"
#include "allocator/allocator_T_ts.cpp"
