#include <exception>
#include "ConditionArea.h"

using namespace std;

ConditionArea::ConditionArea(Field* input_area)
{
	area = input_area;
}

int ConditionArea::get_type() {
	return 4;	
}

bool ConditionArea::check_condition(Field* source, Field* target) {
	return area->location->inside(source, area);
}
