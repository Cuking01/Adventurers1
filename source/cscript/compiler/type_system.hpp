#pragma once

enum class Type_T:u2
{
	Void,
	Base,
	Struct,
	Array,
	Pointer,
	Function
};

namespace Type_Descriptions
{
	struct Void
	{

	};
	struct Base
	{
		bool is_signed;
		bool is_integer;
		s2 level;
		std::wstring name;
	};
	struct Struct
	{

	};
	struct Array
	{
		u2 len;
	};
	struct Pointer
	{

	};
	struct Function
	{

	};

	using Description=std::variant<Void,Base,Struct,Array,Pointer,Function>;
};


struct Var_Type
{
	u2 sz;
	u2 align;
	u2 id;

	Type_T t;
	Type_Descriptions::Description description;

	Var_Type*next;

};


struct Type_Tree
{
	struct Node
	{
		Type_Tree*tree;

		Var_Type description;

		std::map<u2,u2> array;
		u2 pointer=0;
		u2 const_pointer=0;
		std::map<std::vector<u2>,u2> function;

		Node(Type_Tree*tree,Var_Type description):tree(tree),description(std::move(description)){}

		void add_array(u2 len)
		{
			if(array.find(len)==array.end())
				array[len]=tree->add_node(
					{
						.sz=description.sz*len,
						.align=description.align,
						.t=Type_T::Array,
						.description=Type_Descriptions::Array{len},
						.next=&this->description
					});
		}


		std::wstring name()
		{
			if(description.t==Type_T::Base)
				return std::get<Type_Descriptions::Base>(description.description).name;
			if(description.t==Type_T::Array)
			{
				u2 len=std::get<Type_Descriptions::Array>(description.description).len;
				if(len==0)
					return tree->get_type_name(description.next->id)+L"[]";
				else
					return tree->get_type_name(description.next->id)+std::format(L"[{}]",len);
			}
			return L"other type";
		}

	};

	std::vector<Node> nodes;

	void check_index(u2 id)
	{
		printf(">>>>%u\n",id);
		if(id==0||id>=nodes.size())
			throw std::runtime_error("check_index:error.");
	}

	u2 get_child_by_array(u2 id,u2 len)
	{
		//if(id==0||id>=nodes.size())throw std::runtime_error("goto_child_by_array:error");
		check_index(id);
		Node&p=nodes[id];
		p.add_array(len);
		return p.array[len];
	}

	u2 get_father(u2 id)
	{
		check_index(id);
		return nodes[id].description.next->id;
	}

	u2 add_node(Var_Type description)
	{
		nodes.emplace_back(this,std::move(description));
		nodes.back().description.id=nodes.size()-1;
		return nodes.size()-1;
	}

	std::wstring get_type_name(u2 id)
	{
		check_index(id);
		return nodes[id].name();
	}

	Type_Tree()
	{
		nodes.reserve(1000);
		nodes.emplace_back(this,Var_Type{.id=0,.next=nullptr});
		nodes.emplace_back(this,
			Var_Type
			{
				.sz=0,
				.align=0,
				.id=1,
				.t=Type_T::Void,
				.description=Type_Descriptions::Void{},
				.next=nullptr
			}
		);

		nodes.emplace_back(this,
			Var_Type
			{
				.sz=4,
				.align=4,
				.id=2,
				.t=Type_T::Base,
				.description=Type_Descriptions::Base{true,true,8,L"integer"},
				.next=nullptr
			}
		);

		nodes.emplace_back(this,
			Var_Type
			{
				.sz=4,
				.align=4,
				.id=3,
				.t=Type_T::Base,
				.description=Type_Descriptions::Base{true,false,9,L"float"},
				.next=nullptr
			}
		);

		nodes.emplace_back(this,
			Var_Type
			{
				.sz=8,
				.align=8,
				.id=4,
				.t=Type_T::Base,
				.description=Type_Descriptions::Base{false,false,10,L"double"},
				.next=nullptr
			}
		);
	}


};


