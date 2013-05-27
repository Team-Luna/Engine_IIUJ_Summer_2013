#ifndef __Level_h__
#define __Level_h__

#include "AnimationTable.h"
#include "Entity.h"
#include "Point.h"

#include "ValRetrieval.h"

#include "Condition.h"
#include "ConditionComplex.h"
#include "ConditionCompare.h"
#include "ConditionPoint.h"

#include "Action.h"
#include "ActionUnit.h"
#include "ActionEvaluate.h"
#include "ActionWait.h"
#include "ActionIfThenElse.h"
#include "ActionLoop.h"

#include "AITable.h"

#include "Background.h"
#include "Behaviour.h"
#include "BgMovableObject.h"
#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "Border.h"
#include <exception>
#include <irrlicht.h>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>


using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

using namespace std;

class Background;
class BgMovableObject;
class Player;
class Point;
class Field;
class Item;
class Event;
class Monster;
class Border;
class Level;

class Level
{
	public:
		Level(IrrlichtDevice* Device, char* path);

		//irrlicht data
		IrrlichtDevice *device;
		IVideoDriver* driver;
		ISceneManager* smgr;
		IGUIEnvironment* guienv;

		Point start; //Top left corner
		Point size;
		Point respawn;
		Point active_range;
		Player* player;
		int custom_attribute1;
		int custom_attribute2;
		int custom_attribute3;
		std::map< std::string, AnimationTable* > animation_tables;
		std::map< std::string, Event* > event_dictionary;
		double gravity;
		int lc_interval;
		float delta_time;
		std::map< std::string, Condition* > conditions;
		std::map< std::string, Action* > actions;
		std::map< std::string, AITable* > action_tables;
		
		Background* bg_sky;
		Background* bg_trees;
		Background* bg_beach;

		void add_event(std::string init);
		void add_border(Point start, Point size);
		void add_monster(std::string init, Point position = Point(), Point size = Point(5.0, 10.0, 1.0));
		void add_item(std::string init, Point position = Point(), Point size = Point(5.0, 5.0, 1.0));
		void add_bgobject(Point start);

		void turn_around(Field* field);
		void move_forward(Field* field);
		void jump_forward(Field* field);
		void jump_backwards(Field* field);
		void climb_upwards(Field* field);
		void climb_downwards(Field* field);
		void attack(Field* field);
		void shoot(Field* field);
		void idle(Field* field);
		void stop(Field* field, bool grounded);

		void advance_frame(ICameraSceneNode *cam);
		bool collision_detect(Field* source);
		Field* collision_Point(Point p);
		
		void move_field(Field* field);
		void demove_field(Field* field);
		
		void remove_player(Field* field);
		void remove_border(Field* field, Border* entity);
		void remove_monster(Field* field, Monster* entity);
		void remove_item(Field* field, Item* entity);
		void remove_bgobject(BgMovableObject* entity);
		
		void trash(Field* field);
		void process_key(irr::EKEY_CODE keycode);

		double retrieveValue(int type, Field* From, Field* To);

	private:
		std::list<Field*> fields;
		std::list<Field*> garbage;
		std::list<Item*> items;
		std::list<BgMovableObject*> bgobjects;
		int time_left;
		std::list<Monster*> monsters;
		std::list<Border*> boundaries;
		inline std::string getNextRelevantLine(ifstream& infile);
		void extractValues(std::string source, double* output);
};

#endif
