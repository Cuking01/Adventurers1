#pragma once


void Compiler::parse()     //语法分析
{
	Productions::Declaration declaration(*this);
	Productions::Storage_Spec*storage_spec=declaration.storage_spec;
	Productions::Type_Qualifier*type_qualifier=declaration.type_qualifier;
	Productions::Type*type=declaration.type;
	Productions::Declarator*declarator=declaration.declarator;

	#define print(p,x) {if(p)printf("%d",(int)p->x);else printf("null\n");}

	
	print(storage_spec,type);
	print(type_qualifier,type);
	print(type,t);
	print(declarator,idt);

	#undef print
}

Unit* Compiler::get_unit() noexcept
{
	if(unit_p<units.size())
		return units[unit_p++];
	return nullptr;
}


template<Symbol_Str symbol_str>
Unit* Compiler::match_symbol() noexcept
{
	auto unit=get_unit();
	if(unit&&unit->type2==Unit_T2::Key&&unit->id==symbol<symbol_str>)
		return unit;

	if(unit)unit_p--;
	return nullptr;
}

template<Symbol_Str... symbols,typename... Callbacks>
Unit* Compiler::match_symbol(Callbacks&&...callbacks) noexcept
{
	Unit*ret=nullptr;
	(((ret=match_symbol<symbols>())&&(callbacks(),true))||...);
	return ret;
}

void Compiler::unmatch_symbol()
{
	if(unit_p==0)
		throw std::runtime_error("unmatch_symbol:unip_p=0.");
	unit_p--;
	if(units[unit_p]->type2!=Unit_T2::Key)
		throw std::runtime_error("unmatch_symbol:unit is not a keyword");
}

Unit* Compiler::match_idt() noexcept
{
	auto unit=get_unit();
	if(unit&&unit->type2==Unit_T2::Identifier)
		return unit;
	if(unit)unit_p--;
	return nullptr;
}

void Compiler::unmatch_idt()
{
	if(unit_p==0)
		throw std::runtime_error("unmatch_idt:unip_p=0.");
	unit_p--;
	if(units[unit_p]->type2!=Unit_T2::Identifier)
		throw std::runtime_error("unmatch_idt:unit is not an idt");
}
