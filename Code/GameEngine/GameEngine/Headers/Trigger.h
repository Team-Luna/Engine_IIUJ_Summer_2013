#include <exception>
using namespace std;

#ifndef __Trigger_h__
#define __Trigger_h__

#include "Condition.h"
#include "Event.h"

class Event;
class Field;
class Condition;

class Trigger
{
	public:
		Trigger(Condition* input_con, Event* input_eve, bool input_tk);
		void check(Field* source = 0, Field* target = 0);

		Condition* con;
		Event* eve;
		bool takes_units;
};

#endif
