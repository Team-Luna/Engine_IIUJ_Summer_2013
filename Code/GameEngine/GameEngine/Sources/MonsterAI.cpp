#include "MonsterAI.h"

MonsterAI::MonsterAI(Monster* own, AITable* ait, Action* ca, Action* l)
{
	owner = own;
	table = ait;
	current = ca;
	looped = l;
}

void MonsterAI::evaluate_actions(bool v1, bool v2, bool v3, bool v4,
	bool v5, bool v6, bool v7, bool v8,
	bool v9, bool v10, bool v11)
{
	//move_inwards, move_outwards, obstackle_in_front, wall_in_front,
	//jumpable_obstackle, climbable_front, cliff_in_front, can_climb_down,
	//can_drop, can_jump, can_jump_climb);
	if (evaluate)
	{
		if (v4)
			current = table->actions[0];
		if (v3)
			current = table->actions[1];
		if (v7)
			current = table->actions[2];
		if (v1 || v2)
			current = table->actions[5];
		if (false)
			current = table->actions[3];
		if (false)
			current = table->actions[4];
	}

	while(true)
	{
		if (current == 0)
			break;
		evaluate = current->evaluate;
		if (current->loop)
			looped = current;
		switch(current->ID)
		{
		case 0: //Turn Around
			owner->main_field->location->turn_around(owner->main_field);
			current = current->next_normal;
			break;
		case 1: //Move Forward
			owner->main_field->location->move_forward(owner->main_field);
			current = current->next_normal;
			break;
		case 2: //Jump
			owner->main_field->location->jump(owner->main_field, current->extra);
			current = current->next_normal;
			break;
		case 3: //Climb
			owner->main_field->location->climb(owner->main_field, current->extra);
			current = current->next_normal;
			break;
		case 4: //Attack
			owner->main_field->location->attack(owner->main_field);
			current = current->next_normal;
			break;
		case 5: //Shoot
			owner->main_field->location->shoot(owner->main_field);
			current = current->next_normal;
			break;
		case 6: //Idle
			owner->main_field->location->idle(owner->main_field);
			current = current->next_normal;
			break;
		case 7: //Wait until
			switch((int)current->scale1)
			{
			case 0: //!Climbing
				break;
			case 1: //Grounded
				break;
			case 2: //Animation is finished
				break;
			case 3: //Certain delay passed
				break;
			case 4: //!Sideway movement possible
				break;
			case 5: //Velocity change to
				break;
			}
			break;
		case 8: //If/then/else
			break;
		}
	}
}

void MonsterAI::proceed(double time)
{
	if ((current == 0) && (loop == true))
		handle_action(looped->ID, looped->extra);
}

bool MonsterAI::handle_action(int id, bool extra)
{
	switch(id)
	{
	case 0:
		owner->main_field->location->turn_around(owner->main_field);
		return true;
	case 1:
		owner->main_field->location->move_forward(owner->main_field);
		return true;
	case 2:
		owner->main_field->location->jump(owner->main_field, extra);
		return true;
	case 3:
		owner->main_field->location->climb(owner->main_field, extra);
		return true;
	case 4:
		owner->main_field->location->attack(owner->main_field);
		return true;
	case 5:
		owner->main_field->location->shoot(owner->main_field);
		return true;
	case 6:
		owner->main_field->location->idle(owner->main_field);
		return true;
	default:
		return false;
	}
}

void MonsterAI::set(double de, bool e, bool l, bool c, bool g, bool d)
{
	delay = de;
	evaluate = e;
	loop = l;
	climbing = c;
	grounded = g;
	dead = d;
}
