#pragma once

Buff_Helper::Buff_Helper():add(0),sub(0),addp(1),subp(1){}
f3 Buff_Helper::operator()(f3 x) const
{
	return x*addp*subp+add-sub;
}
Buff_Base::Tag::Tag(){pn=0;}

s2 Buff::operator()(Attribute&attr,Buff_Helper&bh)
{
	return fun(attr,bh,st);
}
s2 Event::operator()(State&state,Hid hid)
{
	return fun(state,hid,st);
}
s2 Damage_Handler::operator()(State&state,Damage&damage)
{
	return fun(state,damage,st);
}
