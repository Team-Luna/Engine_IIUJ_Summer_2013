#ifndef __EventCP_h__
#define __EventCP_h__

#include "Event.h"
#include "ValRetrieval.h"

class Field;
class ValRetrieval;

class EventCP : public Event
{
	public:
		EventCP(Level* L, double it, int iv1t, int iv2t, double iv1v,
			double iv2v, bool ia, bool idt1, bool idt2, Event* in);

		int get_type();
		void invokeEvent(Field* source, Field* target);

		int type;
		ValRetrieval* val1;
		ValRetrieval* val2;
		bool additive;
		bool deltaTime1;
		bool deltaTime2;
		Event* next;
};

#endif