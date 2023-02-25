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
	trigger_damage_handler_a(sa),
	damage_a(sa)
{}

Hero::Hero(State&state,Hid hid,const Player_Config::Hero&hero,Hero_A&a):
	Attribute_Table(hero,a.attribute_table_a),
	Sp_State(a.sp_state_a),
	state(state),
	id(hero.id),
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
	t_damage(a.trigger_damage_handler_a),
	t_before_damaged(a.trigger_damage_handler_a),
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

void Hero::HP_recover(f3 x)
{
	HP+=x;
	f3 lim=HP_lim();
	if(HP>lim)HP=lim;
}

void Hero::MP_recover(f3 x)
{
	MP+=x;
	f3 lim=MP_lim();
	if(MP>lim)MP=lim;
}

void Hero::AP_recover(f3 x)
{
	AP+=x;
	f3 lim=AP_lim();
	if(AP>lim)AP=lim;
}

void Hero::recover()
{
	HP_recover(HP_re()*0.1);
	MP_recover(MP_re()*0.1);
	if(!眩晕())
	{
		f3 x=(AP_re()-AP_re.x)*exAPre_profit();
		if(x<0)x=0;
		AP_recover(x*0.1);
	}
}

s2 Hero::die()
{
	auto ret=t_die(state);
	if(ret==0)
		alive=0;
	return ret;
}

s2 Hero::damaged(Damage&damage)
{

	HP-=damage();
	if(HP<eps)die();
	return 0;
}



Damage& Hero::make_damage(Hid to,f3 x,Damage::Tag tag)
{
	Hid from=tag.无来源?Hid(-1):hid;

	u2 crt=state.gen_bool(tag.可暴击?state[hid].Crt():0.0);
	Damage& damage=*state.damage_pool(state,x,from,to,crt,tag,state.damage_a);

	t_damage(state,damage);

	return damage;
}

s2 Hero::cause_damage(Hid to,f3 x,Damage::Tag tag)
{
	Damage& damage=make_damage(to,x,tag);
	s2 ret=damage.act();
	damage.destroy();
	return ret;
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
