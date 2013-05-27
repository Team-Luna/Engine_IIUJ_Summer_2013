#ifndef __ConditionCompare_h__
#define __ConditionCompare_h__

#include <exception>
#include "Condition.h"
#include "ValRetrieval.h"

using namespace std;

class Level;
class Field;
class ValRetrieval;

class ConditionCompare : Condition
{
	public:
		ConditionCompare(Level* L, int T1, int T2, double V1, double V2, int input_ref);
		ValRetrieval* val1;
		ValRetrieval* val2;
		int ref;	//1 ==
					//2 >=
					//3 <=
					//4 >
					//5 <

		int get_type();
		bool check_condition(Field* source = 0, Field* target = 0);
};

#endif
