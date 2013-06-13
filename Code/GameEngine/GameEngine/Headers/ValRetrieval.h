#ifndef __ValRetrieval_h__
#define __ValRetrieval_h__

#include <exception>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Level.h"

using namespace std;

class Field;
class Level;

class ValRetrieval
{
	public:
		ValRetrieval(Level* L, int T, double V);

		Level* location;
		int type;	//-1 = random (return 1-100)
					// 0 = fixed (return val)
					// 1-3 = return position
					// 4-6 = return velocity
					// 7-9 = return custom attributes
					// 10 = return facing angle
					// 11 = distance
					// 12 = type (int)
					// 13 = animation progress [0,1]
		double val;

		double retrieve(Field* From, Field* To);
};

#endif
