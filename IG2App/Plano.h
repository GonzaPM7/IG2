#pragma once
#include <OgreInput.h>
#include <OgreEntity.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include "EntidadIG.h"

class Plano : public EntidadIG
{
private:
	bool moving = true;
public:
	Plano(Ogre::SceneNode* node);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

};

