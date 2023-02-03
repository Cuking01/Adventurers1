#pragma once

struct Skill
{
	wchar_t name[32];
	wchar_t description[1024];
	Attribute_Table exAttribute;
	Attribute cd,cd_init;
	Attribute AP_use,MP_use;

	typedef void(*Callback_Fun)(State::State&state,State::Group&group,State::Hero&hero,State::Skill&skill);
	Callback_Fun init,use,heck;

	struct Tag
	{
		u2 default_target_check:1;
		u2 need_target:1;
		u2 group_restrict:1;
		u2 target_group:1;
	};
	Tag tag;
};
