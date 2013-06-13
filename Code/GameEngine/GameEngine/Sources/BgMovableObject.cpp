#include "BgMovableObject.h"
#include <exception>

BgMovableObject::~BgMovableObject(){

}

BgMovableObject::BgMovableObject(Level* L, Point position, Point scale, char* TexturePath, int t, Point mov){

	movement=mov;
	type = t;
	IVideoDriver* driver = L->driver;
	ISceneManager* smgr = L->smgr;

	graphic_model= smgr->addCubeSceneNode();
	graphic_model->setMaterialFlag(video::EMF_LIGHTING, true);
	graphic_model->setMaterialTexture(0, driver->getTexture(TexturePath));
	graphic_model->setMaterialFlag(video::EMF_LIGHTING, false);
		
	graphic_model->setPosition(core::vector3df(position.position_x, position.position_y, position.layer));
	graphic_model->setScale(core::vector3df(scale.position_x, scale.position_y, scale.layer));
	graphic_model->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
}

void BgMovableObject::move(Level* L){


	switch(type){
		case 1:	
				if (graphic_model->getPosition().X > (L->player->main_field->position.position_x -150))
					graphic_model->setPosition(graphic_model->getPosition() - vector3df(movement.position_x, 0, 0)); 
				else
					graphic_model->setPosition(vector3df((L->player->main_field->position.position_x +150), graphic_model->getPosition().Y, graphic_model->getPosition().Z));
				break;
		case 2:
				if (graphic_model->getPosition().X > (L->player->main_field->position.position_x -150)){
					if (graphic_model->getPosition().Y > -100)
						graphic_model->setPosition(graphic_model->getPosition() - vector3df(movement.position_x, movement.position_y, 0)); 
					else
						graphic_model->setPosition(vector3df(graphic_model->getPosition().X, 100, graphic_model->getPosition().Z));
				}else
					graphic_model->setPosition(vector3df((L->player->main_field->position.position_x +150), graphic_model->getPosition().Y, graphic_model->getPosition().Z));
				break;
	}			

}
