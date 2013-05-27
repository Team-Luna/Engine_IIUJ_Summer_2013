#ifndef __ActionIfThenElse_h__
#define __ActionIfThenElse_h__

#include "Action.h"
#include "Condition.h"
#include "Level.h"

class ActionIfThenElse : Action
{
	public:
		ActionIfThenElse(Level* L, Condition* input_if, Action* input_then, Action* input_else);
		Condition* condition_if;
		Action* action_then;
		Action* action_else;

		int get_type();
		Action* get_next_action();
		Action* get_extra_action();
		bool do_action(double deltaTime = 0.0, Field* source = 0, Field* target = 0);
};


#endif