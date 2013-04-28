#include <exception>
#include <string>
#include <list>
#include <Windows.h>

using namespace std;

#include "Monster.h"
#include "Behaviour.h"

Monster::~Monster() {
	delete(aI);
	main_field = 0;
}

Monster::Monster(Level* L, int ms, int mhp, std::string nm, std::string mt, //movement speed, hit points, name, monster type
			Point pos, Point size, int ca1, int ca2, int ca3, int gd, int fa, //position, size, custom attributes, gravity degree, facing angle
			char* animT, char* modelP, Point trans, bool anim, //animation table, model path, translation, animated?
			int lt, bool a, bool aa, bool cl) { //life time, active, always active, climbing?
	movement_speed = ms;
	aI = new MonsterAI(this);
	hp = mhp;
	name = nm; //where will this be derived from?
	monster_type = mt; //where will this be derived from?
	
	custom_attribute1 = ca1;
	custom_attribute2 = ca2;
	custom_attribute3 = ca3;
	gravity_degree = gd;
	facing_angle = fa;
	climbing = cl;
	main_field = new Field(this, pos, size, 2, modelP, L, lt, trans, anim, a, aa);
	if (anim)
		animator = new Animator(L->animation_tables.find(animT)->second, main_field->graphic_model_animated);
	else animator = 0;
}

unsigned int Monster::get_type() {
	return 2;
}

