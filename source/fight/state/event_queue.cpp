#pragma once

Event_Queue_A::Event_Queue_A(Mem::SA&sa):
	time_a(sa),
	events_a(sa)
{}

Event_Queue::Event_Queue(State&state,Event_Queue_A&a):
	state(state),
	time(a.time_a),
	events(a.events_a)
{}

void Event_Queue::add(u2 id,s2 t,const Event& event)
{
	time.insert(id,t);
	events.insert(std::pair{t,id},event);
}

void Event_Queue::erase(u2 id)
{
	events.erase({time[id],id});
	time.erase(id);
}
void Event_Queue::run(s2 t)
{
	while(events.size())
	{

		auto [pos,event]=*events.begin();
		if(pos.first<=t)
		{
			events.erase(pos);
			time.erase(pos.second);
			event(state);
		}
		else break;
	}
}
