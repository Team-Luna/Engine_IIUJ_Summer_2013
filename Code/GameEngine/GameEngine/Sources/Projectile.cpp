#include "Projectile.h"

Projectile::Projectile(Level* L, double ms, Point pos,
			char* animT, char* modelP, bool anim, Event* cr, bool ip, bool im,
			bool it, bool ib, double et, bool h)
{
	movement_speed = (float)ms;
	
	custom_attribute1 = 0;
	custom_attribute2 = 0;
	custom_attribute3 = 0;
	gravity_degree = 0;
	facing_angle = 90;
	main_field = new Field(this, pos, Point(1, 1, 0.1), 5, modelP, L, -1, Point(), anim, true, true);
	if (anim)
		animator = new Animator(L->animation_tables.find(animT)->second, main_field->graphic_model_animated);
	else animator = 0;
}

unsigned int Projectile::get_type() {
	return 5;
}

void Projectile::remove() {
	main_field->location->remove_projectile(main_field, this);
}