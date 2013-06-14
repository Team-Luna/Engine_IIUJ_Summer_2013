#ifndef __Projectile_h__
#define __Projectile_h__

#include "Entity.h"
#include "Level.h"
#include "Point.h"
#include "Event.h"
#include <exception>

using namespace std;

class Level;
class Event;
class Projectile;

class Projectile : public Entity
{
	public:
		Projectile(Level* L, double ms, Point pos,
			char* animT, char* modelP, bool anim, Event* cr, bool ip, bool im,
			bool it, bool ib, double et, bool h);
		unsigned int get_type();
		void remove();

		Event* collision_reaction;
		bool ignores_player;
		bool ignores_monsters;
		bool ignores_items;
		bool ignores_borders;
		double expiration_time;
		bool homing;
};

#endif
