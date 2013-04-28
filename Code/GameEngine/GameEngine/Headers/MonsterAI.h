#ifndef __MonsterAI_h__
#define __MonsterAI_h__

#include "Monster.h"
#include "Action.h"
#include "AITable.h"
#include <list>

class Monster;
class Action;
class AITable;

class MonsterAI
{
	public:
	MonsterAI(Monster* own, AITable* ait, Action* ca, Action* l);
	
	void set(double de, bool e, bool l, bool c, bool g, bool d);
	void evaluate_actions(bool v1, bool v2, bool v3, bool v4, bool v5, bool v6,
		bool v7, bool v8, bool v9, bool v10, bool v11);
	void proceed(double time);
	bool handle_action(int id);

	AITable* table;
	Monster* owner;
	Action* current;
	Action* looped;
	double delay;
	bool evaluate;
	bool loop;
	bool climbing;
	bool grounded;
	bool dead;
};

#endif
