#pragma once



struct Storage_Spec:Production<Storage_Spec>
{
	enum class Type
	{
		Static,
		Typedef
	};
	Type type;

	Storage_Spec(Compiler&compiler);
	~Storage_Spec();
};

struct Type_Qualifier:Production<Type_Qualifier>
{
	enum class Type
	{
		Const
	};
	Type type;

	Type_Qualifier(Compiler&compiler);
	~Type_Qualifier();
};

struct Type:Production<Type>
{
	u2 t;
	Type(Compiler&compiler);
	~Type();
};

struct Declarator:Production<Declarator>
{
	u2 idt;
	Declarator(Compiler&compiler);
	~Declarator();
};




struct Declaration:Production<Declaration>
{
	s2 idt;

	s2 try_flag[3];

	Storage_Spec::Handler storage_spec;
	Type_Qualifier::Handler type_qualifier;
	Type::Handler type;
	Declarator::Handler declarator;

	void try_match(s2 order);
	void try_unmatch(s2 order);
	Declaration(Compiler&compiler);
	~Declaration();
};

