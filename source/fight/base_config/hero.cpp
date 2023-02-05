#pragma once

struct Hero
{
	const wchar_t* name;
	struct Tag{};
	Tag tag;
	Attribute_Table attribute_table;
	Skill skill[5];

	s2 id() const
	{
		return this-hero;
	}
};

Hero hero[0x300];

s2 hero_init()
{
	#include "hero/0x011_test1.cpp"
	#include "hero/0x012_test2.cpp"

	return 0;
}

s2 hero_init_helper=hero_init();
