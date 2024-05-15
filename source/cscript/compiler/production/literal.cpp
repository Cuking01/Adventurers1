#pragma once

Literal::Literal(Compiler&compiler):Production(compiler)
{
	auto*p=compiler.match_literal();
	if(p)
	{
		literal=static_cast<::Cscript::Literal*>(literal);
		is_matched=true;
	}
}

Literal::~Literal()
{
	if(is_matched)
		compiler->unmatch_literal();
}
