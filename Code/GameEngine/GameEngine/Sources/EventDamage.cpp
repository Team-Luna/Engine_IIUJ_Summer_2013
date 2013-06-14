#include "EventDamage.h"
#include "Windows.h"

EventDamage::EventDamage(Level* L, double ia, Event* in)
{
	location = L;
	amount = ia;
	next = in;
}

int EventDamage::get_type()
{
	return 4;
}

void EventDamage::invokeEvent(Field* source, Field* target)
{
	if (source->owner == 0)
		return;
	location->damage(source, amount); //monster
}

