#ifndef __BgMovableObject_h__
#define __BgMovableObject_h__

#include "Point.h"
#include "Level.h"
#include <exception>
#include <irrlicht.h>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Level;
class BgMovableObject;

class BgMovableObject
{
	public:
		~BgMovableObject();
		BgMovableObject(Level* L,Point position, Point scale,  char* TexturePath, int t, Point mov);
		void move(Level* L);
	private:
		Point movement;
		int type;
		scene::ISceneNode* graphic_model;
};

#endif