#include <exception>
using namespace std;

#ifndef __Event_h__
#define __Event_h__

#include "Level.h"
#include "Field.h"

class Level;
class Field;
class Event;
///Declarations for class Event
class Event
{
	public:
		virtual void invokeEvent(Field* source, Field* target) = 0;
	private:
		int custom_attribute1;
		int custom_attribute2;
		Level* location;

};

#endif