void Monster::act(double time) {
	Point p;
	Field* f;
	
	//Checking layer movement
	bool move_inwards = false;
	p.position_x = main_field->position.position_x;
	p.position_y = main_field->position.position_y - 10;
	p.layer = main_field->position.layer - 1;
	f = main_field->location->collision_Point(p);
	if ((f != 0) && (f->owner->get_type() == 4))
		move_inwards = true;

	bool move_outwards = false;
	p.position_x = main_field->position.position_x;
	p.position_y = main_field->position.position_y - 10;
	p.layer = main_field->position.layer + 1;
	f = main_field->location->collision_Point(p);
	if ((f != 0) && (f->owner->get_type() == 4))
		move_outwards = true;

	//Orientation
	double o = 0;
	if (facing_angle == 90)
		o = 1;
	else o = -1;

	//Checking obstackles
	bool obstackle_in_front = false;
	bool wall_in_front = false;
	bool jumpable_obstackle = false;
	bool climbable_front = false;
	p.position_x = main_field->position.position_x + o*10;
	p.position_y = main_field->position.position_y;
	p.layer = main_field->position.layer;
	f = main_field->location->collision_Point(p);
	if ((f != 0) && (f->owner->get_type() == 4))
	{
		if (f->owner->custom_attribute1 == 1)
			climbable_front = true;
		p.position_x = main_field->position.position_x + o*10;
		p.position_y = main_field->position.position_y + 10;
		p.layer = main_field->position.layer;
		f = main_field->location->collision_Point(p);
		if ((f != 0) && (f->owner->get_type() == 4))
			wall_in_front = true;
		else
		{
			obstackle_in_front = true;
			p.position_x = main_field->position.position_x + o*30;
			p.position_y = main_field->position.position_y - 10;
			p.layer = main_field->position.layer;
			f = main_field->location->collision_Point(p);
			if ((f != 0) && (f->owner->get_type() == 4))
				jumpable_obstackle = true;
		}
	}

	//Checking cliff
	bool cliff_in_front = false;
	bool can_climb_down = false;
	bool can_drop = false;
	bool can_jump = false;
	bool can_jump_climb = false;
	p.position_x = main_field->position.position_x + o*10;
	p.position_y = main_field->position.position_y - 10;
	p.layer = main_field->position.layer;
	f = main_field->location->collision_Point(p);
	if ((f == 0) || (f->owner->get_type() != 4))
	{
		cliff_in_front = true;
		p.position_x = main_field->position.position_x + o*2;
		p.position_y = main_field->position.position_y - 10;
		p.layer = main_field->position.layer;
		f = main_field->location->collision_Point(p);
		if (f->owner->custom_attribute1 == 1)
			can_climb_down = true;

		for (int i = 2; i < 6; i++)
		{
			p.position_x = main_field->position.position_x + o*20;
			p.position_y = main_field->position.position_y - i*10;
			p.layer = main_field->position.layer;
			f = main_field->location->collision_Point(p);
			if ((f != 0) && (f->owner->get_type() == 4))
			{
				can_drop = true;
				break;
			}
		}

		//Checking jump posiibility
		p.position_x = main_field->position.position_x + o*40;
		p.position_y = main_field->position.position_y + 10;
		p.layer = main_field->position.layer;
		f = main_field->location->collision_Point(p);
		if ((f != 0) && (f->owner->get_type() == 4))
			can_jump = true;
		p.position_x = main_field->position.position_x + o*50;
		p.position_y = main_field->position.position_y;
		p.layer = main_field->position.layer;
		f = main_field->location->collision_Point(p);
		if ((f != 0) && (f->owner->get_type() == 4))
			can_jump = true;
		p.position_x = main_field->position.position_x + o*50;
		p.position_y = main_field->position.position_y - 10;
		p.layer = main_field->position.layer;
		f = main_field->location->collision_Point(p);
		if ((f != 0) && (f->owner->get_type() == 4))
			can_jump = true;
		
		//Checking jump + climb posiibility
		p.position_x = main_field->position.position_x + o*20;
		p.position_y = main_field->position.position_y + 10;
		p.layer = main_field->position.layer;
		f = main_field->location->collision_Point(p);
		if ((f != 0) && (f->owner->get_type() == 4) && (f->owner->custom_attribute1 == 1))
			can_jump_climb = true;
		p.position_x = main_field->position.position_x + o*30;
		p.position_y = main_field->position.position_y + 20;
		p.layer = main_field->position.layer;
		f = main_field->location->collision_Point(p);
		if ((f != 0) && (f->owner->get_type() == 4) && (f->owner->custom_attribute1 == 1))
			can_jump_climb = true;
		p.position_x = main_field->position.position_x + o*40;
		p.position_y = main_field->position.position_y + 20;
		p.layer = main_field->position.layer;
		f = main_field->location->collision_Point(p);
		if ((f != 0) && (f->owner->get_type() == 4) && (f->owner->custom_attribute1 == 1))
			can_jump_climb = true;
		p.position_x = main_field->position.position_x + o*50;
		p.position_y = main_field->position.position_y + 10;
		p.layer = main_field->position.layer;
		f = main_field->location->collision_Point(p);
		if ((f != 0) && (f->owner->get_type() == 4) && (f->owner->custom_attribute1 == 1))
			can_jump_climb = true;
		p.position_x = main_field->position.position_x + o*60;
		p.position_y = main_field->position.position_y;
		p.layer = main_field->position.layer;
		f = main_field->location->collision_Point(p);
		if ((f != 0) && (f->owner->get_type() == 4))
			can_jump_climb = true;
	}

	if (move_inwards == true)
	{
		OutputDebugString(">> [AI]\n");
		OutputDebugString("I can move inwards.\n");
		OutputDebugString(">> /[AI]\n");
	}
	if (move_outwards == true)
	{
		OutputDebugString(">> [AI]\n");
		OutputDebugString("I can move outwards.");
		OutputDebugString(">> /[AI]\n");
	}
	if (obstackle_in_front == true)
	{
		OutputDebugString(">> [AI]\n");
		OutputDebugString("Obstackle in front.\n");
		if (climbable_front)
			OutputDebugString("CAN climb it.\n");
		if (jumpable_obstackle)
			OutputDebugString("CAN jump over it.\n");
		OutputDebugString(">> /[AI]\n");
	}
	if (wall_in_front == true)
	{
		OutputDebugString(">> [AI]\n");
		OutputDebugString("Wall in front.\n");
		if (climbable_front)
			OutputDebugString("CAN climb it.\n");
		OutputDebugString(">> /[AI]\n");
	}
	if (cliff_in_front == true)
	{
		OutputDebugString(">> [AI]\n");
		OutputDebugString("Cliff in front.\n");
		if (can_climb_down)
			OutputDebugString("CAN climb down.\n");
		if (can_drop)
			OutputDebugString("CAN drop down safely.\n");
		OutputDebugString(">> /[AI]\n");
	}
	aI->evaluate(time);
}

void Monster::remove() {
	main_field->location->remove_monster(main_field, this);
}