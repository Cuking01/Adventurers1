#pragma once

struct Timed_Val_Buff_Table_A
{
	DS::Map<u2,Timed_Val_Buff>::A map_a;
	Timed_Val_Buff_Table_A(Mem::SA&sa);
};


struct Timed_Val_Buff_Table:DS::Map<u2,Timed_Val_Buff>
{
	State&state;
	Hid hid;
	Timed_Val_Buff_Table(State&state,Hid hid,Timed_Val_Buff_Table_A&a);
	u2 add(BT tag,s2 t,const wchar_t*name=nullptr);
};
