#pragma once

Attribute_A::Attribute_A(Mem::SA&sa):
	trigger_a(sa)
{}

Attribute::Attribute(A&a):Attribute(0,a){}
Attribute::Attribute(f3 x,A&a):Attribute(x,0,inf,a){}
Attribute::Attribute(f3 x,f3 min,f3 max,A&a):x(x),min(min),max(max),trigger(a.trigger_a){}
void Attribute::add(u2 key,const Buff&buff)
{
	trigger.insert(key,buff);
}
void Attribute::erase(u2 key)
{
	trigger.erase(key);
}
Buff* Attribute::find(u2 key)
{
	return trigger.find(key);
}

f3 Attribute::operator()()
{
	Buff_Helper bh;
	trigger(*this,bh);
	f3 tmp=bh(x);
	return std::max(std::min(tmp,max),min);
}

