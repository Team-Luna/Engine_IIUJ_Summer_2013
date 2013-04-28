#ifndef __AIPoint_h__
#define __AIPoint_h__

#include "Point.h"

class AIPoint
{
	public:
	AIPoint(int o, int t, Point pos, int ca1, int ca2, int ca3);

	int orientation;
	int type;
	Point position;

	int custom_attribute1;
	int custom_attribute2;
	int custom_attribute3;
};

#endif
