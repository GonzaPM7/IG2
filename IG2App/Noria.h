#pragma once
#include "Obj.h"
#include "Aspa.h"
#include <vector>
#include <OgreInput.h>
#include <OgreEntity.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include "EntidadIG.h"

class Noria : public EntidadIG
{
protected:
	int numeroAspas;
	std::vector<Aspa> aspas;
	Ogre::SceneNode* cilindro;
	bool moving = true;
	
public:
	Noria(Ogre::SceneNode* node, int nAspas);	
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual void frameRendered(const Ogre::FrameEvent& evt);
};

