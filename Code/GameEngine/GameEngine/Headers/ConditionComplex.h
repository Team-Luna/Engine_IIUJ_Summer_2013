#ifndef __ConditionComplex_h__
#define __ConditionComplex_h__

#include <exception>
#include "Condition.h"

using namespace std;

class Field;

class ConditionComplex : Condition
{
	public:
		ConditionComplex(Condition* input_con1, Condition* input_con2, bool input_and);
		Condition* con1;
		Condition* con2;
		bool and; //0 = and, 1 = or

		int get_type();
		bool check_condition(Field* source = 0, Field* target = 0);
};

#endif
