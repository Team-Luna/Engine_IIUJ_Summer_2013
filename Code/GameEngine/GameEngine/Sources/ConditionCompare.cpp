#include <exception>
#include "ConditionCompare.h"

using namespace std;

ConditionCompare::ConditionCompare(Level* L, int T1, int T2, double V1, double V2, int input_ref)
{
	val1 = new ValRetrieval(L, T1, V1);
	val2 = new ValRetrieval(L, T2, V2);
	ref = input_ref;
}

int ConditionCompare::get_type() {
	return 2;	
}

bool ConditionCompare::check_condition(Field* source, Field* target) {
	if (ref == 0) //!=
	{
		if (val1->retrieve(source, target) != val2->retrieve(target, source))
			return true;
		return false;
	}
	if (ref == 1) //==
	{
		if (val1->retrieve(source, target) == val2->retrieve(target, source))
			return true;
		return false;
	}
	if (ref == 2) //>=
	{
		if (val1->retrieve(source, target) >= val2->retrieve(target, source))
			return true;
		return false;
	}
	if (ref == 3) //<=
	{
		if (val1->retrieve(source, target) <= val2->retrieve(target, source))
			return true;
		return false;
	}
	if (ref == 4) //>
	{
		if (val1->retrieve(source, target) > val2->retrieve(target, source))
			return true;
		return false;
	}
	if (ref == 5) //<
	{
		if (val1->retrieve(source, target) < val2->retrieve(target, source))
			return true;
		return false;
	}
	return false;
}
