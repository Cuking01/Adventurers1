#pragma once

Damage_A::Damage_A(Mem::SA&sa):
	attribute_a(sa),
	trigger_a(sa)
{}

Damage::Damage(f3 x,Hid from,Hid to,Tag tag,Damage_A&a):
	x(x,a.attribute_a),
	from(from),to(to),
	addition(a.trigger_a),
	破甲(0,a.attribute_a),
	破魔(0,a.attribute_a),
	tag(tag)
{}
