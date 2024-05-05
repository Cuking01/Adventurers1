#pragma once

Float_Literal::Float_Literal(const Code_Char* begin,const Code_Char* end,Compiler&compiler)
	:Literal(Literal_T::Float,begin->line,begin->col)
{
	if(end-begin>1000)
	{
		compiler.report_error(line,col,L"浮点字面量过长");
		this->type=Float_T::F32;
		this->f32=0;
		return;
	}

	auto type=Float_T::F64;
	if(*(end-1)==L'f')
	{
		type=Float_T::F32;
		end--;
	}

	s2 cnt_point=0;
	s2 flag_other=0;
	char tmp[1001];

	for(s2 i=0;begin+i<end;i++)
	{
		if(begin[i]==L'.')cnt_point++;
		else if(!isdigit(begin[i]))flag_other=1;
		tmp[i]=(char)begin[i].c;
	}

	if(flag_other)
	{
		compiler.report_error(line,col,L"浮点字面量格式错误");
	}

	this->type=type;
	if(type==Float_T::F64)
		sscanf(tmp,"%lf",&this->f64);
	else
		sscanf(tmp,"%f",&this->f32);

}

std::wstring Float_Literal::what([[maybe_unused]] const Compiler&compiler) const
{
	return std::format(L"float_literal: {:s} {:f}",type==Float_T::F32?L"F32":L"F64",type==Float_T::F32?f32:f64);
}
