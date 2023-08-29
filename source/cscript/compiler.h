#pragma once

constexpr s2 max_code_length=65536;
constexpr s2 max_mem_size=1<<20;//1MiB
/*
	内存结构，总共1MiB，从小到大为：
	1KiB保留区，禁止用户读写
	不定长代码区
	不定长常量区
	不定长全局（静态）区
	不定长自由区（堆区）
	64KiB栈区

*/

#include "compiler/char_set.h"
#include "compiler/symbol.h"
#include "compiler/code_char.h"
#include "compiler/mem_seg.h"
#include "compiler/unit.h"
#include "compiler/lexer.h"

struct Compiler;

