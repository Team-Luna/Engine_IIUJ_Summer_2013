#ifndef __ActionEvaluate_h__
#define __ActionEvaluate_h__

#include "Action.h"
#include "Level.h"

class ActionEvaluate : Action
{
	public:
		ActionEvaluate(Level* L, bool input_value, Action* input_next);
		bool value;
		Action* next;

		int get_type();
		Action* get_next_action();
		Action* get_extra_action();
		bool do_action(double deltaTime = 0.0, Field* source = 0, Field* target = 0);
};


#endif