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

	using Basic_Type=Symbol_Set<"int8","int16","int32","int64","uint8","uint16","uint32","uint64","void","integer","double">;
	using Me=Any<Basic_Type,Idt>;

	Me::Handler handler;

	u2 t;

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

	void analyze()
	{
		handler->dispatch_call
		(
			[this](Basic_Type&t1)
			{
				t=0;
				t1.dispatch_call
				(
					[this](){},
					[this](){},
					[this](){},
					[this](){},
					[this](){},
					[this](){},
					[this](){},
					[this](){},
					[this](){},
					[this](){t=2;},
					[this](){t=4;}
				);
			},
			[this](Idt&)
			{
				t=0;
			}
		);
		printf("%d\n",t);
	}
};

struct Declarator:Production<Declarator>
{
	static constexpr Name_Str name="declarator";

	using T1=Idt;
	using T2=Combination<Symbol_Set<"(">,Declarator,Symbol_Set<")">>;
		
	using Pointer=Combination<Symbol_Set<"*">,Opt<Type_Qualifier>>;

	using Beta=Any<T1,T2>;

	using T4=Combination<Symbol_Set<"[">,Opt<Exp>,Symbol_Set<"]">>;
	using T5=Combination<Symbol_Set<"(">,/*Opt<Para_List>,*/Symbol_Set<")">>;

	using Alpha=Any<T4,T5>;

	using Me=Combination<Repeat<Pointer>,Beta,Repeat<Alpha>>;

	Me::Handler handler;
	u2 t;

	Declarator(Compiler&compiler):Production(compiler)
	{
		is_matched=handler=Me::match(compiler);
	}

	void print_ast(u2 dep,std::wostream&o);
	void analyze(u2 type);
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

struct Initialize:Production<Initialize>
{
	static constexpr Name_Str name="initialize";

	using Me=Combination<Symbol_Set<"=">,Expk<14>>;

	Me::Handler handler;
	Initialize(Compiler&compiler):Production(compiler)
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

struct Declaration:Production<Declaration>
{

	static constexpr Name_Str name="declaration";
	s2 try_flag[3];

	Storage_Spec::Handler storage_spec;
	Type_Qualifier::Handler type_qualifier;
	Type::Handler type;

	using Declarator_With_Init=Combination<Declarator,Opt<Initialize>>;
	using Declarators=Combination<Repeat<Combination<Declarator_With_Init,Symbol_Set<",">>>,Declarator_With_Init>;

	Declarators::Handler declarators;

	void try_match(s2 order);
	void try_unmatch(s2 order);
	Declaration(Compiler&compiler);
	~Declaration();

	void try_print_ast(u2 dep,std::wostream&o,s2 order);
	void print_ast(u2 dep,std::wostream&o);
	void analyze();
};

struct Function_Arg_Decl:Production<Function_Arg_Decl>
{
	static constexpr Name_Str name="function arg declaration";
	using T1=Combination<Type,Type_Qualifier>;
	using T2=Combination<Type_Qualifier,Type>;
	using T3=Type;

	using Me=Combination<Any<T1,T2,T3>,Declarator>;

	Me::Handler handler;

	u2 type;

	Function_Arg_Decl(Compiler&compiler):Production(compiler)
	{
		is_matched=handler=Me::match(compiler);
	}

	void analyze();

	void print_ast(u2 dep,std::wostream&o)
	{
		print_tree(dep,o);
		o<<name<<'\n';
		handler->print_ast(dep+1,o);
	}
};
