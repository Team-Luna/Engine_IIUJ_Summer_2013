using namespace std;

#include "Animator.h"
///Code for class Animator functions
Animator::Animator(std::string Path, scene::IAnimatedMeshSceneNode* Model)
{
	graphic_model = Model;
	animSpeed = 15;
	active = true;
	setAnimation(0);
}

void Animator::check()
{
	if (!active)
		return;
	if (graphic_model->getFrameNr() == maxFrame)
	{
		if (looping)
			setAnimation(animID);
		else
		{
			active = false;
			animSpeed = 0;
		}
	}
}

int Animator::getAnimation()
{
	return animID;
}

void Animator::setAnimation(int As)
{
	srand((unsigned)time(0));
	int random = rand()%3;
	switch (As)
	{
	//Idle
	case 0:
		animID = 0;
		looping = true;
		if (random == 0)
		{
			minFrame = 183;
			maxFrame = 204;
		}
		if (random == 1)
		{
			minFrame = 205;
			maxFrame = 249;
		}
		if (random == 2)
		{
			minFrame = 250;
			maxFrame = 299;
		}
		break;
	//Walk
	case 1:
		animID = 1;
		looping = true;
		minFrame = 0;
		maxFrame = 13;
		break;
	default:
		break;
	}
	graphic_model->setFrameLoop(minFrame, maxFrame);
	graphic_model->setAnimationSpeed(animSpeed);
}

void Animator::setSpeed(int As)
{
	animSpeed = As;
}

void Animator::stop()
{
	if (graphic_model == 0)
		return;
	graphic_model->setAnimationSpeed(0);
	active = false;
}

void Animator::resume()
{
	if (graphic_model == 0)
		return;
	graphic_model->setAnimationSpeed(animSpeed);
	active = true;
}