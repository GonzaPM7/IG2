#include "Sinbad.h"
#include <OgreFrameListener.h>
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>
#include <iostream>

Sinbad::Sinbad(Ogre::SceneNode* node): EntidadIG(node)
{
	ent = mSM->createEntity("Sinbad.mesh");
	mNode->attachObject(ent);

	mNode->setScale(50, 50, 50);
	mNode->setPosition(800, 250, -800);
	mNode->setInitialState();

	sword1 = mSM->createEntity("Sword.mesh");
	ent->attachObjectToBone("Sheath.R", sword1);
	
	sword2 = mSM->createEntity("Sword.mesh");
	ent->attachObjectToBone("Sheath.L", sword2);

	danceState = ent->getAnimationState("Dance");
	danceState->setEnabled(true);
	danceState->setLoop(true);

	runbaseState = ent->getAnimationState("RunBase");
	runtopState = ent->getAnimationState("RunTop");
	runbaseState->setLoop(true);
	runtopState->setLoop(true);

	int duracion = 15;
	int longDesplazamientoX = 1650;
	int longDesplazamientoZ = 1600;

	Ogre::Animation* animation = mSM->createAnimation("animSS", duracion);
	Ogre::NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(mNode);

	Ogre::Real durPaso = duracion / 5.0;
	Ogre::Vector3  keyframePos(0.0);
	Ogre::Vector3 src(0, 0, 1); // posici�n y orientaci�n iniciales
	Ogre::TransformKeyFrame* kf;  // 4 keyFrames: origen(0), abajo, arriba, origen(3)
	
	kf = track->createNodeKeyFrame(durPaso * 0);
	kf->setTranslate(keyframePos);// Keyframe 0: esquina arriba derecha

	kf = track->createNodeKeyFrame(durPaso * 1);   // Keyframe 1: esquina abajo derecha
	keyframePos += Ogre::Vector3::UNIT_Z * longDesplazamientoZ;
	kf->setTranslate(keyframePos); // Abajo

	kf = track->createNodeKeyFrame(durPaso * 1.25); // giro
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_X * 100;
	keyframePos += Ogre::Vector3::UNIT_Z * 100;
	kf->setTranslate(keyframePos);
	kf->setRotation(src.getRotationTo(Ogre::Vector3(-1, 0, 0))); // Yaw(45)

	kf = track->createNodeKeyFrame(durPaso * 2.25); // Keyframe 2: esquina abajo izquierda
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_X * longDesplazamientoX;
	kf->setTranslate(keyframePos);  // Arriba
	kf->setRotation(src.getRotationTo(Ogre::Vector3(-1, 0, 0)));

	kf = track->createNodeKeyFrame(durPaso * 2.5); // giro
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_X * 100;
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_Z * 100;
	kf->setTranslate(keyframePos);
	kf->setRotation(src.getRotationTo(Ogre::Vector3(0, 0, -1))); // Yaw(45)

	kf = track->createNodeKeyFrame(durPaso * 3.5); // Keyframe 3: esquina arriba izquierda
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_Z * longDesplazamientoZ;
	kf->setTranslate(keyframePos);  // Arriba
	kf->setRotation(src.getRotationTo(Ogre::Vector3(0, 0, -1)));

	kf = track->createNodeKeyFrame(durPaso * 3.75); // giro
	keyframePos += Ogre::Vector3::UNIT_X * 100;
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_Z * 100;
	kf->setTranslate(keyframePos);
	kf->setRotation(src.getRotationTo(Ogre::Vector3(1, 0, 0))); // Yaw(45)

	kf = track->createNodeKeyFrame(durPaso * 4.75);  // Keyframe 4: origen
	keyframePos += Ogre::Vector3::UNIT_X * longDesplazamientoX;
	kf->setTranslate(keyframePos);  // Arriba
	kf->setRotation(src.getRotationTo(Ogre::Vector3(1, 0, 0)));

	kf = track->createNodeKeyFrame(durPaso * 5); // giro
	keyframePos += Ogre::Vector3::UNIT_X * 100;
	keyframePos += Ogre::Vector3::UNIT_Z * 100;
	kf->setTranslate(keyframePos);

	movingState = mSM->createAnimationState("animSS");
	movingState->setLoop(true);
}

