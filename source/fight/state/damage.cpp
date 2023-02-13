#pragma once


namespace Damage_Tag
{
	enum T1:u0{直接,间接};
	enum T2:u0{物理,魔法,真实};
	enum T3:u0{单体,群体};
	enum T4:u0{必中=1};
	enum T5:u0{普攻=1};
	enum T6:u0{暴击=1};
};

struct Damage_A
{
	Attribute_A attribute_a;
	Trigger_A<Damage_Handler> trigger_a;
	Damage_A(Mem::SA&sa):
		attribute_a(sa),
		trigger_a(sa)
	{}
};

struct Damage
{
	struct Tag
	{
		u0 直接_间接;
		u0 物理_魔法_真实;
		u0 单体_群体;
		u0 必中;
		u0 普攻;
		u0 暴击;
	};
	Attribute x;
	Hid from,to;
	Trigger<Damage_Handler> addition;
	Attribute 破甲,破魔;
	Tag tag;
	
	Damage(f3 x,Hid from,Hid to,Tag tag,Damage_A&a):
		x(x,a.attribute_a),
		from(from),to(to),
		addition(a.trigger_a),
		破甲(0,a.attribute_a),
		破魔(0,a.attribute_a),
		tag(tag)
	{}

};
