#pragma once

Symbol::Symbol(const Code_Char* begin,const Code_Char* end,Compiler&compiler)
	:Unit(Unit_T::Symbol,begin->line,begin->col)
{
	auto dfa_status=symbol_dfa.init_status();

	while(begin<end)
		dfa_status=dfa_status(*begin++);


	if(!(this->x=dfa_status.id()))
	{
		compiler.report_error(line,col,L"非法符号");
	}
}
