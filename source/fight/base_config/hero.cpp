#pragma once

s2 Hero::id() const
{
	return this-hero;
}

s2 Hero::check() const
{
	return name!=nullptr;
}

Hero hero[0x300];

s2 hero_init()
{
	#include "hero/!pattern.cpp"
	#include "hero/0x011_test1.cpp"
	#include "hero/0x012_test2.cpp"

	return 0;
}

s2 hero_init_helper=hero_init();
