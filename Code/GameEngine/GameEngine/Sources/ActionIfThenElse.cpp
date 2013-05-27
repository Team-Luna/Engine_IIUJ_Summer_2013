#include "ActionIfThenElse.h"

ActionIfThenElse::ActionIfThenElse(Level* L, Condition* input_if, Action* input_then, Action* input_else)
{
	location = L;
	condition_if = input_if;
	action_then = input_then;
	action_else = input_else;
}

int ActionIfThenElse::get_type()
{
	return 4;
}

Action* ActionIfThenElse::get_next_action()
{
	if (condition_if->check_condition())
		return action_then;
	else return action_else;
}

Action* ActionIfThenElse::get_extra_action()
{
	return 0;
}

bool ActionIfThenElse::do_action(double deltaTime, Field* source, Field* target)
{
	return true;
}