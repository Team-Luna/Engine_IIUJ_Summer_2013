#ifndef __Monster_h__
#define __Monster_h__

#include "Entity.h"
#include "Level.h"
#include "Point.h"
#include "Behaviour.h"
#include "MonsterAI.h"
#include <exception>
#include <string>
#include <list>

using namespace std;

//class Entity;
class Level;
class Behaviour;
class Monster;
class MonsterAI;

class Monster : public Entity
{
	public:
		bool climbing;
		int hp;
		std::string name;
		MonsterAI* aI;

		~Monster();
		Monster(Level* L, int ms, int mhp, std::string nm, std::string mt,
			Point pos, Point size, int ca1, int ca2, int ca3, int gd, int fa,
			char* animT, char* modelP, Point trans, bool anim, int lt, bool a, bool aa, bool cl);
		unsigned int get_type();
		void act(double time);
		void remove();
	private:
		std::string monster_type;

};

#endif
