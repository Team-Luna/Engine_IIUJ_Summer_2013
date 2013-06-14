#ifndef __ConditionTimer_h__
#define __ConditionTimer_h__

#include <exception>
#include "Timer.h"
#include "Point.h"
#include "Level.h"
#include "Condition.h"

using namespace std;

class Timer;
class Point;
class Level;
class Field;

class ConditionTimer : public Condition
{
	public:
		ConditionTimer(Level* L, Timer* it);
		Level* location;
		Timer* timer;

		int get_type();
		bool check_condition(Field* source = 0, Field* target = 0);
};

#endif
