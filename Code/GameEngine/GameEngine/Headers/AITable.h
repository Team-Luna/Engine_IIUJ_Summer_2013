#ifndef __AITable_h__
#define __AITable_h__

#include "Action.h"

class Action;

class AITable
{
	public:
	AITable();

	Action* actions[5];
	//Obstackle
	//Cliff
	//Monster
	//Player
	//Side
};

#endif
