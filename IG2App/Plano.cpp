#include "Plano.h"

Plano::Plano(Ogre::SceneNode* node): EntidadIG(node)
{
	Ogre::MeshManager::getSingleton().createPlane("mPlane1080x800", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Ogre::Plane(Ogre::Vector3::UNIT_Y, 0), 2080, 1800, 100, 80, true, 1, 1.0, 1.0, Ogre::Vector3::UNIT_Z);
	Ogre::SceneNode* PlanoNode = mSM->getRootSceneNode()->createChildSceneNode();
	planoEnt = mSM->createEntity("mPlane1080x800");
	planoEnt->setMaterialName("agua");
	node->attachObject(planoEnt);
}

bool Plano::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_p)
	{
		mNode->yaw(Ogre::Degree(5), Ogre::SceneNode::TS_LOCAL);
	}
	else if (evt.keysym.sym == SDLK_r)
	{
		sendEvent(this);
	}
	return true;
}

void Plano::receiveEvent(EntidadIG* entidad)
{	
	if (moving)
	{
		planoEnt->setMaterialName("agua2");
	}
	else
	{
		planoEnt->setMaterialName("agua");
	}
	moving = !moving;
}
