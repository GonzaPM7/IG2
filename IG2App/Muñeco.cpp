#include "Muñeco.h"

Muneco::Muneco(Ogre::SceneNode* node, bool nouse): EntidadIG(node)
{
	Ogre::SceneNode* cuelloNode = mNode->createChildSceneNode("cuello");

	Ogre::SceneNode* cabeza = cuelloNode->createChildSceneNode("cabeza");
	cabezaEnt = mSM->createEntity("sphere.mesh");
	if(nouse)
		cabezaEnt->setMaterialName("cuerpo");
	else
		cabezaEnt->setMaterialName("cabeza");

	cabeza->attachObject(cabezaEnt);
	cabeza->setScale(0.5, 0.5, 0.5);
	cabeza->setPosition(10, 125, 10);

	if (nouse) {
		Ogre::SceneNode* nariz = cabeza->createChildSceneNode("nariz");
		Ogre::Entity* ent2 = mSM->createEntity("sphere.mesh");
		ent2->setMaterialName("nariz");
		nariz->attachObject(ent2);
		nariz->setScale(0.15, 0.15, 0.15);
		nariz->setPosition(70, 0, 70);
	}
	
	Ogre::SceneNode* cuerpo	= cuelloNode->createChildSceneNode("cuerpo");
	cuerpoEnt = mSM->createEntity("sphere.mesh");
	if (nouse)
		cuerpoEnt->setMaterialName("cuerpo");
	else
		cuerpoEnt->setMaterialName("cuerpo2");
	cuerpo->attachObject(cuerpoEnt);
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
	double x = cos(angulo * 3.1416 / 180);
	double z = -sin(angulo * 3.1416 / 180);
	if (evt.keysym.sym == SDLK_q)
	{
		moving = !moving;
	}
	else if (evt.keysym.sym == SDLK_UP)
	{
		moving = false;
		mNode->setPosition(mNode->getPosition() + Ogre::Vector3(x, 0, z) * -speed);
		mNode->getChild("cuello")->getChild("cuerpo")->rotate(Ogre::Vector3(-1, 0, 1), Ogre::Degree(-headspeed));
	}
	else if (evt.keysym.sym == SDLK_DOWN)
	{
		moving = false;
		mNode->setPosition(mNode->getPosition() + Ogre::Vector3(x, 0, z) * speed);
		mNode->getChild("cuello")->getChild("cuerpo")->rotate(Ogre::Vector3(-1, 0, 1), Ogre::Degree(headspeed));
	}
	else if (evt.keysym.sym == SDLK_LEFT)
	{
		moving = false;
		mNode->getChild("cuello")->getChild("cuerpo")->yaw(Ogre::Degree(headspeed), Ogre::SceneNode::TS_WORLD);
		angulo += headspeed;
	}
	else if (evt.keysym.sym == SDLK_RIGHT)
	{
		moving = false;
		mNode->getChild("cuello")->getChild("cuerpo")->yaw(Ogre::Degree(-headspeed), Ogre::SceneNode::TS_WORLD);
		angulo -= headspeed;
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
			mNode->getChild("cuello")->getChild("cuerpo")->roll(Ogre::Degree(3), Ogre::SceneNode::TS_WORLD);//rotate(Ogre::Vector3(-1, 0, 1), Ogre::Degree(headspeed));
		}
		else
		{
			mNode->setPosition(mNode->getPosition().x - speed, mNode->getPosition().y, mNode->getPosition().z);
			mNode->getChild("cuello")->getChild("cuerpo")->roll(Ogre::Degree(-3), Ogre::SceneNode::TS_WORLD);//rotate(Ogre::Vector3(-1, 0, 1), Ogre::Degree(-headspeed));
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

void Muneco::receiveEvent(EntidadIG* entidad)
{
	if (!rojo) {
		cabezaEnt->setMaterialName("cabezaroja");
		cuerpoEnt->setMaterialName("cuerporojo");
		moving = false;
	}
	else {
		cabezaEnt->setMaterialName("cabeza");
		cuerpoEnt->setMaterialName("cuerpo2");
		moving = true;
	}
	rojo = !rojo;
}


