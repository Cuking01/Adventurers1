#pragma once


void Compiler::parse() try     //语法分析
{
	Productions::Stat stat(*this);


	// Productions::Declaration declaration(*this);
	// Productions::Storage_Spec*storage_spec=declaration.storage_spec;
	// Productions::Type_Qualifier*type_qualifier=declaration.type_qualifier;
	// Productions::Type*type=declaration.type;
	// Productions::Declarator*declarator=declaration.declarator;

	// #define print(p,x) {if(p)printf("%d\n",(int)p->x);else printf("null\n");}

	
	// print(storage_spec,symbol);
	// print(type_qualifier,symbol);
	// print(type,t);
	// print(declarator,id);



	// #undef print

	std::wofstream ofs("ast.txt");
	stat.print_ast(0,ofs);
	printf("%u\n",unit_p);
}
catch(std::exception&e)
{
	std::cerr<<e.what()<<'\n';
}

static constexpr bool match_debug_trigger=false;

Unit* Compiler::get_unit() noexcept
{
	if(unit_p<units.size())
		return units[unit_p++];
	return nullptr;
}


template<Symbol_Str symbol_str>
Unit* Compiler::match_symbol_impl() noexcept
{
	auto unit=get_unit();
	if(unit&&unit->type2==Unit_T2::Key&&unit->id==symbol<symbol_str>)
	{
		match_debug_trigger&&printf("  match %u\n",unit_p-1);
		return unit;
	}

	if(unit)unit_p--;
	return nullptr;
}

template<Symbol_Str... symbols>
Unit* Compiler::match_symbol() noexcept
{
	Unit*ret=nullptr;
	((ret=match_symbol_impl<symbols>())||...);
	return ret;
}

void Compiler::unmatch_symbol()
{

	if(unit_p==0)
		throw std::runtime_error("unmatch_symbol:unip_p=0.");
	unit_p--;
	match_debug_trigger&&printf("unmatch %u\n",unit_p);
	if(units[unit_p]->type2!=Unit_T2::Key)
		throw std::runtime_error("unmatch_symbol:unit is not a keyword");
}

Unit* Compiler::match_idt() noexcept
{
	auto unit=get_unit();
	if(unit&&unit->type2==Unit_T2::Identifier)
	{
		match_debug_trigger&&printf("  match %u\n",unit_p-1);
		return unit;
	}
	if(unit)unit_p--;
	return nullptr;
}

void Compiler::unmatch_idt()
{
	if(unit_p==0)
		throw std::runtime_error("unmatch_idt:unip_p=0.");
	unit_p--;
	match_debug_trigger&&printf("unmatch %u\n",unit_p);
	if(units[unit_p]->type2!=Unit_T2::Identifier)
		throw std::runtime_error("unmatch_idt:unit is not an idt");
}

Literal* Compiler::match_literal() noexcept
{
	auto unit=get_unit();
	if(unit&&unit->type==Unit_T::Literal)
	{
		match_debug_trigger&&printf("  match %u\n",unit_p-1);
		return static_cast<Literal*>(unit);
	}
	if(unit)unit_p--;
	return nullptr;
}

void Compiler::unmatch_literal()
{
	if(unit_p==0)
		throw std::runtime_error("unmatch_idt:unip_p=0.");
	unit_p--;
	match_debug_trigger&&printf("unmatch %u\n",unit_p);
	if(units[unit_p]->type!=Unit_T::Literal)
		throw std::runtime_error("unmatch_literal:unit is not a literal");
}
