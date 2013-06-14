#include <list>
using namespace std;

#ifndef __Behaviour_h__
#define __Behaviour_h__

#include "Condition.h"
#include "Event.h"

class Event;
class Behaviour;

///Declarations for class Behaviour
class Behaviour
{
	public:
		bool check_conditions();
		Event* Event;
	private:
		std::list<Condition*> conditions;
};

#endif
