#include "ActionLoop.h"

ActionLoop::ActionLoop(Level* L, Action* input_next, Action* input_looped)
{
	location = L;
	next = input_next;
	looped = input_looped;
}

int ActionLoop::get_type()
{
	return 5;
}

Action* ActionLoop::get_next_action()
{
	return next;
}

Action* ActionLoop::get_extra_action()
{
	return looped;
}

bool ActionLoop::do_action(double deltaTime, Field* source, Field* target)
{
	return true;
}