bool Sinbad::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_c)
	{
		if (running)
		{
			danceState->setEnabled(true);
			runbaseState->setEnabled(false);
			runtopState->setEnabled(false);
			ent->detachObjectFromBone(sword1);
			ent->attachObjectToBone("Sheath.R", sword1);
			movingState->setEnabled(false);
		}
		else
		{
			danceState->setEnabled(false);
			runbaseState->setEnabled(true);
			runtopState->setEnabled(true);	
			ent->detachObjectFromBone(sword1);
			ent->attachObjectToBone("Handle.R", sword1);
			movingState->setEnabled(true);
		}
		running = !running;
	}
	return true;
}

void Sinbad::frameRendered(const Ogre::FrameEvent& evt)
{	
	if (!dead) {
		if (running) {
			movingState->addTime(evt.timeSinceLastFrame);
			runbaseState->addTime(evt.timeSinceLastFrame);
			runtopState->addTime(evt.timeSinceLastFrame);
		}
		else
			danceState->addTime(evt.timeSinceLastFrame);
	}
	if (dead) {
		bombState->addTime(evt.timeSinceLastFrame);
		if (bombState->getTimePosition() < 2.60) {
			runbaseState->addTime(evt.timeSinceLastFrame);
			runtopState->addTime(evt.timeSinceLastFrame);
		}
		else {
			runbaseState->setEnabled(false);
			runtopState->setEnabled(false);
		}
	}
}

void Sinbad::receiveEvent(EntidadIG* entidad)
{
	danceState->setEnabled(false);
	runbaseState->setEnabled(true);
	runtopState->setEnabled(true);
	movingState->setEnabled(false);

	dead = true;

	int duracion = 6;
	//mNode->setPosition(0, 0, 0);
	mNode->setInitialState();

	Ogre::Animation* animation = mSM->createAnimation("animBomb", duracion);
	Ogre::NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(mNode);

	Ogre::Real durPaso = duracion / 3;
	Ogre::Vector3 keyFramePos = mNode->getPosition();
	Ogre::Vector3 src(mNode->_getDerivedOrientation() * Ogre::Vector3::UNIT_Z); // posici�n y orientaci�n iniciales
	Ogre::Vector3 direccion = Ogre::Vector3(0., 250., 0.) - keyFramePos;

	Ogre::TransformKeyFrame* kf;  // 4 keyFrames: origen(0), abajo, arriba, origen(3)

	kf = track->createNodeKeyFrame(durPaso * 0);
	//kf->setTranslate(keyFramePos - Ogre::Vector3(800, 250, -800));
	kf->setRotation(src.getRotationTo(direccion));

	kf= track->createNodeKeyFrame(durPaso * 1);
	keyFramePos = Ogre::Vector3(0., 250., 0.) - keyFramePos;
	kf->setTranslate(keyFramePos);
	kf->setRotation(src.getRotationTo(direccion));

	kf = track->createNodeKeyFrame(durPaso * 1.15);
	keyFramePos += Ogre::Vector3(0., 300., 0.);
	kf->setTranslate(keyFramePos);
	kf->setRotation(src.getRotationTo(direccion));

	kf = track->createNodeKeyFrame(durPaso * 1.30);	
	keyFramePos -= Ogre::Vector3(0., 550., 0.);
	kf->setTranslate(keyFramePos);
	kf->setRotation(src.getRotationTo(direccion));
	kf->setRotation(src.getRotationTo(Ogre::Vector3(0., 1000., 0.)));

	kf = track->createNodeKeyFrame(durPaso * 3);	
	keyFramePos += Ogre::Vector3(1000., 0., 0.);
	kf->setTranslate(keyFramePos);
	kf->setRotation(src.getRotationTo(direccion));
	kf->setRotation(src.getRotationTo(Ogre::Vector3(0., 1000., 0.)));
	
	bombState = mSM->createAnimationState("animBomb");
	bombState->setLoop(false);
	bombState->setEnabled(true);
}

