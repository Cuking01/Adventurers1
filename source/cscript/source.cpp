#pragma once


Unit_T Symbol::type() const noexcept {return Unit_T::symbol;}
Unit_T Literal::type() const noexcept {return Unit_T::literal;}
Unit_T Identifier::type() const noexcept {return Unit_T::identifier;}

Compiler::Compiler(std::wstring code,Compiler_A&a):
	a(&a),code(code)
{}

s2 Compiler::compile_init()
{
	//清空各种辅助
	return 0;
}

s2 Compiler::pre_process()
{
	//去注释+
	//执行预处理命令
	return 0;
}

s2 Compiler::split()
{
	//拆分成单元
	return 0;
}
s2 Compiler::compile()
{
	//初始化
	compile_init();
	//预处理
	pre_process();
	//拆分成单元
	split();

	return 0;
}
