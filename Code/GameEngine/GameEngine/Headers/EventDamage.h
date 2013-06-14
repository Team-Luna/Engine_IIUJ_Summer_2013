#ifndef __EventDamage_h__
#define __EventDamage_h__

#include "Event.h"
#include "ValRetrieval.h"

class Field;
class ValRetrieval;

class EventDamage : public Event
{
	public:
		EventDamage(Level* L, double ia, Event* in);

		int get_type();
		void invokeEvent(Field* source, Field* target);

		double amount;
		Event* next;
};

#endif