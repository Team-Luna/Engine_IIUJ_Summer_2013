#include "Action.h"

Action::Action()
{
	name = 0;
	interruptable = false;
	delay = 0;
}

void Action::set(char* nm, bool in, double d)
{
	name = nm;
	interruptable = in;
	delay = d;
}