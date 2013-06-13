#ifndef __Background_h__
#define __Background_h__

#include "Entity.h"
#include "Point.h"
#include "Condition.h"

#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "Border.h"
#include <exception>
#include <irrlicht.h>
#include <string>
#include <list>
#include <map>
#include <iostream>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Player;
class Background;

class Background
{
	
	irr::f32 speedHorizontal;
	irr::f32 speedInwards;
	float playerMovementSpeed;
	irr::f32 SizeX,SizeD;
	Background* temp;

public:
	ISceneNode* cubes;
	Background(void);
	Background(Level* L, vector3df Size, vector3df Position, bool Transparency, char* TexturePath, irr::f32 SpeedHorizontal, irr::f32 SpeedInwards);
	~Background(void);

	ISceneNode* generateSingleCube(Level* L, vector3df Size, vector3df Position, bool Transparency, char* TexturePath, irr::f32 SpeedHorizontal, irr::f32 SpeedInwards);
	

	irr::f32 getSpeedHorizontal();
	irr::f32 getSpeedInwards();
	vector3df getPosition();

	void setSpeedHorizontal(irr::f32 newSpeed);
	void setSpeedInwards(irr::f32 newSpeed);

	void moveLeft(Level* L);
	void moveRight(Level* L);
	void moveInwards();  // ruch wglab ekranu (w kierunku tla)
	void moveOutwards();  // ruch w przeciwnym kierunku co Inwards ;)
};
#endif
