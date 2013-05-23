#pragma once
#include "Level.h"

class HUD
{
	Level* level;
	IrrlichtDevice* device;
	IVideoDriver* driver;

public:
	HUD(Level* lvl, IrrlichtDevice* dvc);

	void drawHUD();

	~HUD(void);
};

