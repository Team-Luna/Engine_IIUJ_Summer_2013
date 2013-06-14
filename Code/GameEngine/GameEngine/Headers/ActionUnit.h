#ifndef __ActionUnit_h__
#define __ActionUnit_h__

#include "Action.h"
#include "Level.h"

class ActionUnit : public Action
{
	public:
		ActionUnit(Level* L, int input_actionID, Action* input_next);
		int actionID;
		Action* next;

		int get_type();
		Action* get_next_action();
		Action* get_extra_action();
		bool do_action(double deltaTime = 0.0, Field* source = 0, Field* target = 0);
};


#endif