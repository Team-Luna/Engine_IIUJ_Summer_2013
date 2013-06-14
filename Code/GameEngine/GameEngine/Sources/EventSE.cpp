#include "EventSE.h"
#include <Windows.h>

EventSE::EventSE(Level* L, int it, Event* in, int ims, Point ipos,
	Point isize, Point ica, int i_hit_points, std::string i_name)
{
	location = L;
	type = it; //type (of entity)
	next = in;

	//Generic
	ms = ims; //movement speed
	pos = ipos; //position
	size = isize; //size
	ca1 = ica.position_x; //custom attribute
	ca2 = ica.position_y; //custom attribute
	ca3 = ica.layer; //custom attribute
	//Monster
	hit_points = i_hit_points; //hit points
	name = i_name; //monster name
}

void EventSE::set1(int igd, int ifa, int imt, Point itrans, bool ianim, int ilt,
	bool ia, bool iaa, char* ianimT, char* imodelP)
{
	gd = igd; //gravity degree
	fa = ifa; //facing angle
	mt = imt; //model type
	trans = itrans; //translation
	anim = ianim; //animated?
	lt = ilt; //lifetime
	a = ia; //active
	aa = iaa; //always active

	for (int i = 0; i < animT_size; i++)
		animT[i] = ianimT[i]; //animation table
	for (int i = 0; i < modelP_size; i++)
		modelP[i] = imodelP[i]; //model path
}

void EventSE::set2(bool iload, bool iac, bool ilo, int iaid, int ias, int icurf,
	int iminf, int imaxf, bool iabs, bool ib, std::string imonster_type)
{
	//Animator:
	load = iload; //load or go with default value
	ac = iac; //active
	lo = ilo; //looping
	aid = iaid; //animation id
	as = ias; //animation speed
	curf = icurf; //current frame
	minf = iminf; //min frame
	maxf = imaxf; //max frame

	//Border
	abs = iabs; //absolute
	b = ib; //bouncing
	//Monster
	monster_type = imonster_type;
}

int EventSE::get_type()
{
	return 2;
}

void EventSE::invokeEvent(Field* source, Field* target)
{
	if (type == 2)
		location->add_monster(this);
	if (type == 3)
		location->add_item(this);
	if (type == 4)
		location->add_border(this);
}

