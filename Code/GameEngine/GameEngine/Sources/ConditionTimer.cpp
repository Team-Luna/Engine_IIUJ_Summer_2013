#include <exception>
#include "ConditionTimer.h"

using namespace std;

ConditionTimer::ConditionTimer(Level* L, Timer* it)
{
	location = L;
	timer = it;
}

int ConditionTimer::get_type() {
	return 5;	
}

bool ConditionTimer::check_condition(Field* source, Field* target) {
	return timer->check();
}
