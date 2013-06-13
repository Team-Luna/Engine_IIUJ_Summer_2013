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
	return action_then;
}

Action* ActionIfThenElse::get_extra_action()
{
	return action_else;
}

bool ActionIfThenElse::do_action(double deltaTime, Field* source, Field* target)
{
	return condition_if->check_condition(source, target);
}