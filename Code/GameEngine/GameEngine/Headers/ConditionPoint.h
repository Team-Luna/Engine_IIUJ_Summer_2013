#ifndef __ConditionPoint_h__
#define __ConditionPoint_h__

#include <exception>
#include "Point.h"
#include "Level.h"
#include "Condition.h"

using namespace std;

class Point;
class Level;
class Field;

class ConditionPoint : Condition
{
	public:
		ConditionPoint(Level* L, Point input_P, int input_ref, int input_type);
		Level* location;
		Point P;
		int ref;	//0 fixed
					//1 from source
					//2 from target
		int type;	//-1 non-owned field
					//0 empty
					//1 player
					//2 monster
					//3 item
					//4 border
					//5 anything

		int get_type();
		bool check_condition(Field* source = 0, Field* target = 0);
};

#endif
