#include <exception>
#include "Condition.h"

using namespace std;

int Condition::get_type() {
	return 0;	
}

bool Condition::check_condition(Field* source, Field* target) {
	return false;
}
