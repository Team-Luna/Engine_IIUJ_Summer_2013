#include <exception>
#include "ConditionPoint.h"

using namespace std;

ConditionPoint::ConditionPoint(Level* L, Point input_P, int input_ref, int input_type)
{
	location = L;
	P = input_P;
	ref = input_ref;
	type = input_type;
}

int ConditionPoint::get_type() {
	return 3;	
}

bool ConditionPoint::check_condition(Field* source, Field* target) {
	//Handling proper reference
	Point T;
	if (ref == 0)
		T = P; //fixed
	if (ref == 1)
		T = P + source->position;
	if (ref == 2)
		T = P + target->position;
	//Getting the point
	Field* F = location->collision_Point(T);
	//Handling effects
	if (F == 0)
	{
		if (type == 0)
			return true;
	}
	else
	{
		if (F->owner == 0)
		{
			if (type == -1)
				return true;
			else return false;
		}
		if (F->owner->get_type() == type)
			return true;
		if (type == 5)
			return true;
	}
	return false;
}
