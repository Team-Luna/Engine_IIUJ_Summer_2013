#include "Background.h"
#include <exception>
#include <string>
#include <list>
#include <map>

Background::Background(void)
{
}

Background::Background(Level* L, vector3df Size, vector3df Position, bool Transparency, char* TexturePath, irr::f32 SpeedHorizontal, irr::f32 SpeedInwards)
{
	speedHorizontal = SpeedHorizontal;
	speedInwards = SpeedInwards;
	playerMovementSpeed = L->player->movement_speed;

	irr:f32 initialHorizontalPosition = Position.X;
	cubes = generateSingleCube(L, Size, vector3df(initialHorizontalPosition+Size.X*10*0,Position.Y,Position.Z), Transparency, TexturePath, speedHorizontal, speedInwards);

}

Background::~Background(void)
{
}

ISceneNode* Background::generateSingleCube(Level* L, vector3df Size, vector3df Position, bool Transparency, char* TexturePath, irr::f32 SpeedHorizontal, irr::f32 SpeedInwards)
{
	IVideoDriver* driver = L->device->getVideoDriver();
	ISceneManager* smgr = L->device->getSceneManager();

	ISceneNode* cube = smgr->addCubeSceneNode();
	cube->setScale(Size);
	cube->setPosition(Position);

	cube->setMaterialTexture(0,driver->getTexture(TexturePath));
	cube->setMaterialFlag(video::EMF_LIGHTING, false);
	if(Transparency) cube->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);

	return cube;
}


irr::f32 Background::getSpeedHorizontal()
{
	return speedHorizontal;
}

irr::f32 Background::getSpeedInwards()
{
	return speedInwards;
}

vector3df Background::getPosition(int i)
{
	return cubes->getPosition();
}


void Background::setSpeedHorizontal(irr::f32 newSpeed)
{
	speedHorizontal = newSpeed;
}

void Background::setSpeedInwards(irr::f32 newSpeed)
{
	speedInwards = newSpeed;
}


void Background::moveLeft()
{
	for(int i=0; i<10; i++)
	{
		cubes->setPosition(cubes->getPosition()+vector3df((-1)*speedHorizontal,0,0)*(playerMovementSpeed/10));
	}
}

void Background::moveRight()
{
	for(int i=0; i<10; i++)
	{
		cubes->setPosition(cubes->getPosition()+vector3df(speedHorizontal,0,0)*(playerMovementSpeed/10));
	}
}

void Background::moveInwards()
{	
	for(int i=0; i<10; i++)
	{
		cubes->setPosition(cubes->getPosition()+vector3df(0,speedInwards,0)*(playerMovementSpeed/10));
	}
}

void Background::moveOutwards()
{
	for(int i=0; i<10; i++)
	{
		cubes->setPosition(cubes->getPosition()+vector3df(0,(-1)*speedInwards,0)*(playerMovementSpeed/10));
	}
}