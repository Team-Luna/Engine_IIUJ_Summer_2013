#include "ActionEvaluate.h"

ActionEvaluate::ActionEvaluate(Level* L, bool input_value, Action* input_next)
{
	location = L;
	value = input_value;
	next = input_next;
}

int ActionEvaluate::get_type()
{
	return 2;
}

Action* ActionEvaluate::get_next_action()
{
	return next;
}

Action* ActionEvaluate::get_extra_action()
{
	return 0;
}

bool ActionEvaluate::do_action(double deltaTime, Field* source, Field* target)
{
	return value;
}