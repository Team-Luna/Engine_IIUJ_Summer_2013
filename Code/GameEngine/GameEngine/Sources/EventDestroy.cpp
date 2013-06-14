#include "EventDestroy.h"
#include "Windows.h"

EventDestroy::EventDestroy(Level* L)
{
	location = L;
}

int EventDestroy::get_type()
{
	return 3;
}

void EventDestroy::invokeEvent(Field* source, Field* target)
{
	if (source->owner != 0)
	{
		if (source == location->player->main_field)
			return;

		location->trash(source);
	}
}

