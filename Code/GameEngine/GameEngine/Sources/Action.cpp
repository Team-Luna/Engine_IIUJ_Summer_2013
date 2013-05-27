#include "Action.h"

int Action::get_type()
{
	return 0;
}

Action* Action::get_next_action()
{
	return 0;
}

Action* Action::get_extra_action()
{
	return 0;
}

bool Action::do_action(double deltaTime, Field* source, Field* target)
{
	return true;
}