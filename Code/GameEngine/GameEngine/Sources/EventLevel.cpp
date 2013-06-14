#include "EventLevel.h"
#include "Windows.h"

EventLevel::EventLevel(Level* L, int it, Point iv, Event* in)
{
	location = L;
	type = it;
	vals = iv;
	next = in;
}

int EventLevel::get_type()
{
	return 5;
}

void EventLevel::invokeEvent(Field* source, Field* target)
{

}

