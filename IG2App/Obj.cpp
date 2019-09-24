#include "Obj.h"

Obj::Obj(Ogre::SceneNode* node)
{
	Ogre::SceneManager* mSM = mNode->getCreator();
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

