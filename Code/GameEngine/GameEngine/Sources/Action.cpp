#include "Action.h"

Action::Action()
{
	father = 0;
	next_normal = 0;
	next_extra = 0;
}

void Action::set_values(char* nm, int id, double s1, double s2, bool l, bool e, bool ex)
{
	name = nm;
	ID = id;
	scale1 = s1;
	scale2 = s2;
	loop = l;
	evaluate = e;
	extra = ex;
}