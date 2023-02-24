#pragma once

struct Event_Queue_A
{
	DS::Map<s2,s2>::A time_a;
	DS::Map<std::pair<s2,s2>,Event>::A events_a;
	Event_Queue_A(Mem::SA&sa);
};

struct Event_Queue
{
	State&state;

	DS::Map<s2,s2> time;
	DS::Map<std::pair<s2,s2>,Event> events;

	Event_Queue(State&state,Event_Queue_A&a);

	void insert(s2 id,s2 t,const Event& event);
	void erase(s2 id);
	void run(s2 t);
};
