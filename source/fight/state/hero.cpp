#pragma once

Sp_State_A::Sp_State_A(Mem::SA&sa):
	attribute_a(sa),
	trigger_a(sa)
{}

Sp_State::Sp_State(Sp_State_A&a):

	眩晕(a.attribute_a),
	沉默(a.attribute_a),
	致盲(a.attribute_a),
	潜行(a.attribute_a),
	嘲讽(a.attribute_a),
	重伤(0.0,0.0,1.0,a.attribute_a),
	霸体(a.attribute_a),

	t_眩晕(a.trigger_a),
	t_沉默(a.trigger_a),
	t_致盲(a.trigger_a),
	t_潜行(a.trigger_a),
	t_嘲讽(a.trigger_a),
	t_重伤(a.trigger_a),
	t_霸体(a.trigger_a),

	tq_眩晕(a.trigger_a),
	tq_沉默(a.trigger_a),
	tq_致盲(a.trigger_a),
	tq_潜行(a.trigger_a),
	tq_嘲讽(a.trigger_a),
	tq_重伤(a.trigger_a),
	tq_霸体(a.trigger_a)
{}

#define en_sp(sp_name,正负面)                                                        \
	u2 Hero::en_##sp_name(s2 t,BT::驱散等级_t 驱散等级)                               \
	{                                                                                \
		if(正负面.val==BT::负面.val&&霸体()>eps)return 0;                             \
		s2 num=sp_name.trigger.size();                                               \
                                                                                     \
		u2 id=state.gen_id();                                                        \
		sp_name.add(id,                                                              \
		{                                                                            \
			{.tag={正负面,驱散等级},.hid=hid,.name=PP_CONCAT(L,#sp_name)},            \
			lambda_Buff{bh.add+=1;return 0;}                                         \
		});                                                                          \
                                                                                     \
		state.event_queue.add(state.gen_id(),state.time+t,                           \
		{                                                                            \
			{.st={.I0=(s2)hid,.I4=(s2)id}},                                          \
			lambda_Event{state[Hid(st.I0)].sp_name.erase(st.U4);return 0;}           \
		});                                                                          \
                                                                                     \
		if(num==0)t_##sp_name(state);                                                \
                                                                                     \
		return id;                                                                   \
	}

#define en_正面(sp_name) en_sp(sp_name,BT::正面)
#define en_负面(sp_name) en_sp(sp_name,BT::负面)

PP_FOR_EACH(en_负面,眩晕,沉默,致盲)
PP_FOR_EACH(en_正面,潜行,嘲讽,霸体)

u2 Hero::en_重伤(s2 t,f3 p,BT::驱散等级_t 驱散等级)
{
	if(霸体()>eps)return 0;
	s2 num=重伤.trigger.size();
	t=round(t*(1.0-Con_res()));
	u2 id=state.gen_id();
	重伤.add(id,
	{
		{.st={.D0=p},.tag={BT::负面,驱散等级},.hid=hid,.name=L"重伤"},
		lambda_Buff{if(st.D0>bh.add)bh.add=st.D0;return 0;}
	});

	state.event_queue.add(state.gen_id(),state.time+t,
	{
		{.st={.I0=(s2)hid,.I4=(s2)id}},
		lambda_Event{state[Hid(st.I0)].重伤.erase(st.U4);return 0;}
	});

	if(num==0)t_重伤(state);

	return id;
}

#undef en_负面
#undef en_正面
#undef en_sp

#define cls_sp(sp_name)                                                         \
	void Hero::cls_##sp_name(BT::驱散等级_t 驱散等级)                            \
	{                                                                           \
		s2 num=sp_name.trigger.size();                                          \
		for(auto it=sp_name.trigger.begin();it!=sp_name.trigger.end();)         \
		{                                                                       \
			auto& buff=it->value;                                               \
			if(buff.tag.驱散等级<=驱散等级.val)                                  \
				it=sp_name.trigger.erase(it);                                   \
			else                                                                \
				++it;                                                           \
		}                                                                       \
		if(num&&sp_name.trigger.size()==0)                                      \
			tq_##sp_name(state);                                                \
	}

PP_FOR_EACH(cls_sp,眩晕,沉默,致盲,潜行,嘲讽,重伤,霸体)

#undef cls_sp

#define del_sp(sp_name)                                    \
	void Hero::del_##sp_name(u2 id)                        \
	{                                                      \
		s2 num=sp_name.trigger.size();                     \
		sp_name.erase(id);                                 \
		if(num&&sp_name.trigger.size()==0)                 \
			tq_##sp_name(state);                           \
	}

PP_FOR_EACH(del_sp,眩晕,沉默,致盲,潜行,嘲讽,重伤,霸体)

#undef del_sp

Hero_A::Hero_A(Mem::SA&sa):
	attribute_table_a(sa),
	sp_state_a(sa),
	skill_a(sa),
	equipment_a(sa),
	trigger_event_a(sa),
	trigger_damage_handler_a(sa),
	trigger_skill_handler_a(sa),
	damage_a(sa),
	timed_val_buff_table_a(sa)
{}

Hero::Hero(State&state,Hid hid,const Player_Config::Hero&hero,Hero_A&a):
	Attribute_Table(hero,a.attribute_table_a),
	Sp_State(a.sp_state_a),
	state(state),
	st(),
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
	t_use_skill(a.trigger_skill_handler_a),
	t_die(a.trigger_event_a),
	timed_val_buff_table(state,hid,a.timed_val_buff_table_a)
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

//战报中使用的名称
std::wstring Hero::report_name() const
{
	return fmt::format(L"{:s}({:c},{:d})",Base_Config::hero[id].name,(wchar_t)('A'+hid.gid),hid.pos);
};

void Hero::HP_add(f3 x)
{
	HP+=x;
	f3 lim=HP_lim();
	if(HP>lim)HP=lim;
}
void Hero::MP_add(f3 x)
{
	MP+=x;
	f3 lim=MP_lim();
	if(MP>lim)MP=lim;
}
void Hero::AP_add(f3 x)
{
	AP+=x;
	f3 lim=AP_lim();
	if(AP>lim)AP=lim;
}


void Hero::HP_recover(f3 x){HP_add(x*(1-重伤()));}
void Hero::MP_recover(f3 x){MP_add(x);}
void Hero::AP_recover(f3 x){AP_add(x);}


void Hero::recover()
{
	if(!alive)return;
	HP_recover(HP_re()*0.1);
	MP_recover(MP_re()*0.1);
	if(!(眩晕()>eps))
	{
		f3 profit=exAPre_profit();
		f3 x=AP_re()*profit+Base_Config::hero[id].attribute_table.AP_re(level)*(1-profit);
		if(x<0)x=0;
		AP_recover(x*0.1);
	}
	for(s1 sid=0;sid<5;sid++)
		skill[sid].CD_recover();
	for(s1 eid=0;eid<3;eid++)
		equipment[eid].CD_recover();
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
	f3 val=damage();
	Damage damage_tmp(state,val,damage.from,damage.to,damage.crt,damage.tag,state.damage_a);

	val=damage_tmp();

	state.report.write(fmt::format(L"{:s} 受到了 {:.2f} 点伤害\n",report_name(),val));
	HP-=val;
	if(HP<eps)die();
	else t_damaged(state,damage_tmp);
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
