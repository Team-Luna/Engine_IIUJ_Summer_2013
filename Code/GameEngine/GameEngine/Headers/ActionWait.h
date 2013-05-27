#ifndef __ActionWait_h__
#define __ActionWait_h__

#include "Action.h"
#include "Level.h"

class ActionWait : Action
{
	public:
		ActionWait(Level* L, bool input_time, double input_amount, Action* input_next);
		bool time;
		double amount;
		Action* next;

		int get_type();
		Action* get_next_action();
		Action* get_extra_action();
		bool do_action(double deltaTime = 0.0, Field* source = 0, Field* target = 0);
};


#endif