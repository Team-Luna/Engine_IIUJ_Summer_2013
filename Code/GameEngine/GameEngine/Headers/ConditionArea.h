#ifndef __ConditionArea_h__
#define __ConditionArea_h__

#include <exception>
#include "Point.h"
#include "Level.h"
#include "Condition.h"

using namespace std;

class Point;
class Level;
class Field;

class ConditionArea : public Condition
{
	public:
		ConditionArea(Field* input_area);
		Field* area;

		int get_type();
		bool check_condition(Field* source = 0, Field* target = 0);
};

#endif
