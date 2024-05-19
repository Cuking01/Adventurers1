#pragma once

struct Storage_Spec:Production<Storage_Spec>
{
	static constexpr Name_Str name="storage_spec";
	using Me=Symbol_Set<"static","typedef">;
	Me::Handler handler;
	Storage_Spec(Compiler&compiler):Production(compiler)
	{
		is_matched=handler=Me::match(compiler);
	};

	void print_ast(u2 dep,std::wostream&o)
	{
		print_tree(dep,o);
		o<<name<<'\n';
		handler->print_ast(dep+1,o);
	}
};

struct Type_Qualifier:Production<Type_Qualifier>
{
	static constexpr Name_Str name="type_qualifier";
	using Me=Symbol_Set<"const">;
	Me::Handler handler;
	Type_Qualifier(Compiler&compiler):Production(compiler)
	{
		is_matched=handler=Me::match(compiler);
	};

	void print_ast(u2 dep,std::wostream&o)
	{
		print_tree(dep,o);
		o<<name<<'\n';
		handler->print_ast(dep+1,o);
	}
};

struct Type:Production<Type>
{
	static constexpr Name_Str name="type";

	using Basic_Type=Symbol_Set<"int8","int16","int32","int64","uint8","uint16","uint32","uint64","void">;
	using Me=Any<Basic_Type,Idt>;

	Me::Handler handler;

	Type(Compiler&compiler):Production(compiler)
	{
		is_matched=handler=Me::match(compiler);
	}

	void print_ast(u2 dep,std::wostream&o)
	{
		print_tree(dep,o);
		o<<name<<'\n';
		handler->print_ast(dep+1,o);
	}
};

struct Declarator:Production<Declarator>
{
	static constexpr Name_Str name="declarator";

	using T1=Combination<Idt>;
	using T2=Combination<Symbol_Set<"(">,Declarator,Symbol_Set<")">>;
	using T3=Combination<Symbol_Set<"*">,Opt<Type_Qualifier>,Declarator>;
		
	using Beta=Any<T1,T2,T3>;

	using T4=Combination<Symbol_Set<"[">,Opt<Exp>,Symbol_Set<"]">>;
	using T5=Combination<Symbol_Set<"(">,/*Opt<Para_List>,*/Symbol_Set<")">>;

	using Alpha=Any<T4,T5>;

	using Me=Combination<Beta,Repeat<Alpha>>;

	Me::Handler handler;

	Declarator(Compiler&compiler):Production(compiler)
	{
		is_matched=handler=Me::match(compiler);
	}

	void print_ast(u2 dep,std::wostream&o)
	{
		print_tree(dep,o);
		o<<name<<'\n';
		handler->print_ast(dep+1,o);
	}
};

struct Type_Name:Production<Type_Name>
{
	static constexpr Name_Str name="type name";

	// void print_ast(u2 dep,std::wostream&o)
	// {
	// 	print_tree(dep,o);
	// 	o<<name<<'\n';
	// 	handler->print_ast(dep+1,o);
	// }
};

struct Declaration:Production<Declaration>
{

	static constexpr Name_Str name="declaration";
	s2 try_flag[3];

	Storage_Spec::Handler storage_spec;
	Type_Qualifier::Handler type_qualifier;
	Type::Handler type;
	Repeat_1<Declarator>::Handler declarators;

	void try_match(s2 order);
	void try_unmatch(s2 order);
	Declaration(Compiler&compiler);
	~Declaration();

	void try_print_ast(u2 dep,std::wostream&o,s2 order);
	void print_ast(u2 dep,std::wostream&o);
};

