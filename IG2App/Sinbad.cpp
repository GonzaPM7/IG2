#include "Sinbad.h"
#include <OgreFrameListener.h>
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>

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

	int duracion = 10;
	int longDesplazamientoX = 1650;
	int longDesplazamientoZ = 1600;

	Ogre::Animation* animation = mSM->createAnimation("animSS", duracion);
	Ogre::NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(mNode);

	Ogre::Real durPasoX = duracion * 0.25;  // uniformes
	Ogre::Real durPasoZ = duracion * 0.15;  // uniformes
	Ogre::Real durGiro= duracion * 0.05;  // uniformes
	Ogre::Vector3  keyframePos(0.0);
	Ogre::Vector3 src(0, 0, 1); // posición y orientación iniciales
	Ogre::TransformKeyFrame* kf;  // 4 keyFrames: origen(0), abajo, arriba, origen(3)

	kf = track->createNodeKeyFrame(durPasoX * 0);  // Keyframe 0: esquina arriba derecha

	kf = track->createNodeKeyFrame(durPasoZ * 1);   // Keyframe 1: esquina abajo derecha
	keyframePos += Ogre::Vector3::UNIT_Z * longDesplazamientoZ;
	kf->setTranslate(keyframePos); // Abajo

	kf = track->createNodeKeyFrame(durGiro * 2); // giro
	kf->setRotation(src.getRotationTo(Ogre::Vector3(-1, 0, 0))); // Yaw(45)

	kf = track->createNodeKeyFrame(durPasoX * 3); // Keyframe 2: esquina abajo izquierda
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_X * longDesplazamientoX;
	kf->setTranslate(keyframePos);  // Arriba

	kf = track->createNodeKeyFrame(durGiro * 4); // giro
	kf->setRotation(src.getRotationTo(Ogre::Vector3(0, 0, -1))); // Yaw(45)

	kf = track->createNodeKeyFrame(durPasoZ * 5); // Keyframe 3: esquina arriba izquierda
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_Z * longDesplazamientoZ;
	kf->setTranslate(keyframePos);  // Arriba

	kf = track->createNodeKeyFrame(durGiro * 6); // giro
	kf->setRotation(src.getRotationTo(Ogre::Vector3(1, 0, 0))); // Yaw(45)

	kf = track->createNodeKeyFrame(durPasoX * 7);  // Keyframe 4: origen
	keyframePos += Ogre::Vector3::UNIT_X * longDesplazamientoX;
	kf->setTranslate(keyframePos);  // Arriba

	kf = track->createNodeKeyFrame(durGiro * 8); // giro
	kf->setRotation(src.getRotationTo(Ogre::Vector3(0, 0, 1))); // Yaw(45)

	movingState = mSM->createAnimationState("animSS");
	movingState->setLoop(true);
	movingState->setEnabled(true);
	
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
		}
		else
		{
			danceState->setEnabled(false);
			runbaseState->setEnabled(true);
			runtopState->setEnabled(true);	
			ent->detachObjectFromBone(sword1);
			ent->attachObjectToBone("Handle.R", sword1);
		}
		running = !running;
	}
	return true;
}

void Sinbad::frameRendered(const Ogre::FrameEvent& evt)
{
	danceState->addTime(evt.timeSinceLastFrame);
	runbaseState->addTime(evt.timeSinceLastFrame);
	runtopState->addTime(evt.timeSinceLastFrame);
	movingState->addTime(evt.timeSinceLastFrame);
}
