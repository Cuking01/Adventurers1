#pragma once


struct Addr
{

};

#include "compiler/char_set.hpp"
#include "compiler/symbol.hpp"
#include "compiler/code_char.hpp"
#include "compiler/mem_seg.hpp"
#include "compiler/unit.hpp"
#include "compiler/type_system.hpp"
#include "compiler/production.hpp"

s2 hextox(wchar_t c);

using Compiler_A=Mem::MTU_Allocor<Symbol,Integer_Literal,Float_Literal,String_Literal,Char_Literal>;


struct Variable
{
	u2 type;
	Addr addr;
	u2 dep;

};

struct Compiler
{
	using A=Compiler_A;
	using SA=Mem::MTU_SA<A>;
	SA mtu_sa;
	A a;
	std::vector<Code_Char> code;
	std::vector<Unit*> units;

	u2 unit_p=0;

	std::map<std::wstring,s2> identifier_map;
	std::vector<std::wstring> identifier_name_table;

	Type_Tree type_tree;

	std::map<u2,std::stack<Variable>> var_table;
	std::stack<std::vector<u2>> scope_record;
	u2 dep=0;

	std::vector<std::wstring> error;
	void report_error(s2 line,s2 col,std::wstring err);
	void report_error(std::wstring err);

	Mem_Seg mem_code,mem_const,mem_static;



	Compiler(std::wstring code,Mem::SA&sa);

	s2 compile_init();
	s2 add_identifier(std::wstring);
	std::wstring identifier_name(s2 id) const;
	void add_variable(u2 id,Variable info);
	void earse_variable(u2 id);
	Variable* get_variable(u2 id);
	void dep_inc();
	void dep_dec();

	#include "compiler/lexer.hpp"
	#include "compiler/parser.hpp"
	
	s2 pre_process();

	s2 compile();
};



