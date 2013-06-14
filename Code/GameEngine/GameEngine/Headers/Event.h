#include <exception>
using namespace std;

#ifndef __Event_h__
#define __Event_h__

class Level;
class Field;

class Event
{
	public:
		virtual int get_type() = 0;
		virtual void invokeEvent(Field* source, Field* target) = 0;

		int custom_attribute1;
		int custom_attribute2;
		Level* location;
};

#endif
