#include "Muñeco.h"

Muneco::Muneco(Ogre::SceneNode* node): EntidadIG(node)
{
	Ogre::SceneNode* cuelloNode = mNode->createChildSceneNode("cuello");

	Ogre::SceneNode* cabeza = cuelloNode->createChildSceneNode("cabeza");
	Ogre::Entity* ent1 = mSM->createEntity("sphere.mesh");
	ent1->setMaterialName("cuerpo");
	cabeza->attachObject(ent1);
	cabeza->setScale(0.5, 0.5, 0.5);
	cabeza->setPosition(10, 125, 10);

	Ogre::SceneNode* nariz = cabeza->createChildSceneNode("nariz");
	Ogre::Entity* ent2 = mSM->createEntity("sphere.mesh");
	ent2->setMaterialName("nariz");
	nariz->attachObject(ent2);
	nariz->setScale(0.15, 0.15, 0.15);
	nariz->setPosition(70, 0, 70);

	Ogre::SceneNode* cuerpo = cuelloNode->createChildSceneNode("cuerpo");
	Ogre::Entity* ent3 = mSM->createEntity("sphere.mesh");
	ent3->setMaterialName("cuerpo");
	cuerpo->attachObject(ent3);
	cuerpo->setPosition(10, 0, 10);

	Ogre::SceneNode* ombligo = cuerpo->createChildSceneNode("ombligo");
	Ogre::Entity* ent4 = mSM->createEntity("sphere.mesh");
	ent4->setMaterialName("ombligo");
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
	/*mNode->getChild("cuello")->getChild("cuerpo")->rotate({ 0,1,0 }, Ogre::Degree(60));
	mNode->getChild("cuello")->getChild("cabeza")->rotate({ 0,1,0 }, Ogre::Degree(60));*/
}

bool Muneco::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_q)
	{
		moving = !moving;
	}
	return true;
}

void Muneco::frameRendered(const Ogre::FrameEvent& evt)
{
	if (moving)
	{
		if (forward)
		{
			mNode->setPosition(mNode->getPosition().x + speed, mNode->getPosition().y, mNode->getPosition().z);
			mNode->getChild("cuello")->getChild("cuerpo")->rotate(Ogre::Vector3(-1, 0, 1), Ogre::Degree(headspeed));
		}
		else
		{
			mNode->setPosition(mNode->getPosition().x - speed, mNode->getPosition().y, mNode->getPosition().z);
			mNode->getChild("cuello")->getChild("cuerpo")->rotate(Ogre::Vector3(-1, 0, 1), Ogre::Degree(-headspeed));
		}

		if (forward && mNode->getPosition().x >= 600)
			forward = false;
		if (!forward && mNode->getPosition().x <= -600)
			forward = true;

		if (forwardhead)
		{
			mNode->getChild("cuello")->getChild("cabeza")->rotate(Ogre::Vector3(0, 1, 0), Ogre::Degree(headspeed));
			angle += headspeed;
		}
		else
		{
			mNode->getChild("cuello")->getChild("cabeza")->rotate(Ogre::Vector3(0, 1, 0), Ogre::Degree(-headspeed));
			angle -= headspeed;
		}


		if (forwardhead && angle >= 180)
			forwardhead = false;
		if (!forwardhead && angle <= 0)
			forwardhead = true;
	}
}


