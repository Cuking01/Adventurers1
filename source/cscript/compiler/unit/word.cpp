#pragma once

Word::Word(const Code_Char* begin,const Code_Char* end,Compiler&compiler)
	:Unit(Unit_T::Word,begin->line,begin->col)
{
	s2 len=end-begin;
	if(len>100)
	{
		compiler.report_error(line,col,L"标识符过长");
		this->type=Word_T::Identifier;
		this->x=0;
		return;
	}

	auto dfa_status=symbol_dfa.init_status();

	while(begin<end)
		dfa_status=dfa_status(*begin++);
	
	if(dfa_status.id())
	{
		this->type=Word_T::Key;
		this->x=dfa_status;
		return;
	}

	std::wstring word{begin,end};

	auto it=compiler.identifier_map.find(word);
	if(it==compiler.identifier_map.end())
	{
		s2 id=compiler.identifier_map.size();
		compiler.identifier_map[word]=id;
		compiler.identifier_name.push_back(word);
	}

	this->type=Word_T::Identifier;
	this->x=compiler.identifier_map[word];

}

