#ifndef __EventSE_h__
#define __EventSE_h__

#include "Point.h"
#include "Event.h"
#include "ValRetrieval.h"

class Point;
class Field;
class ValRetrieval;

class EventSE : public Event
{
	public:
		EventSE(Level* L, int it, Event* in, int ims, Point ipos,
			Point isize, Point ica, int i_hit_points, std::string i_name);
		void set1(int igd, int ifa, int imt, Point itrans, bool ianim, int ilt,
			bool ia, bool iaa, char* ianimT, char* imodelP);
		void set2(bool iload, bool iac, bool ilo, int iaid, int ias, int icurf,
			int iminf, int imaxf, bool iabs, bool ib, std::string imonster_type);

		int get_type();
		void invokeEvent(Field* source, Field* target);

		int type;
		Event* next;

		//Generic:
		int ms; //movement speed
		Point pos; //position
		Point size; //size
		int ca1; //custom attribute
		int ca2; //custom attribute
		int ca3; //custom attribute
		int gd; //gravity degree
		int fa; //facing angle
		int mt; //model type
		Point trans; //translation
		bool anim; //animated?
		int lt; //lifetime
		bool a; //active
		bool aa; //always active
		
		static const int animT_size = 15;
		char animT[animT_size]; //animation table
		static const int modelP_size = 50;
		char modelP[modelP_size]; //model path
		//Animator:
		bool load; //load or go with default value
		bool ac; //active
		bool lo; //looping
		int aid; //animation id
		int as; //animation speed
		int curf; //current frame
		int minf; //min frame
		int maxf; //max frame

		//Border
		bool abs; //absolute
		bool b; //bouncing
		//Monster
		int hit_points;
		std::string name;
		std::string monster_type;
};

#endif