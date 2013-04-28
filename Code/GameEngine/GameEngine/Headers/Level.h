#ifndef __Level_h__
#define __Level_h__

#include "AnimationTable.h"
#include "Entity.h"
#include "Point.h"
#include "Condition.h"
#include "AIPoint.h"
#include "Action.h"

#include "Background.h"
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
		std::list<AIPoint*> aipoints;
		std::vector<Action*> actions;
		
		Background* bg_sky;
		Background* bg_trees;
		Background* bg_beach;

		void add_event(std::string init);
		void add_border(Point start, Point size);
		void add_monster(std::string init, Point position = Point(), Point size = Point(5.0, 10.0, 1.0));
		void add_item(std::string init, Point position = Point(), Point size = Point(5.0, 5.0, 1.0));
		void add_bgobject(Point start);

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
