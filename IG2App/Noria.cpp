#include "Noria.h"

Noria::Noria(Ogre::SceneNode* node, int nAspas): EntidadIG(node)
{
	numeroAspas = nAspas;

	int angle = 360 / numeroAspas;

	cilindro = mNode->createChildSceneNode("cilindro");
	Ogre::Entity* ent = mSM->createEntity("Barrel.mesh");
	ent->setMaterialName("cilindro");
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
	if (evt.keysym.sym == SDLK_r)
	{
		moving = !moving;
	}
	return false;
}

void Noria::frameRendered(const Ogre::FrameEvent& evt)
{
	if (moving) {
		mNode->roll(Ogre::Degree(1));

		cilindro->yaw(Ogre::Degree(-1));
		for (int i = 0; i < numeroAspas; i++)
		{
			aspas[i].getNode()->getChildren()[2]->rotate({ 0,0,1 }, Ogre::Degree(-1));
		}
	}
}
