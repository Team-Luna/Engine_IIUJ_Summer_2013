#ifndef __Animator_h__
#define __Animator_h__

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <exception>
#include <irrlicht.h>

using namespace std;

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Field;
///Declarations for class Animator
class Animator
{
	public:
		Animator(std::string Path, scene::IAnimatedMeshSceneNode* Model);

		void check();
		int getAnimation();
		void setAnimation(int As);
		void setSpeed(int As);
		void stop();
		void resume();
	private:
		bool active;
		bool looping;
		int animID;
		int animSpeed;
		int minFrame;
		int maxFrame;
		scene::IAnimatedMeshSceneNode* graphic_model;
};

#endif
