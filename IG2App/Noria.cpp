#include "Noria.h"

Noria::Noria(Ogre::SceneNode* node, int nAspas)
{
	mNode = node;
	mSM = mNode->getCreator();

	numeroAspas = nAspas;

	int angle = 360 / numeroAspas;

	cilindro = mNode->createChildSceneNode("cilindro");
	Ogre::Entity* ent = mSM->createEntity("Barrel.mesh");
	cilindro->setScale(20,40,20);
	cilindro->pitch(Ogre::Degree(90));
	cilindro->attachObject(ent);

	for (int i = 0; i < numeroAspas; i++)
	{
		Aspa aspa = Aspa(node);
		aspa = mNode->createChildSceneNode("aspa_" + std::to_string(i));
		aspa.getNode()->setPosition(0, 0, 0);
		aspa.getNode()->roll(Ogre::Degree(angle * i));
		aspa.rotateBox(angle * i);
		aspas.push_back(aspa);
	}
	
}

bool Noria::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_q)
	{
		mNode->yaw(Ogre::Degree(5));
	}
	return true;
}
