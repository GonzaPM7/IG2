#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>

#include "Aspa.h"
#include "Noria.h"
#include "Muñeco.h"
#include "Plano.h"

class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener 
{
public:
  explicit IG2App() : IG2ApplicationContext("IG2App") { };  // new -> setup()  
  virtual ~IG2App() { };   // delete -> shutdown()  
 
protected:
  virtual void setup();
  virtual void shutdown();

  virtual void setupScene();
  virtual void setupSceneClock();
  virtual void setupSceneNoria();
  virtual void setupSceneMuneco();

  void turnClock();
  void moveMuneco(bool forward);

  virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
      
  Ogre::SceneManager* mSM = nullptr;
  OgreBites::TrayManager* mTrayMgr = nullptr;    
  Ogre::SceneNode* mLightNode = nullptr;
  Ogre::SceneNode* mCamNode = nullptr;
  Ogre::SceneNode* mSinbadNode = nullptr;

  Ogre::SceneNode* clockNode = nullptr;
  int radio = 400;
  Ogre::SceneNode* hourNode[12];
  Ogre::SceneNode* knotNode = nullptr;

  Ogre::SceneNode* noriaNode = nullptr;

  Ogre::SceneNode* munecoNode = nullptr;


  OgreBites::CameraMan* mCamMgr = nullptr;
 
};

#endif
