#pragma once

struct Buff_Helper
{
	f3 add;
	f3 sub;
	f3 addp;
	f3 subp;
	Buff_Helper():add(0),sub(0),addp(1),subp(1){}
	f3 operator()(f3 x) const
	{
		return x*addp*subp+add-sub;
	}
};

struct Buff
{
	Arg_t_6 st;
	s2 (*fun)(Attribute&,Buff_Helper&,Arg_t_6&);
	s2 operator()(Attribute&attr,Buff_Helper&bh)
	{
		return fun(attr,bh,st);
	}
};

