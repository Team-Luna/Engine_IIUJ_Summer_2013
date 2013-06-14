#include "Field.h"
#include <exception>
#include <iostream>
using namespace std;
#include "Windows.h"

Field::~Field() {
	//owner already destroyed, no need to do this
	owner = 0;
	collision_effect = 0;
	destroy_event = 0;
	if (graphic_model == 0)
		graphic_model_animated->remove();
	else graphic_model->remove();
	graphic_model = 0;
	graphic_model_animated = 0;
}

Field::Field(Entity* O, Point P, Point S, int model_type, char* Path, //owner, position, size, type, file path
		Level* L, int lifetime, Point trans, bool anim, //level, lifetime, translation, animated?
		bool a, bool aa) { //active, always active
	owner = O;
	if (owner != 0)
		type = O->get_type();
	else type = 0;
	movement_type = 'u'; //unknown, I assume it's based on type?
	position = P;
	size = S;
	time_left = lifetime;

	collision_effect = 0;
	velocity = Point();
	movement_point = Point();
	destroy_event = 0;
	destroy_at_stop = false;
	location = L;
	translation = trans;
	active = a;
	always_active = aa;

	if (owner == 0)
	{
		graphic_model = 0;
		graphic_model_animated = 0;
		return;
	}
	if (anim)
	{
		graphic_model = 0;
		
		graphic_model_animated = L->smgr->addAnimatedMeshSceneNode(L->smgr->getMesh(Path));
		graphic_model_animated->setMaterialFlag(video::EMF_LIGHTING, false);
		graphic_model_animated->setFrameLoop(205, 249);
		graphic_model_animated->setAnimationSpeed(15);

		graphic_model_animated->setPosition(core::vector3df(position.position_x + translation.position_x,
		position.position_y + translation.position_y, position.layer + translation.layer));
		graphic_model_animated->setScale(core::vector3df(1.0, 1.0, 1.0));
		graphic_model_animated->setRotation(core::vector3df(0,O->facing_angle,0));
	}
	else
	{
		if (model_type == 4)
			graphic_model = L->smgr->addCubeSceneNode();
		else
			graphic_model = L->smgr->addSphereSceneNode();
		graphic_model->setMaterialTexture(0, L->driver->getTexture(Path));
		graphic_model->setMaterialFlag(video::EMF_LIGHTING, false);
	
		graphic_model->setPosition(core::vector3df(position.position_x + translation.position_x,
			position.position_y + translation.position_y, position.layer + translation.layer));
		graphic_model->setScale(core::vector3df(size.layer, size.position_y/10, size.position_x/10));
		graphic_model->setRotation(core::vector3df(0,O->facing_angle,0));

		graphic_model_animated = 0;
	}
}

void Field::rescale(Point to_size) {
	//Function specifically for rescaling graphic model, does not affect object size
	if (graphic_model != 0)
		graphic_model->setScale(core::vector3df(to_size.position_x, to_size.position_y, to_size.layer));
	if (graphic_model_animated != 0)
		graphic_model_animated->setScale(core::vector3df(to_size.position_x, to_size.position_y, to_size.layer));
}


void Field::update() {
	//Updating active status
	if (!always_active)
	{
		double difx = abs(position.position_x - location->player->main_field->position.position_x);
		double dify = abs(position.position_y - location->player->main_field->position.position_y);
		if ((difx <= location->active_range.position_x) && (dify <= location->active_range.position_y))
			active = true;
		else active = false;
	}
	if (!always_active && !active)
		return;
	
	//Updating unit position based on velocity, detecting collision
	location->move_field(this);
	/*
	if (location->collision_detect(this))
	{
		location->demove_field(this);
		velocity.position_x = 0;
		velocity.position_y = 0;
	}
	*/

	//Updating animation
	if (this->owner != 0)
		if (this->owner->animator != 0)
			this->owner->animator->check();
	
	//Updating Model position/rotation
	if (graphic_model != 0) {
		graphic_model->setPosition(core::vector3df(position.position_x + translation.position_x,
			position.position_y + translation.position_y, (position.layer - 1 + translation.layer)*10));
		if (this->owner != 0)
			graphic_model->setRotation(core::vector3df(0,this->owner->facing_angle,0));
	}
	if (graphic_model_animated != 0) {
		graphic_model_animated->setPosition(core::vector3df(position.position_x + translation.position_x,
			position.position_y + translation.position_y, (position.layer - 1 + translation.layer)*10));
		if (this->owner != 0)
			graphic_model_animated->setRotation(core::vector3df(0,this->owner->facing_angle,0));
	}

	//Handling gravity
	if (this->owner)
		if (this->owner->custom_attribute1 != 1)
			velocity.position_y -= location->gravity*location->delta_time*this->owner->gravity_degree/100;

	//Handling life time
	if (time_left == 0)
		if (destroy_at_stop)
			location->trash(this);
		else time_left--;
		//owner->remove();
	if (time_left > 0)
		time_left--;
}

void Field::move_line(Point speed, int time) {
	throw "Not yet implemented";
}

void Field::move_circle(Point speed, Point center, int time) {
	throw "Not yet implemented";
}

