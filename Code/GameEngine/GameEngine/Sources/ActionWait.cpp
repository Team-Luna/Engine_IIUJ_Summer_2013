#include "ActionWait.h"

ActionWait::ActionWait(Level* L, bool input_time, double input_amount, Action* input_next)
{
	location = L;
	time = input_time;
	amount = input_amount;
	next = input_next;
}

int ActionWait::get_type()
{
	return 3;
}

Action* ActionWait::get_next_action()
{
	return next;
}

Action* ActionWait::get_extra_action()
{
	return 0;
}

bool ActionWait::do_action(double deltaTime, Field* source, Field* target)
{
	if (time)
	{
		if (deltaTime < amount)
			return false;
		return true;
	}
	else
	{
		if (source->owner == 0)
			return true;
		if (source->owner->animator == 0)
			return true;
		if (source->owner->animator->checkProgress() < amount)
			return false;
		return true;
	}
}