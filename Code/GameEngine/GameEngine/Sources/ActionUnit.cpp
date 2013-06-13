#include "ActionUnit.h"

ActionUnit::ActionUnit(Level* L, int input_actionID, Action* input_next)
{
	location = L;
	actionID = input_actionID;
	next = input_next;
}

int ActionUnit::get_type()
{
	return 1;
}

Action* ActionUnit::get_next_action()
{
	return next;
}

Action* ActionUnit::get_extra_action()
{
	return 0;
}

bool ActionUnit::do_action(double deltaTime, Field* source, Field* target)
{
	switch(actionID)
	{
	case 0: //Turn Around
		location->turn_around(source);
		break;
	case 1: //Move Forward
		location->move_forward(source);
		break;
	case 2: //Jump Forward
		location->jump_forward(source);
		break;
	case 3: //Jump Backwards
		location->jump_backwards(source);
		break;
	case 4: //Climb Upwards
		location->climb_upwards(source);
		break;
	case 5: //Climb Downwards
		location->climb_downwards(source);
		break;
	case 6: //Attack
		location->attack(source);
		break;
	case 7: //Shoot
		location->shoot(source);
		break;
	case 8: //Idle
		location->idle(source);
		break;
	case 9: //Stop climbing
		location->stop_climbing(source);
		break;
	}
	return true;
}