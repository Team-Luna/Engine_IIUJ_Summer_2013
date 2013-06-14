#ifndef __Player_h__
#define __Player_h__

#include "Animator.h"
#include "Entity.h"
#include "Level.h"
#include "Point.h"
#include <exception>

using namespace std;

class Level;
//class Entity;
class Player;

class Player : public Entity
{
	public:
		int hp;
		int lifes;
		bool climbing;
		
		~Player();
		Player();
		Player(Level* L, int ms, int php, int l, Point pos, Point size,
			int ca1, int ca2, int ca3, int gd, int fa, char* animT, char* modelP,
			Point trans, bool anim, bool cl);
		unsigned int get_type();
		void remove();
};

#endif
