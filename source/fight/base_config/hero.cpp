#pragma once

struct Hero
{
	const wchar_t* name;
	const wchar_t* description;
	struct Tag{};
	Tag tag;
	Attribute_Table attribute_table;
	Skill skill[5];

	s2 id() const
	{
		return this-hero;
	}
	s2 check() const
	{
		return name!=nullptr;
	}
};

Hero hero[0x300];

s2 hero_init()
{
	#include "hero/!pattern.cpp"
	#include "hero/0x011_test1.cpp"
	#include "hero/0x012_test2.cpp"

	return 0;
}

s2 hero_init_helper=hero_init();
