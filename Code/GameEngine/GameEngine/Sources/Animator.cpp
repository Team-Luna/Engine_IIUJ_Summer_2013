#include "Animator.h"

Animator::Animator(AnimationTable* Table, scene::IAnimatedMeshSceneNode* Model)
{
	animTable = Table;
	graphic_model = Model;
	animSpeed = 15;
	active = true;
	setAnimation(0);
}

void Animator::check()
{
	if (!active)
		return;
	if (graphic_model->getEndFrame()-1 < graphic_model->getFrameNr())
	{
		if (looping)
			setAnimation(animID);
		else
			stop();
	}
}

double Animator::checkProgress() {
	double current = graphic_model->getFrameNr() - graphic_model->getStartFrame();
	current /= graphic_model->getEndFrame() - graphic_model->getStartFrame();
	return abs(current);
}

int Animator::getAnimation()
{
	return animID;
}

void Animator::setAnimation(int As)
{
	resume();
	active = true;
	//If no change is needed, skip the rest
	if ((animID == As) && (animTable->size[As] < 2))
		return;
	animID = As;
	//Check if the animation is looping
	looping = false;
	if (As == 0)
		looping = true;
	if (As == 1)
		looping = true;
	if (As == 2)
		looping = true;
	if (As == 10)
		looping = true;
	
	//Set the new cycle
	int minFrame = graphic_model->getFrameNr();
	int maxFrame = graphic_model->getFrameNr();
	if (0 < animTable->size[As])
	{
		int random = rand()%(animTable->size[As]);

		minFrame = animTable->animation[As][random*2];
		maxFrame = animTable->animation[As][random*2+1];
	}
	graphic_model->setFrameLoop(minFrame, maxFrame);
	graphic_model->setCurrentFrame(minFrame);
	graphic_model->setAnimationSpeed(animSpeed);
}

void Animator::setSpeed(int As)
{
	animSpeed = As;
	graphic_model->setAnimationSpeed(animSpeed);
}

void Animator::stop()
{
	graphic_model->setAnimationSpeed(0);
	active = false;
}

void Animator::resume()
{
	graphic_model->setAnimationSpeed(animSpeed);
	active = true;
}

void Animator::set(bool ac, bool lo, int aid, int as, int curf, int minf, int maxf)
{
	active = ac;
	looping = lo;
	animID = aid;
	animSpeed = as;
	
	if (!active)
		graphic_model->setAnimationSpeed(0);
	else
		graphic_model->setAnimationSpeed(animSpeed);
	graphic_model->setFrameLoop(minf, maxf);
	graphic_model->setCurrentFrame(curf);
}