#pragma once

Damage_A::Damage_A(Mem::SA&sa):
	attribute_a(sa),
	trigger_a(sa)
{}

Damage::Damage(State&state,f3 x,Hid from,Hid to,u2 crt,Tag tag,Damage_A&a):
	state(state),
	x(x,a.attribute_a),
	from(from),to(to),
	addition(a.trigger_a),
	破甲(0,a.attribute_a),
	破魔(0,a.attribute_a),
	crt(crt),
	tag(tag)
{}

f3 Damage::operator()()
{
	f3 val=x();

	auto type=tag.物理_魔法_真实;
	if(type==DT::物理)
	{
		破甲.x=state[to].P_res();
		val/=1+0.01*破甲();
	}
	else if(type==DT::魔法)
	{
		破魔.x=state[to].M_res();
		val/=1+0.01*破魔();
	}
	else
	{
		//真实伤害啥也不干
	}
	return val;
}

s2 Damage::act()
{
	if(s2 ret=state[to].t_before_damaged(state,*this);ret)
		return ret;
	return state[to].damaged(*this);
}

void Damage::destroy()
{
	state.damage_pool<<this;
}
