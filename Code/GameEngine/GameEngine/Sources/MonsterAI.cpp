#include "MonsterAI.h"

MonsterAI::MonsterAI(Monster* own, AITable* ait, Action* ca, Action* l, double de, bool e, bool d)
{
	owner = own;
	table = ait;
	current = ca;
	looped = l;
	delay = de;
	evaluate = e;
	dead = d;
}

void MonsterAI::evaluate_actions(double time, bool v1, bool v2, bool v3, bool v4,
	bool v5, bool v6, bool v7, bool v8, bool v9, bool v10, bool v11, bool v12,
	bool v13)
{
	Field* target = owner->main_field->location->player->main_field;
	delay += time;
	//move_inwards, move_outwards, obstackle_in_front, wall_in_front,
	//jumpable_obstackle, climbable_front, cliff_in_front, can_climb_down,
	//can_drop, can_jump, can_jump_climb, monster_in_front, player_in_range);

	if (evaluate && v13) //Player
	{
		current = table->actions[3];

		while (true)
		{
			//Handling looped action
			if (looped != 0)
				looped->do_action(delay, owner->main_field, target);

			if (current == 0)
				break;

			//Checking current action
			if (current->get_type() == 2) //Evaluate change
			{
				delay = 0;
				evaluate = current->do_action(delay, owner->main_field, target);
				current = current->get_next_action();
				continue;
			}
			if (current->get_type() == 4) //If/Then/Else
			{
				delay = 0;
				if (current->do_action(delay, owner->main_field, target))
					current = current->get_next_action();
				else 
					current = current->get_extra_action();
				continue;
			}
			if (current->get_type() == 5) //Looped
			{
				delay = 0;
				looped = current->get_extra_action();
				current = current->get_next_action();
				continue;
			}
			if (current->do_action(delay, owner->main_field, target)) //Standard
			{
				delay = 0;
				current = current->get_next_action();
				continue;
			}
			else
				break;
		}
	}
	target = 0;

	if (evaluate)
	{
		if (v4) //Wall
			current = table->actions[0];
		if (v3) //Obstackle
			current = table->actions[0];
		if (v7) //Cliff
			current = table->actions[1];
		if (v12) //Monster
			current = table->actions[2];
		if (v1 || v2) //Side
			current = table->actions[4];
	}

	while(true)
	{
		//Handling looped action
		if (looped != 0)
			looped->do_action(delay, owner->main_field, target);

		if (current == 0)
			break;

		//Checking current action
		if (current->get_type() == 2) //Evaluate change
		{
			delay = 0;
			evaluate = current->do_action(delay, owner->main_field, target);
			current = current->get_next_action();
			continue;
		}
		if (current->get_type() == 4) //If/Then/Else
		{
			delay = 0;
			if (current->do_action(delay, owner->main_field, target))
				current = current->get_next_action();
			else 
				current = current->get_extra_action();
			continue;
		}
		if (current->get_type() == 5) //Looped
		{
			delay = 0;
			looped = current->get_extra_action();
			current = current->get_next_action();
			continue;
		}
		if (current->do_action(delay, owner->main_field, target)) //Standard
		{
			delay = 0;
			current = current->get_next_action();
			continue;
		}
		else
			break;
	}
}
