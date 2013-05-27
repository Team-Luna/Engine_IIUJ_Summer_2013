#include <list>
using namespace std;

#include "Behaviour.h"
#include "Condition.h"
#include "Event.h"
///Code for class Behaviour functions
bool Behaviour::check_conditions() {
	bool checked = true;
	for (std::list<Condition*>::iterator ii=conditions.begin(); ii!=conditions.end(); ++ii)
		if (!(*ii)->check_condition()) {
			checked = false;
			break;
		}
	return checked;
}