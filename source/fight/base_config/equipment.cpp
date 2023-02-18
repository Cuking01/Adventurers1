#pragma once

Equipment::id() const
{
	return this-equipment;
}

Equipment equipment[0x300];

s2 equipment_init()
{

	return 0;
}

s2 equipment_init_helper=equipment_init();
