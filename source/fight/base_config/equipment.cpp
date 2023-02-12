#pragma once

struct Equipment
{
	const wchar_t* name;
	const wchar_t* description;
	Attribute_Table attribute_table;
	Skill skill;

	s2 id() const
	{
		return this-equipment;
	}
};

Equipment equipment[0x300];

s2 equipment_init()
{

	return 0;
}

s2 equipment_init_helper=equipment_init();
