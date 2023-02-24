#pragma once

namespace Damage_Tag
{
	enum T1:u0{直接,间接};
	enum T2:u0{物理,魔法,真实};
	enum T3:u0{单体,群体};
	enum T4:u0{普攻=1};
	enum T5:u0{必中=1};
	enum T6:u0{可暴击=1};
	enum T7:u0{无来源=1};
};

struct Damage_A
{
	Attribute_A attribute_a;
	Trigger_A<Damage_Handler> trigger_a;
	Damage_A(Mem::SA&sa);
};

struct Damage
{
	struct Tag
	{
		u0 直接_间接;
		u0 物理_魔法_真实;
		u0 单体_群体;
		u0 普攻;
		u0 必中;
		u0 可暴击;
		u0 无来源;
	};
	State&state;
	Attribute x;
	Hid from,to;
	Trigger<Damage_Handler> addition;
	Attribute 破甲,破魔;
	u2 crt;
	Tag tag;
	
	Damage(State&state,f3 x,Hid from,Hid to,u2 crt,Tag tag,Damage_A&a);
	f3 operator()();
	s2 act();
};
