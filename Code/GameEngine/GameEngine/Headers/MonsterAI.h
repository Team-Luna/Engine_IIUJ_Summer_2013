#ifndef __MonsterAI_h__
#define __MonsterAI_h__

#include "Monster.h"
#include <list>

class Monster;

class MonsterAI
{
	public:
	MonsterAI(Monster* own);
	
	void set(double d, double iP, int o);
	void addToList(int which, int value);
	void addCurrent(int value);
	void evaluate(double time);
	void setAction(bool in, int ac, int d);

	private:
	std::list<int> behaviours[10];
	Monster* owner;
	double delay;
	double ignorePoints;
	int orientation;
	bool interruptable;
	int current_action;
	std::list<int> actions;
};

#endif
