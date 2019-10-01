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

class Muneco:public EntidadIG
{
protected:
public:
	Muneco(Ogre::SceneNode* node);
	void SetPosition(int x, int y, int z);
	void SetRotation(int angle);
};

