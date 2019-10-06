#include "Aspa.h"

Aspa::Aspa(Ogre::SceneNode* node): EntidadIG(node)
{
	tablonIzquierdo = mNode->createChildSceneNode();
	Ogre::Entity* ent1 = mSM->createEntity("cube.mesh");
	ent1->setMaterialName("aspa");
	tablonIzquierdo->attachObject(ent1);
	tablonIzquierdo->setScale(10, 0.7, 0.25);
	tablonIzquierdo->setPosition(-500, 0, -70);

	tablonDerecho = mNode->createChildSceneNode();
	Ogre::Entity* ent2 = mSM->createEntity("cube.mesh");
	ent2->setMaterialName("aspa");
	tablonDerecho->attachObject(ent2);
	tablonDerecho->setScale(10, 0.7, 0.25);
	tablonDerecho->setPosition(-500, 0, 70);
	
	cangilon = mNode->createChildSceneNode();
	Ogre::Entity* ent3 = mSM->createEntity("cube.mesh");
	ent3->setMaterialName("cangilon");
	cangilon->attachObject(ent3);
	cangilon->setPosition(-1000,0,0);
	cangilon->setScale(1.5, 1.5, 1.5);
}

void Aspa::rotateBox(int angle)
{
	cangilon->roll(Ogre::Degree(-angle));
}
