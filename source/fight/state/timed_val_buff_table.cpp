#pragma once

Timed_Val_Buff_Table_A::Timed_Val_Buff_Table_A(Mem::SA&sa):
	map_a(sa)
{}

Timed_Val_Buff_Table::Timed_Val_Buff_Table(State&state,Hid hid,Timed_Val_Buff_Table_A&a):
	DS::Map<u2,Timed_Val_Buff>(a.map_a),
	state(state),
	hid(hid)
{}

Timed_Val_Buff*Timed_Val_Buff_Table::add(BT tag,s2 t,s2 max_x,const wchar_t*name)
{
	u2 id=state.gen_id();
	auto &buff=insert(id,Timed_Val_Buff{state,{.tag=tag,.hid=hid,.name=name},t,max_x})->value;
	return &buff;
}
