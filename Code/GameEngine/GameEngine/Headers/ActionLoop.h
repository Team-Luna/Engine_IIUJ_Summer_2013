#ifndef __ActionLoop_h__
#define __ActionLoop_h__

#include "Action.h"
#include "Level.h"

class ActionLoop : public Action
{
	public:
		ActionLoop(Level* L, Action* input_next, Action* input_looped);
		Action* next;
		Action* looped;

		int get_type();
		Action* get_next_action();
		Action* get_extra_action();
		bool do_action(double deltaTime = 0.0, Field* source = 0, Field* target = 0);
};


#endif