#pragma once
#include "Obj.h"
#include <vector>
#include <OgreInput.h>
#include <OgreEntity.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include "EntidadIG.h"

class Sinbad :public EntidadIG
{
private:
	bool running = false;
	bool dead = false;
	Ogre::AnimationState* danceState;
	Ogre::AnimationState* runbaseState;
	Ogre::AnimationState* runtopState;

	Ogre::AnimationState* movingState;
	Ogre::AnimationState* bombState;

	Ogre::Entity* ent;
	Ogre::Entity* sword1;
	Ogre::Entity* sword2;

public:
	Sinbad(Ogre::SceneNode* node);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual void frameRendered(const Ogre::FrameEvent& evt);
	virtual void receiveEvent(EntidadIG* entidad);
};

