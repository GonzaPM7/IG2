#pragma once
#include <OgreInput.h>
#include <OgreEntity.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>

class EntidadIG: public OgreBites::InputListener
{
public:
	EntidadIG(Ogre::SceneNode* node);
	~EntidadIG();

	static std::vector<EntidadIG*> appListeners;
	static void addListener(EntidadIG* entidad);
	Ogre::SceneNode* getNode();
protected:
	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM;

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
};

