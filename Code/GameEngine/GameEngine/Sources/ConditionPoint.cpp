#include <exception>
#include "ConditionPoint.h"

using namespace std;

ConditionPoint::ConditionPoint(Level* L, Condition* input_con, Point input_P, int input_ref, int input_type)
{
	location = L;
	con = input_con;
	P = input_P;
	ref = input_ref;
	type = input_type;
}

int ConditionPoint::get_type() {
	return 3;	
}

bool ConditionPoint::check_condition(Field* source, Field* target) {
	bool orientation;
	if (ref == 1)
		if (source->owner->facing_angle == 90)
			orientation = true;
		else orientation = false;
	else
		if (target->owner->facing_angle == 90)
			orientation = true;
		else orientation = false;
	//Handling proper reference
	Point T;
	if (ref == 0)
		T = P; //fixed
	if (ref == 1)
	{
		if (orientation == 1)
			T.position_x = source->position.position_x + P.position_x;
		else T.position_x = source->position.position_x - P.position_x;
		T.position_y = P.position_y + source->position.position_y;
		T.layer = P.layer + source->position.layer;
	}
	if (ref == 2)
	{
		if (orientation == 1)
			T.position_x = target->position.position_x + P.position_x;
		else T.position_x = target->position.position_x - P.position_x;
		T.position_y = P.position_y + target->position.position_y;
		T.layer = P.layer + target->position.layer;
	}
	//Getting the point
	Field* F = location->collision_Point(T);
	//Handling effects
	//Empty
	if (F == 0)
		if (type == 0)
			return true;
		else return false;
	if (type == 0)
		return false;
	//Non owned field
	if (type == -1)
		if (F->owner == 0)
			return false;
		else return true;
	//Condition
	if (con != 0)
		if (type == 1)
			return con->check_condition(F, target);
		else return con->check_condition(source, F);
	else return true;
}
