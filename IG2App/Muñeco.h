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
	bool moving = true;
	bool forward = true;
	bool forwardhead = true;
	int speed = 5;
	int headspeed = 2;
	int angle = 0;
	bool rojo = false;
public:
	Muneco(Ogre::SceneNode* node, bool nouse);
	void SetPosition(int x, int y, int z);
	void SetRotation(int angle);

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual void frameRendered(const Ogre::FrameEvent& evt);
};

