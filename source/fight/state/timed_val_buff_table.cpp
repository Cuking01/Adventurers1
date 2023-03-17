#pragma once

Timed_Val_Buff_Table_A::Timed_Val_Buff_Table_A(Mem::SA&sa):
	map_a(sa)
{}

Timed_Val_Buff_Table::Timed_Val_Buff_Table(State&state,Hid hid,Timed_Val_Buff_Table_A&a):
	DS::Map<u2,Timed_Val_Buff>(a.map_a),
	state(state),
	hid(hid)
{}

u2 Timed_Val_Buff_Table::add(BT tag,s2 t,const wchar_t*name)
{
	u2 id=state.gen_id();
	insert(id,Timed_Val_Buff{state,{.tag=tag,.hid=hid,.name=name},t});
	return id;
}
