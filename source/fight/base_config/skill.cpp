#pragma once

struct Skill
{
	const wchar_t* name;
	const wchar_t* description;
	Attribute_Table attribute_table;
	Attribute cd,cd_init;
	Attribute AP_use,MP_use;



	void(*fun_init)([[maybe_unused]] ::Fight::State::Skill&skill);
	s2  (*fun_check)([[maybe_unused]] ::Fight::State::Skill&skill,[[maybe_unused]] const Arg_t_6&arg);
	void(*fun_use)([[maybe_unused]] ::Fight::State::Skill&skill,[[maybe_unused]] const Arg_t_6&arg);
	struct Tag
	{
		u2 default_target_check:1;
		u2 need_target:1;
		u2 group_restrict:1;
		u2 target_group:1;
	};
	Tag tag;
};
