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
	Ogre::AnimationState* danceState;
	Ogre::AnimationState* runbaseState;
	Ogre::AnimationState* runtopState;

	Ogre::Entity* ent;
	Ogre::Entity* sword1;
	Ogre::Entity* sword2;

public:
	Sinbad(Ogre::SceneNode* node);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual void frameRendered(const Ogre::FrameEvent& evt);
};

