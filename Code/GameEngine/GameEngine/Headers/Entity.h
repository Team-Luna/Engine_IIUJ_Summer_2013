#ifndef __Entity_h__
#define __Entity_h__

#include "Animator.h"
#include <exception>

using namespace std;

class Field;

class Entity
{
	public:
		Animator* animator;
		float movement_speed;
		Field* main_field;
		int custom_attribute1;
		int custom_attribute2;
		int custom_attribute3;
		int gravity_degree;
		int facing_angle;
		bool grounded;

		virtual unsigned int get_type() = 0; //0 - Entity, 1 - Player, 2 - Monster, 3 - Item, 4 - Border
		virtual void remove() = 0;
};

#endif
