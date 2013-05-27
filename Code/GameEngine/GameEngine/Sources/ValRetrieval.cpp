#include <exception>
#include "ValRetrieval.h"

using namespace std;

ValRetrieval::ValRetrieval(Level* L, int T, double V)
{
	location = L;
	type = T;
	val = V;
}

double ValRetrieval::retrieve(Field* From, Field* To)
{
	if (type == -1)
	{
		srand (time(NULL));
		return rand()%100 + 1;
	}
	if (type == 0)
		return val;
	return location->retrieveValue(type, From, To);
}