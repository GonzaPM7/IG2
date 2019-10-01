#include "EntidadIG.h"

std::vector<EntidadIG*> EntidadIG::appListeners = std::vector<EntidadIG*>(0, nullptr);

EntidadIG::EntidadIG(Ogre::SceneNode* node)
{
	mNode = node;
	mSM = mNode->getCreator();
}

EntidadIG::~EntidadIG()
{
	for (auto it = appListeners.begin(); it != appListeners.end(); ++it)
	{
		delete (*it);
	}
}

void EntidadIG::addListener(EntidadIG* entidad)
{
	appListeners.push_back(entidad);
}

Ogre::SceneNode* EntidadIG::getNode()
{
	return mNode;
}

bool EntidadIG::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	return false;
}
