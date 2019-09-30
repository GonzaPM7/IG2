#pragma once
#include "Obj.h"
#include <vector>
#include <OgreInput.h>
#include <OgreEntity.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>

class Muneco:public OgreBites::InputListener
{
protected:
	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM;

public:
	Muneco(Ogre::SceneNode* node);
	void SetPosition(int x, int y, int z);
	void SetRotation(int angle);
};

