#include "AIPoint.h"

AIPoint::AIPoint(int o, int t, Point pos, int ca1, int ca2, int ca3)
{
	orientation = o;
	type = t;
	position.position_x = pos.position_x;
	position.position_y = pos.position_y;
	position.layer = pos.layer;

	custom_attribute1 = ca1;
	custom_attribute2 = ca2;
	custom_attribute3 = ca3;
}