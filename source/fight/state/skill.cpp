#pragma once

Skill_A::Skill_A(Mem::SA&sa):
	attribute_a(sa)
{}

Skill::Tag::Tag(Base_Config::Skill::Tag tag):
			consumption_check(tag.consumption_check),
			sp_state_check(tag.sp_state_check),
			target_check(tag.target_check),
			group_restrict(tag.group_restrict),
			target_group(tag.target_group)
		{}

Skill::Skill(State&state,Hid hid,const Base_Config::Skill&skill,s2 level,Skill_A&a):
	state(state),
	hid(hid),
	level(level),
	AP_use(skill.AP_use(level),a.attribute_a),
	MP_use(skill.MP_use(level),a.attribute_a),
	CD_lim(skill.cd(level),a.attribute_a),
	st{},
	CD(skill.cd_init(level)),
	tag{skill.tag},
	fun_init(skill.fun_init),
	fun_check(skill.fun_check),
	fun_use(skill.fun_use)
{}

void Skill::init(){if(fun_init)fun_init(*this);}



s2 Skill::consumption_check()
{
	if(!tag.consumption_check)return 0;
	auto& hero=state[hid];
	if(CD>eps)return 0x01;
	if(AP_use()>hero.AP)return 0x02;
	if(MP_use()*hero.MP_lim()>hero.MP)return 0x03;
	return 0;
}

s2 Skill::sp_state_check()
{
	if(!tag.sp_state_check)return 0;
	auto& hero=state[hid];
	if(hero.眩晕()>eps)return 0x11;
	if(hero.沉默()>eps&&(this-hero.skill)!=1)return 0x12;
	if(hero.致盲()>eps&&(this-hero.skill)==1)return 0x13;
	return 0;
}

s2 Skill::target_check(Hid target)
{
	if(!tag.target_check)return 0;
	if(!target.check())return 0x21;
	if(tag.group_restrict&&target.gid!=tag.target_group)return 0x22;
	if(target.gid==1)
	{
		target.gid^=hid.gid;
		s2 cnt_嘲讽=0;
		for(s2 i=0;i<5;i++)
			cnt_嘲讽+=state[target.gid][i].嘲讽()>eps;
		if(cnt_嘲讽&&state[target].嘲讽()<eps)return 0x23;
	}
	return 0;
}

//0表示正常
s2 Skill::check(const Arg_t_6&arg)
{
	if(auto ret=consumption_check();ret)return ret;
	if(auto ret=sp_state_check();ret)return ret;
	if(auto ret=target_check(arg);ret)return ret;
	return fun_check?fun_check(*this,arg):0;
}
void Skill::use(const Arg_t_6&arg){fun_use(*this,arg);}
