#pragma once

Symbol::Symbol(const Code_Char* begin,const Code_Char* end,Compiler&compiler)
	:Unit(Unit_T::Symbol,Unit_T2::Key,begin->line,begin->col,-1)
{
	// auto dfa_status=symbol_dfa.init_status();

	// while(begin<end)
	// 	dfa_status=dfa_status(*begin++);


	// if(!(this->x=dfa_status.id()))
	// {
	// 	compiler.report_error(line,col,L"非法符号");
	// }

	s2 len=end-begin;
	if(len>100)
	{
		compiler.report_error(line,col,L"标识符过长");

		this->type2=Unit_T2::Identifier;
		this->id=0;
		return;
	}

	auto dfa_status=symbol_dfa.init_status();

	auto begin_back=begin;

	while(begin<end)
		dfa_status=dfa_status(*begin++);
	
	if(dfa_status.id())
	{
		this->type2=Unit_T2::Key;
		this->id=dfa_status.id();
		return;
	}

	std::wstring word{begin_back,end};

	this->type2=Unit_T2::Identifier;
	this->id=compiler.add_identifier(word);
	
}

std::wstring Symbol::what([[maybe_unused]] const Compiler&compiler) const
{
	if(this->type2==Unit_T2::Identifier)
		return std::format(L"identifier:{:s}",compiler.identifier_name(id));
	else
		return std::format(L"keyword:{:s}",symbol_table[id]);
}
