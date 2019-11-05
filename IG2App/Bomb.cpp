#include "Bomb.h"
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>
#include <OgreFrameListener.h>

Bomb::Bomb(Ogre::SceneNode* node): EntidadIG(node)
{
	Ogre::SceneNode* bombNode = mNode->createChildSceneNode("bomb");
	Ogre::Entity* ent = mSM->createEntity("uv_sphere.mesh");
	ent->setMaterialName("bomb");
	bombNode->attachObject(ent);
	bombNode->setPosition(0, 0, 0);
	bombNode->setScale(0.25, 0.25, 0.25);

	int duracion = 3;
	int longDesplazamiento = 7;

	Ogre::Animation* animation = mSM->createAnimation("animVV", duracion);
	animation->setRotationInterpolationMode(Ogre::Animation::RIM_SPHERICAL);
	Ogre::NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(mNode);
	
	Ogre::Real durPaso = duracion / 4.0;  // uniformes
	Ogre::Vector3  keyframePos(0.0);
	Ogre::Vector3 src(0, 0, 1); // posición y orientación iniciales
	Ogre::TransformKeyFrame* kf;  // 4 keyFrames: origen(0), abajo, arriba, origen(3)

	kf= track -> createNodeKeyFrame(durPaso * 0);  // Keyframe 0: origen

	kf = track -> createNodeKeyFrame(durPaso * 1);   // Keyframe 1: abajo
	keyframePos+=Ogre::Vector3::NEGATIVE_UNIT_Y * longDesplazamiento;
	kf-> setTranslate(keyframePos); // Abajo
	kf-> setRotation(src.getRotationTo(Ogre::Vector3(1, 0, 1))); // Yaw(45)

	kf = track-> createNodeKeyFrame(durPaso * 3); // Keyframe 2: arriba
	keyframePos+=Ogre::Vector3::UNIT_Y * longDesplazamiento * 2;
	kf-> setTranslate(keyframePos);  // Arriba
	kf-> setRotation(src.getRotationTo(Ogre::Vector3(-1, 0, 1))); // Yaw(-45)

	kf = track-> createNodeKeyFrame(durPaso * 4);  // Keyframe 3: origen

	animationState = mSM->createAnimationState("animVV");
	animationState->setLoop(true);
	animationState->setEnabled(true);
}

bool Bomb::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_b)
	{
		sendEvent(this);
	}
	return true;
}

void Bomb::frameRendered(const Ogre::FrameEvent& evt)
{
	animationState->addTime(evt.timeSinceLastFrame);
}

void Bomb::receiveEvent(EntidadIG* entidad)
{
	animActive = !animActive;
	animationState->setEnabled(animActive);
}
