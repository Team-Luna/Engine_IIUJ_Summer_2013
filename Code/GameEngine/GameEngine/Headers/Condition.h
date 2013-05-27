#ifndef __Condition_h__
#define __Condition_h__

#include <exception>

using namespace std;

class Field;

class Condition
{
	public:
		virtual int get_type() = 0; //1 Complex
									//2 Compare
									//3 Point
		virtual bool check_condition(Field* source = 0, Field* target = 0) = 0;
};

#endif
