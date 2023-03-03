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
		u0 普攻=0;
		u0 必中=0;
		u0 可暴击=0;
		u0 无来源=0;

		struct Initer
		{
			u0 val;
			void operator()(Tag&tag)=delete;
		};

		#define Initer_(name)                             \
			struct name##_t:Initer                        \
			{                                             \
				void operator()(Tag&tag){tag.name=val;}   \
			};                                            \
			s2 operator()(name##_t x){return name==x.val;}    

		PP_FOR_EACH(Initer_,直接_间接,物理_魔法_真实,单体_群体,普攻,必中,可暴击,无来源)

		#undef Initer_

		struct Value
		{
			static constexpr 直接_间接_t 直接{0u},间接{1u};
			static constexpr 物理_魔法_真实_t 物理{0u},魔法{1u},真实{2u};
			static constexpr 单体_群体_t 单体{0u},群体{1u};
			static constexpr 普攻_t 普攻{1u};
			static constexpr 必中_t 必中{1u};
			static constexpr 可暴击_t 可暴击{1u};
			static constexpr 无来源_t 无来源{1u};
		};

		template<typename... Initers>
		Tag(直接_间接_t initer1,物理_魔法_真实_t initer2,单体_群体_t initer3,Initers... initers)
		{
			static_assert((std::is_base_of_v<Initer,Initers>&&...));
			initer1(*this);
			initer2(*this);
			initer3(*this);
			((initers(*this)),...);
		}

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
	void destroy();
};
