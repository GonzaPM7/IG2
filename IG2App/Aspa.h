#pragma once

#include "Obj.h"
#include <OgreInput.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <string>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <OgreSceneNode.h>
#include "EntidadIG.h"

class Aspa: public EntidadIG
{
private:
	Ogre::SceneNode* tablonIzquierdo;
	Ogre::SceneNode* tablonDerecho;
	Ogre::SceneNode* cangilon;
public:
	Aspa(Ogre::SceneNode* node);
	void rotateBox(int angle);
		
	
};

