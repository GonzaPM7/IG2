#pragma once

#include "Obj.h"
#include <OgreInput.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <string>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <OgreSceneNode.h>

class Aspa: public OgreBites::InputListener
{
private:
	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM;

	Ogre::SceneNode* tablonIzquierdo;
	Ogre::SceneNode* tablonDerecho;
	Ogre::SceneNode* cangilon;
public:
	Aspa(Ogre::SceneNode* node);
	Ogre::SceneNode* getNode();
	void rotateBox(int angle);
		
	
};

