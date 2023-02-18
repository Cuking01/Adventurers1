#pragma once

Skill_A::Skill_A(Mem::SA&sa):
	attribute_a(sa)
{}

Skill::Tag::Tag(Base_Config::Skill::Tag tag):
			default_check(tag.default_check),
			need_target(tag.need_target),
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

//0表示正常
s2 Skill::check(const Arg_t_6&arg)
{
	if(tag.default_check)
	{
		
	}
	return fun_check?fun_check(*this,arg):0;
}
void Skill::use(const Arg_t_6&arg){fun_use(*this,arg);}
