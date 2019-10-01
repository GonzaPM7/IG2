#include "Muñeco.h"

Muneco::Muneco(Ogre::SceneNode* node): EntidadIG(node)
{
	Ogre::SceneNode* cuelloNode = mNode->createChildSceneNode();

	Ogre::SceneNode* cabeza = cuelloNode->createChildSceneNode("cabeza");
	Ogre::Entity* ent1 = mSM->createEntity("sphere.mesh");
	cabeza->attachObject(ent1);
	cabeza->setScale(0.5, 0.5, 0.5);
	cabeza->setPosition(10, 125, 10);

	Ogre::SceneNode* nariz = cabeza->createChildSceneNode("nariz");
	Ogre::Entity* ent2 = mSM->createEntity("sphere.mesh");
	nariz->attachObject(ent2);
	nariz->setScale(0.15, 0.15, 0.15);
	nariz->setPosition(70, 0, 70);

	Ogre::SceneNode* cuerpo = cuelloNode->createChildSceneNode("cuerpo");
	Ogre::Entity* ent3 = mSM->createEntity("sphere.mesh");
	cuerpo->attachObject(ent3);
	cuerpo->setPosition(10, 0, 10);

	Ogre::SceneNode* ombligo = cuerpo->createChildSceneNode("ombligo");
	Ogre::Entity* ent4 = mSM->createEntity("sphere.mesh");
	ombligo->attachObject(ent4);
	ombligo->setScale(0.15, 0.15, 0.15);
	ombligo->setPosition(70, 0, 70);
}

void Muneco::SetPosition(int x, int y, int z)
{
	mNode->translate(x, y, z);
}

void Muneco::SetRotation(int angle)
{
	mNode->rotate({ 0,1,0 }, Ogre::Degree(angle));
}


