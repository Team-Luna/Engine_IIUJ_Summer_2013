#ifndef __EventLevel_h__
#define __EventLevel_h__

#include "Event.h"
#include "ValRetrieval.h"
#include "Point.h"

class Field;
class ValRetrieval;
class Point;

class EventLevel : public Event
{
	public:
		EventLevel(Level* L, int it, Point iv, Event* in);

		int get_type();
		void invokeEvent(Field* source, Field* target);

		int type;	//0 - set respawn
					//1 - kill player
					//2 - respawn player
					//3 - victory
					//4 - defeat
		Point vals;
		Event* next;
};

#endif