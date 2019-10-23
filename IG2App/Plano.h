#pragma once
#include <OgreInput.h>
#include <OgreEntity.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include "EntidadIG.h"
#include <OgreEntity.h>
#include <OgreSubEntity.h>
#include <OgreTechnique.h>
#include <OgreCamera.h>
#include <OgreMovablePlane.h>
#include <OgreTextureManager.h>
#include <OgreViewport.h>
#include <OgreHardwarePixelBuffer.h>
#include <OgreRenderWindow.h>
#include <OgreRenderTexture.h>
using namespace Ogre;

class Plano : public EntidadIG
{
private:
	bool moving = true;
public:
	Plano(Ogre::SceneNode* node, Camera* cam);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual void receiveEvent(EntidadIG* entidad);
protected:
	Ogre::Entity* planoEnt;

};

