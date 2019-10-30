#include "Sinbad.h"
#include <OgreFrameListener.h>

Sinbad::Sinbad(Ogre::SceneNode* node): EntidadIG(node)
{
	Ogre::SceneNode* sinbadNode = mNode->createChildSceneNode("sinbad");
	ent = mSM->createEntity("Sinbad.mesh");
	sinbadNode->attachObject(ent);

	sinbadNode->setScale(50, 50, 50);
	sinbadNode->setPosition(800, 250, -800);

	sword1 = mSM->createEntity("Sword.mesh");
	ent->attachObjectToBone("Sheath.R", sword1);
	
	sword2 = mSM->createEntity("Sword.mesh");
	ent->attachObjectToBone("Sheath.L", sword2);

	danceState = ent->getAnimationState("Dance");
	danceState->setEnabled(true);
	danceState->setLoop(true);

	runbaseState = ent->getAnimationState("RunBase");
	runtopState = ent->getAnimationState("RunTop");
	runbaseState->setLoop(true);
	runtopState->setLoop(true);

	
	
}

bool Sinbad::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_c)
	{
		if (running)
		{
			danceState->setEnabled(true);
			runbaseState->setEnabled(false);
			runtopState->setEnabled(false);
			ent->detachObjectFromBone(sword1);
			ent->attachObjectToBone("Sheath.R", sword1);
		}
		else
		{
			danceState->setEnabled(false);
			runbaseState->setEnabled(true);
			runtopState->setEnabled(true);	
			ent->detachObjectFromBone(sword1);
			ent->attachObjectToBone("Handle.R", sword1);
		}
		running = !running;
	}
	return true;
}

void Sinbad::frameRendered(const Ogre::FrameEvent& evt)
{
	danceState->addTime(evt.timeSinceLastFrame);
	runbaseState->addTime(evt.timeSinceLastFrame);
	runtopState->addTime(evt.timeSinceLastFrame);
}
