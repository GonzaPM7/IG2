#include "Obj.h"

Obj::Obj(Ogre::SceneNode* node)
{
	mNode = node;
	mSM = mNode->getCreator();
}

Obj::~Obj()
{

}

bool Obj::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_e )
	{ 
	}
	return true;
}

void Obj::frameRendered(const Ogre::FrameEvent& evt)
{
	// evt.timeSinceLastFrame-> en segundos (float/double)
	// evt.timeSinceLastEvent-> en segundos (float/double)
}

Ogre::SceneNode* Obj::getNode()
{
	return mNode;
}

