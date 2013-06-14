#ifndef __EventDestroy_h__
#define __EventDestroy_h__

#include "Event.h"
#include "ValRetrieval.h"

class Field;
class ValRetrieval;

class EventDestroy : public Event
{
	public:
		EventDestroy(Level* L);

		int get_type();
		void invokeEvent(Field* source, Field* target);
};

#endif