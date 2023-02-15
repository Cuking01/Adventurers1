#pragma once

struct Skill_A
{
	Attribute_A attribute_a;
	Skill_A(Mem::SA&sa):
		attribute_a(sa)
	{}
};

struct Skill
{
	State&state;
	Hid hid;
	s2 level;
	Attribute AP_use,MP_use;
	Attribute CD_lim;
	Arg_t_7 st;

	f3 CD;

	struct Tag
	{
		u2 default_check:1;
		u2 need_target:1;
		u2 group_restrict:1;
		u2 target_group:1;
		Tag(Base_Config::Skill::Tag tag):
			default_check(tag.default_check),
			need_target(tag.need_target),
			group_restrict(tag.group_restrict),
			target_group(tag.target_group)
		{}
	};
	Tag tag;

	void (*fun_init)(Skill&skill);
	s2   (*fun_check)(Skill&skill,const Arg_t_6&arg);
	void (*fun_use)(Skill&skill,const Arg_t_6&arg);
	
	Skill(State&state,Hid hid,const Base_Config::Skill&skill,s2 level,Skill_A&a):
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

	void init(){if(fun_init)fun_init(*this);}
	
	//0表示正常
	s2 check(const Arg_t_6&arg)
	{
		if(tag.default_check)
		{
			
		}
		return fun_check?fun_check(*this,arg):0;
	}
	void use(const Arg_t_6&arg){fun_use(*this,arg);}

};