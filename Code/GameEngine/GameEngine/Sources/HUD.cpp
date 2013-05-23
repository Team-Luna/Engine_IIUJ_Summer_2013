#include "HUD.h"

HUD::HUD(Level* lvl, IrrlichtDevice* dvc)
{
	level = lvl;
	device = dvc;
	IVideoDriver* driver = device->getVideoDriver();
}

void HUD::drawHUD()
{
	gui::IGUIFont* font = device->getGUIEnvironment()->getFont("../media/Levenim14.png");

	irr::core::stringw livesString = "Lives: ";
	livesString.append(irr::core::stringw(level->player->lifes));

	irr::core::stringw hpString = "HP: ";
	hpString.append(irr::core::stringw(level->player->hp));

	font->draw(livesString,
		core::rect<s32>(20,10,70,30),
		video::SColor(255,255,255,255),false,true);
	font->draw(hpString,
		core::rect<s32>(20,35,70,55),
		video::SColor(255,255,255,255),false,true);
}

HUD::~HUD(void)
{
}
