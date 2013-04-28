#include "MonsterAI.h"

MonsterAI::MonsterAI(Monster* own)
{
	owner = own;
}

void MonsterAI::evaluate(double time)
{
	if (delay != -1)
	{
		if (delay-time < 0)
			delay = 0;
		else delay = delay-time;
	}
	if (ignorePoints-time < 0)
		ignorePoints = 0;
	else ignorePoints = ignorePoints-time;

	
	if (ignorePoints == 0.0)
	{
		for (std::list<AIPoint*>::iterator i = owner->main_field->location->aipoints.begin(); i != owner->main_field->location->aipoints.end(); i++)
		{
			double x1 = owner->main_field->position.position_x - 5;
			double x2 = owner->main_field->position.position_x + 5;
			double y1 = owner->main_field->position.position_y - 5;
			double y2 = owner->main_field->position.position_y + 5;

			if ((x1 < (*i)->position.position_x) && ((*i)->position.position_x) < x2)
			{
				if ((y1 < (*i)->position.position_y) && ((*i)->position.position_y) < y2)
				{
					switch((*i)->type)
					{
					default:
						for (std::list<int>::iterator j = behaviours[1].begin(); j != behaviours[1].end(); j++)
							actions.insert(actions.end(), (*j));
						break;
					}
				}
			}
		}
	}

	if ((delay == 0) || ((delay == -1) && (0.95 < owner->animator->checkProgress())))
	{
		if (!actions.empty())
		{
			int n = actions.front();
			actions.pop_front();

			current_action = n;

			switch(current_action)
			{
			case 0: //Ignore points
				ignorePoints = owner->main_field->location->actions[current_action]->delay;
				break;
			case 1: //Idle
				owner->main_field->velocity.position_x = 0;
				owner->animator->setAnimation(0);
				delay = owner->main_field->location->actions[current_action]->delay;
				interruptable = owner->main_field->location->actions[current_action]->interruptable;
				break;
			case 2: //Turn around
				if (owner->facing_angle == 90)
					owner->facing_angle = 270;
				else owner->facing_angle = 90;
				break;
			case 3: //Move
				if (owner->facing_angle == 90)
					owner->main_field->velocity.position_x = owner->movement_speed;
				else owner->main_field->velocity.position_x = -owner->movement_speed;
				owner->animator->setAnimation(1);
				delay = owner->main_field->location->actions[current_action]->delay;
				interruptable = owner->main_field->location->actions[current_action]->interruptable;
				break;
			default:
				break;
			}
		}
	}
}

void MonsterAI::set(double d, double iP, int o)
{
	delay = d;
	ignorePoints = iP;
	orientation = o;
}

void MonsterAI::addToList(int which, int value)
{
	behaviours[which].insert(behaviours[which].end(), value);
}

void MonsterAI::addCurrent(int value)
{
	actions.insert(actions.end(), value);
}