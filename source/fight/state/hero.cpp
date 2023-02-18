#pragma once

Sp_State_A::Sp_State_A(Mem::SA&sa):
	attribute_a(sa)
{}

Sp_State::Sp_State(Sp_State_A&a):
	眩晕(a.attribute_a),
	沉默(a.attribute_a),
	致盲(a.attribute_a),
	潜行(a.attribute_a),
	嘲讽(a.attribute_a),
	重伤(a.attribute_a),
	免疫(a.attribute_a),
	霸体(a.attribute_a)
{}

Hero_A::Hero_A(Mem::SA&sa):
	attribute_table_a(sa),
	sp_state_a(sa),
	skill_a(sa),
	equipment_a(sa),
	trigger_event_a(sa),
	trigger_damage_handler_a(sa)
{}

Hero::Hero(State&state,Hid hid,const Player_Config::Hero&hero,Hero_A&a):
	Attribute_Table(hero,a.attribute_table_a),
	Sp_State(a.sp_state_a),
	state(state),
	hid(hid),
	alive(1),
	level(hero.level),
	skill
	{
		{state,hid,Base_Config::hero[hero.id].skill[0],hero.skill[0].level,a.skill_a},
		{state,hid,Base_Config::hero[hero.id].skill[1],hero.skill[1].level,a.skill_a},
		{state,hid,Base_Config::hero[hero.id].skill[2],hero.skill[2].level,a.skill_a},
		{state,hid,Base_Config::hero[hero.id].skill[3],hero.skill[3].level,a.skill_a},
		{state,hid,Base_Config::hero[hero.id].skill[4],hero.skill[4].level,a.skill_a},
	},
	equipment
	{
		{state,hid,hero.equipment[0],a.equipment_a},
		{state,hid,hero.equipment[1],a.equipment_a},
		{state,hid,hero.equipment[2],a.equipment_a},
	},
	t_damaged(a.trigger_damage_handler_a),
	t_die(a.trigger_event_a)
{}

void Hero::init()
{
	for(int i=0;i<5;i++)
		skill[i].init();
	for(int i=0;i<3;i++)
		equipment[i].init();
	
	HP=HP_lim();
	MP=MP_init();
	AP=AP_init();
}

auto Hero::die()
{
	auto ret=t_die(state,hid);
	if(ret==0)
		alive=0;
	return ret;
}

void Hero::damaged(f3 x)
{
	HP-=x;
	if(x<eps)die();
}

void Hero::cause_damage(Hid to,f3 x,Damage::Tag tag)
{
	Hid from=hid;
	Damage damage(x,from,to,tag, state.damage_a);

	f3 val=damage.x();

	auto type=damage.tag.物理_魔法_真实;
	if(type==DT::物理)
	{
		damage.破甲.x=state[to].P_res();
		val/=1+0.01*damage.破甲();
	}
	else if(type==DT::魔法)
	{
		damage.破魔.x=state[to].M_res();
		val/=1+0.01*damage.破魔();
	}
	else
	{
		//真实伤害啥也不干
	}

	state[to].damaged(val);
	damage.addition(state,damage);
}

//0:正常释放,正数:技能内部检查不通过,负数:其他
//id参数，0~4表示英雄技能，5~7表示装备技能
s2 Hero::use_skill(s2 id,const Arg_t_6&arg)
{
	if(id>=0&&id<5)
	{
		if(auto ret=skill[id].check(arg);ret)
			return ret;
		skill[id].use(arg);
	}
	else if(id>=5&&id<8)
	{
		if(auto ret=equipment[id-5].check(arg);ret)
			return ret;
		equipment[id-5].use(arg);
	}
	else
	{
		return -1;
	}
	return 0;
}
