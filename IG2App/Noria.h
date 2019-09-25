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

class Noria : public OgreBites::InputListener
{
private:
	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM;

	int numeroAspas;
	std::vector<Aspa> aspas;
	Ogre::SceneNode* cilindro;
	
public:
	Noria(Ogre::SceneNode* node, int nAspas);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

};

