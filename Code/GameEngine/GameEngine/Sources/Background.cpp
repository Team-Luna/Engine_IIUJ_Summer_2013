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
	SizeX=Size.X*10;
	if(SizeX<800)
		SizeD=800;
	else
		SizeD=SizeX;


	temp=this;
	speedHorizontal = SpeedHorizontal;
	speedInwards = SpeedInwards;
	playerMovementSpeed = L->player->movement_speed;

<<<<<<< HEAD
	irr:f32 initialHorizontalPosition = Position.X;
	cubes = generateSingleCube(L, Size, vector3df(initialHorizontalPosition+Size.X*10*0,Position.Y,Position.Z), Transparency, TexturePath, speedHorizontal, speedInwards);
=======
	irr::f32 initialHorizontalPosition = Position.X;

	for(int i=0; i<10; i++)
	{
		cubes[i] = generateSingleCube(Size, vector3df(initialHorizontalPosition+Size.X*10*i,Position.Y,Position.Z), Transparency, TexturePath, speedHorizontal, speedInwards, Device, plr);
	}
>>>>>>> origin/AI-Development

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

vector3df Background::getPosition()
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


void Background::moveLeft(Level* L)
{
	for (std::list<Background*>::iterator i=L->backgrounds.begin(); i!=L->backgrounds.end(); i++)
		if (((*i)->cubes->getPosition().Z==temp->cubes->getPosition().Z)&&((*i)->cubes->getPosition().X>temp->cubes->getPosition().X))
			temp=(*i);


	if (cubes->getPosition().X > (L->player->main_field->position.position_x -SizeD))
		cubes->setPosition(cubes->getPosition()+vector3df((-1)*speedHorizontal,0,0)*(playerMovementSpeed/10));
	else
		cubes->setPosition(vector3df((temp->cubes->getPosition().X +SizeX-(SizeX/100)),cubes->getPosition().Y,cubes->getPosition().Z));
}

void Background::moveRight(Level* L)
{
	for (std::list<Background*>::iterator i=L->backgrounds.begin(); i!=L->backgrounds.end(); i++)
		if (((*i)->cubes->getPosition().Z==temp->cubes->getPosition().Z)&&((*i)->cubes->getPosition().X<temp->cubes->getPosition().X))
			temp=(*i);

	if (cubes->getPosition().X < (L->player->main_field->position.position_x +SizeD))
		cubes->setPosition(cubes->getPosition()+vector3df(speedHorizontal,0,0)*(playerMovementSpeed/10));
	else
		cubes->setPosition(vector3df((temp->cubes->getPosition().X -SizeX+(SizeX/100)),cubes->getPosition().Y,cubes->getPosition().Z));
}

void Background::moveInwards()
{	
		cubes->setPosition(cubes->getPosition()+vector3df(0,speedInwards,0)*(playerMovementSpeed/10));
}

void Background::moveOutwards()
{
		cubes->setPosition(cubes->getPosition()+vector3df(0,(-1)*speedInwards,0)*(playerMovementSpeed/10));
}