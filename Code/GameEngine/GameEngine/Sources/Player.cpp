#include "Player.h"
#include <exception>

using namespace std;

Player::~Player() {
	main_field = 0;
}

Player::Player() {
	movement_speed = 5;
	hp = 100;
	lifes = 3;
	grounded = false;

	//Entity:
	custom_attribute1 = 0;
	custom_attribute2 = 0;
	custom_attribute3 = 0;
	gravity_degree = 100;
	facing_angle = 90;
	main_field = 0;
	animator = 0;
}

Player::Player(Level* L, int ms, int php, int l, Point pos, Point size, //level, movement speed, hit points, position, size
				int ca1, int ca2, int ca3, int gd, int fa, char* animT,//custom attributes, gravity degree, facing angle, animation table
				char* modelP, Point trans, bool anim, bool cl) { //model path, translation, animated?, climbing?
	movement_speed = (float)ms;
	hp = php;
	lifes = l;
	grounded = false;

	//Entity:
	custom_attribute1 = ca1;
	custom_attribute2 = ca2;
	custom_attribute3 = ca3;
	gravity_degree = gd;
	facing_angle = fa;
	climbing = cl;
	main_field = new Field(this, pos, size, 1, modelP, L, -1, trans, anim, true, true);
	if (anim)
		animator = new Animator(L->animation_tables.find(animT)->second, main_field->graphic_model_animated);
	else animator = 0;
}

unsigned int Player::get_type() {
	return 1;
}

void Player::remove() {
	main_field->location->remove_player(main_field);
}