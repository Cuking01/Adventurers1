#pragma once

Buff_Helper::Buff_Helper():add(0),sub(0),addp(1),subp(1){}
f3 Buff_Helper::operator()(f3 x) const
{
	return x*addp*subp+add-sub;
}

s2 Buff::operator()(Attribute&attr,Buff_Helper&bh)
{
	return fun(attr,bh,st);
}
s2 Event::operator()(State&state)
{
	return fun(state,st);
}
s2 Damage_Handler::operator()(State&state,Damage&damage)
{
	return fun(state,damage,st);
}
s2 Skill_Handler::operator()(State&state,Hid hid,s2 sid,const Arg_t_6&arg)
{
	return fun(state,hid,sid,arg,st);
}

Timed_Val_Buff::Timed_Val_Buff():state(*(State*)0){}

Timed_Val_Buff::Timed_Val_Buff(State&state,Buff_Base base,s2 t,s2 max_x):
	Buff_Base(base),
	state(state)
{
	//I0记录层数
    //I4记录上一次增加的时间
    //U8记录删除事件的句柄
    //I12存持续时间
    //I16记录最大层数
    st.I0=0;
    st.I4=0;
    st.U8=0;
    st.I12=t;
    st.I16=max_x;
}

void Timed_Val_Buff::add(s2 x)
{
	st.I0+=x;
    if(st.I0>st.I16)st.I0=st.I16;
    st.I4=state.time;
    state.event_queue.erase(st.U8);
    st.U8=state.gen_id();
    state.event_queue.add(st.U8,state.time+st.I12,
    {
        {.st={.P0=(void*)&st.I0}},
        lambda_Event
        {
            *(s2*)st.P0=0;
            return 0;
        }
    });
}
void Timed_Val_Buff::cls(BT::驱散等级_t 驱散等级)
{
    if(驱散等级.val>=tag.驱散等级)
        st.I0=0;
}

s2& Timed_Val_Buff::operator()() noexcept
{
    return st.I0;
}
