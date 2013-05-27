#include <exception>
#include "ConditionComplex.h"

using namespace std;

ConditionComplex::ConditionComplex(Condition* input_con1, Condition* input_con2, bool input_and)
{
	con1 = input_con1;
	con2 = input_con2;
	and = input_and;
}

int ConditionComplex::get_type() {
	return 1;	
}

bool ConditionComplex::check_condition(Field* source, Field* target) {
	if (and == true)
	{
		if (con1->check_condition(source, target) && con2->check_condition(source, target))
			return true;
		return false;
	}
	else
	{
		if (con1->check_condition(source, target) || con2->check_condition(source, target))
			return true;
		return false;
	}
}
