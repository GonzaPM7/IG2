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
#include <OgreParticleSystem.h>

class Bomb :
	public EntidadIG
{
private:
	Ogre::AnimationState* animationState;
	bool animActive = true;
	Ogre::ParticleSystem* ps;
public:
	Bomb(Ogre::SceneNode* node);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual void frameRendered(const Ogre::FrameEvent& evt);
	virtual void receiveEvent(EntidadIG* entidad);

};

