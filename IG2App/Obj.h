#pragma once

#include <OgreInput.h>
#include <OgreEntity.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>

class Obj: public OgreBites::InputListener
{
	public:
		Obj(Ogre::SceneNode* node);
		~Obj();    // métodos de InputListenerque podemos redefinir
		virtual bool keyPressed(const OgreBites:: KeyboardEvent&   evt);
		virtual void frameRendered(const Ogre::FrameEvent&  evt);
		/*virtual bool keyReleased(const OgreBites:: KeyboardEvent&   evt);
		virtual bool mousePressed(const OgreBites::MouseButtonEvent& evt);
		virtual bool mouseRelease(const OgreBites::MouseButtonEvent& evt);
		virtual bool mouseMoved(const OgreBites::MouseMotionEvent& evt);
		virtual bool mouseWheelRolled(const OgreBites::MouseWheelEvent& evt);*/

	protected:
		Ogre::SceneNode* mNode;
		Ogre::SceneManager* mSM;
};

