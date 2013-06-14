#include "EventCP.h"

EventCP::EventCP(Level* L, double it, int iv1t, int iv2t, double iv1v,
	double iv2v, bool ia, bool idt1, bool idt2, Event* in)
{
	location = L;
	type = it;
	val1 = new ValRetrieval(location, iv1t, iv1v);
	val2 = new ValRetrieval(location, iv2t, iv2v);
	additive = ia;
	deltaTime1 = idt1;
	deltaTime2 = idt2;
	next = in;
}

int EventCP::get_type()
{
	return 1;
}

void EventCP::invokeEvent(Field* source, Field* target)
{
	double Ans = 0.0;
	if (deltaTime1)
		Ans = val1->retrieve(source, target)*location->delta_time;
	else Ans = val1->retrieve(source, target);

	if (additive)
	{
		if (deltaTime2)
			Ans = Ans + val2->retrieve(source, target)*location->delta_time;
		else Ans = Ans + val2->retrieve(source, target);
	}
	else
	{
		if (deltaTime2)
			Ans = Ans - val2->retrieve(source, target)*location->delta_time;
		else Ans = Ans - val2->retrieve(source, target);
	}

	location->editValue(type, source, Ans);
	if (next != 0)
		next->invokeEvent(source, target);
}

