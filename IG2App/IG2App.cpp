#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>

using namespace Ogre;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
  if (evt.keysym.sym == SDLK_ESCAPE)
  {
    getRoot()->queueEndRendering();
  }
  /*else if (evt.keysym.sym == SDLK_w)
  {
	  //turnClock();
  }
  else if (evt.keysym.sym == SDLK_q)
  {
	  //moveMuneco(true);
  }
  else if (evt.keysym.sym == SDLK_e)
  {
	  //moveMuneco(false);
  }*/
  
  return true;
}

void IG2App::shutdown()
{
  mShaderGenerator->removeSceneManager(mSM);  
  mSM->removeRenderQueueListener(mOverlaySystem);  
					
  mRoot->destroySceneManager(mSM);  

  delete mTrayMgr;  mTrayMgr = nullptr;
  delete mCamMgr; mCamMgr = nullptr;
  
  // do not forget to call the base 
  IG2ApplicationContext::shutdown();
}

void IG2App::setup(void)
{
  // do not forget to call the base first
  IG2ApplicationContext::setup();

  mSM = mRoot->createSceneManager();  

  // register our scene with the RTSS
  mShaderGenerator->addSceneManager(mSM);

  mSM->addRenderQueueListener(mOverlaySystem);

  mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);  
  mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
  addInputListener(mTrayMgr);

  addInputListener(this);   
  // setupSceneNoria();
  setupScene();

}

void IG2App::setupScene()
{
	Camera* cam = mSM->createCamera("Cam");
	cam->setNearClipDistance(1);
	cam->setFarClipDistance(10000);
	cam->setAutoAspectRatio(true);
	//cam->setPolygonMode(Ogre::PM_WIREFRAME); 

	mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
	mCamNode->attachObject(cam);

	mCamNode->setPosition(0, 0, 1000);
	mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
	//mCamNode->setDirection(Ogre::Vector3(0, 0, -1));  

	// and tell it to render into the main window
	Viewport* vp = getRenderWindow()->addViewport(cam);
	//vp->setBackgroundColour(Ogre::ColourValue(1, 1, 1));

	//------------------------------------------------------------------------

	// without light we would just get a black screen 

	Light* luz = mSM->createLight("Luz");
	luz->setType(Ogre::Light::LT_DIRECTIONAL);
	luz->setDiffuseColour(1, 1, 1);

	mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
	//mLightNode = mCamNode->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);

	mLightNode->setDirection(Ogre::Vector3(1, -1, -1));  //vec3.normalise();
	//lightNode->setPosition(0, 0, 1000);

	//------------------------------------------------------------------------

	// finally something to render

	//Original 
	/*Ogre::Entity* ent = mSM->createEntity("cube.mesh");
	mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
	mSinbadNode->setPosition(0, 200, 0);
	mSinbadNode->attachObject(ent);*/

	//Aspa aspa = Aspa(mSM->getRootSceneNode());
	/*MeshManager::getSingleton().createPlane("mPlane1080x800",ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(Vector3::UNIT_Y, 0), 2080, 1800, 100, 80, true, 1, 1.0, 1.0, Vector3::UNIT_Z);
	SceneNode* PlanoNode = mSM->getRootSceneNode()->createChildSceneNode();
	Entity* e = mSM->createEntity("mPlane1080x800");
	PlanoNode->attachObject(e);*/

	Plano* plano = new Plano(mSM->getRootSceneNode());
	addInputListener(plano);

	Noria* noria = new Noria(plano->getNode()->createChildSceneNode(), 12);
	//mSM->getRootSceneNode() con esto no gira
	addInputListener(noria);

	Muneco* muneco = new Muneco(plano->getNode()->createChildSceneNode());
	muneco->SetPosition(400, 100, 600);
	muneco->SetRotation(-190);

	mCamMgr = new OgreBites::CameraMan(mCamNode);
	addInputListener(mCamMgr);
	mCamMgr->setStyle(OgreBites::CS_ORBIT);

	//mCamMgr->setTarget(mSinbadNode);  
	//mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);

	//------------------------------------------------------------------------

}

void IG2App::setupSceneClock(void)
{
  // create the camera
  Camera* cam = mSM->createCamera("Cam");
  cam->setNearClipDistance(1); 
  cam->setFarClipDistance(10000);
  cam->setAutoAspectRatio(true);
  //cam->setPolygonMode(Ogre::PM_WIREFRAME); 

  mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
  mCamNode->attachObject(cam);

  mCamNode->setPosition(0, 0, 1000);
  mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
  //mCamNode->setDirection(Ogre::Vector3(0, 0, -1));  
  
  // and tell it to render into the main window
  Viewport* vp = getRenderWindow()->addViewport(cam);
  //vp->setBackgroundColour(Ogre::ColourValue(1, 1, 1));

  //------------------------------------------------------------------------

  // without light we would just get a black screen 

  Light* luz = mSM->createLight("Luz");
  luz->setType(Ogre::Light::LT_DIRECTIONAL);
  luz->setDiffuseColour(1, 0, 0);

  mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
  //mLightNode = mCamNode->createChildSceneNode("nLuz");
  mLightNode->attachObject(luz);

  mLightNode->setDirection(Ogre::Vector3(1, -1, -1));  //vec3.normalise();
  //lightNode->setPosition(0, 0, 1000);
 
  //------------------------------------------------------------------------

  // finally something to render

  //Original 
  /*Ogre::Entity* ent = mSM->createEntity("cube.mesh");
  mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");  
  mSinbadNode->setPosition(0, 200, 0);  
  mSinbadNode->attachObject(ent);*/

  //Cubos en circulo
  clockNode = mSM->getRootSceneNode()->createChildSceneNode();
  for (int i = 0; i < 12; i++) {
	  hourNode[i] = nullptr;
	  Ogre::Entity* ent = mSM->createEntity("cube.mesh");
	  hourNode[i] = clockNode->createChildSceneNode("cubo" +std::to_string(i + 1));
	  hourNode[i]->setPosition(radio*Ogre::Math::Cos(2*Ogre::Math::PI*i/12), radio * Ogre::Math::Sin(2 * Ogre::Math::PI*i / 12), 0);
	  if (i % 2 != 0)
		  clockNode->getChild("cubo" + std::to_string(i + 1))->setScale(0.4, 0.4, 0.4);
	  hourNode[i]->attachObject(ent);
  }

  Ogre::Entity* ent = mSM->createEntity("knot.mesh");
  knotNode = mSM->getRootSceneNode()->createChildSceneNode();
  knotNode->setPosition(0,0, 0);
  knotNode->attachObject(ent);


  //mSinbadNode->setScale(20, 20, 20);
  //mSinbadNode->yaw(Ogre::Degree(-45));
  //mSinbadNode->showBoundingBox(true);
  //mSinbadNode->setVisible(false);

  //------------------------------------------------------------------------

  mCamMgr = new OgreBites::CameraMan(mCamNode);
  addInputListener(mCamMgr);
  mCamMgr->setStyle(OgreBites::CS_ORBIT);  
  
  //mCamMgr->setTarget(mSinbadNode);  
  //mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);

  //------------------------------------------------------------------------

}

void IG2App::turnClock()
{
	//ESCENA DEL RELOJ
	/*clockNode->roll(Ogre::Degree(10));

	for (int i = 0; i < 12; i++) {
		clockNode->getChild("cubo" + std::to_string(i + 1))->roll(Ogre::Degree(-10));
		//clockNode->getChild("cubo" + std::to_string(i + 1))->setPosition(radio * Ogre::Math::Cos(2 * Ogre::Math::PI * i / 12), radio * Ogre::Math::Sin(2 * Ogre::Math::PI * i / 12), 0);
	}*/

	//ESCENA DE LA NORIA
	/*noriaNode->roll(Ogre::Degree(5));

	for (int i = 0; i < 12; i++) {
		noriaNode->getChild("aspa" + std::to_string(i + 1))->getChild("cangilon" + std::to_string(i + 1))->roll(Ogre::Degree(-5));
		//clockNode->getChild("cubo" + std::to_string(i + 1))->setPosition(radio * Ogre::Math::Cos(2 * Ogre::Math::PI * i / 12), radio * Ogre::Math::Sin(2 * Ogre::Math::PI * i / 12), 0);
	}*/

	//ESCENA DEL MUNECO
	munecoNode->getChild("cabeza")->yaw(Ogre::Degree(-5));
}

void IG2App::moveMuneco(bool forward)
{
	int speed = 5;
	if(forward)
	{
		munecoNode->setPosition(munecoNode->getPosition().x + speed, munecoNode->getPosition().y, munecoNode->getPosition().z + speed);
		munecoNode->getChild("cuerpo")->rotate(Vector3(1, 0, -1), Ogre::Degree(speed));
	}
	else
	{
		munecoNode->setPosition(munecoNode->getPosition().x - speed, munecoNode->getPosition().y, munecoNode->getPosition().z - speed);
		munecoNode->getChild("cuerpo")->rotate(Vector3(1, 0, -1), Ogre::Degree(-speed));
	}
}

void IG2App::setupSceneNoria(void)
{
	// create the camera
	Camera* cam = mSM->createCamera("Cam");
	cam->setNearClipDistance(1);
	cam->setFarClipDistance(10000);
	cam->setAutoAspectRatio(true);
	//cam->setPolygonMode(Ogre::PM_WIREFRAME); 

	mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
	mCamNode->attachObject(cam);

	mCamNode->setPosition(0, 0, 1000);
	mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
	//mCamNode->setDirection(Ogre::Vector3(0, 0, -1));  

	// and tell it to render into the main window
	Viewport* vp = getRenderWindow()->addViewport(cam);
	//vp->setBackgroundColour(Ogre::ColourValue(1, 1, 1));

	//------------------------------------------------------------------------

	// without light we would just get a black screen 

	Light* luz = mSM->createLight("Luz");
	luz->setType(Ogre::Light::LT_DIRECTIONAL);
	luz->setDiffuseColour(1, 0, 0);

	mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
	//mLightNode = mCamNode->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);

	mLightNode->setDirection(Ogre::Vector3(1, -1, -1));  //vec3.normalise();
	//lightNode->setPosition(0, 0, 1000);

	noriaNode = mSM->getRootSceneNode()->createChildSceneNode();
	Ogre::SceneNode* aspaNode[12];

	for (int i = 0; i < 12; i++)
	{
		aspaNode[i] = noriaNode->createChildSceneNode("aspa" + std::to_string(i + 1));

		Ogre::SceneNode* tablonIzquierdo = aspaNode[i]->createChildSceneNode("tablonIzquierdo" + std::to_string(i + 1));
		Ogre::Entity* ent1 = mSM->createEntity("cube.mesh");
		tablonIzquierdo->attachObject(ent1);
		tablonIzquierdo->setScale(5, 0.5, 0.25);
		tablonIzquierdo->setPosition((radio * Ogre::Math::Cos(2 * Ogre::Math::PI * i / 12)) / 2, (radio * Ogre::Math::Sin(2 * Ogre::Math::PI * i / 12)) / 2, -40);
		tablonIzquierdo->roll(Ogre::Degree(30*i));

		Ogre::SceneNode* tablonDerecho = aspaNode[i]->createChildSceneNode("tablonDerecho" + std::to_string(i + 1));
		Ogre::Entity* ent2 = mSM->createEntity("cube.mesh");
		tablonDerecho->attachObject(ent2);
		tablonDerecho->setScale(5, 0.5, 0.25);
		tablonDerecho->setPosition((radio * Ogre::Math::Cos(2 * Ogre::Math::PI * i / 12))/2, (radio * Ogre::Math::Sin(2 * Ogre::Math::PI * i / 12)) / 2, 40);
		tablonDerecho->roll(Ogre::Degree(30 * i));

		Ogre::SceneNode* cangilon = aspaNode[i]->createChildSceneNode("cangilon" + std::to_string(i + 1));
		Ogre::Entity* ent3 = mSM->createEntity("cube.mesh");
		cangilon->attachObject(ent3);
		cangilon->setPosition(radio * Ogre::Math::Cos(2 * Ogre::Math::PI * i / 12), radio * Ogre::Math::Sin(2 * Ogre::Math::PI * i / 12), 0);
		cangilon->setScale(1.5, 1.5, 1);
	}

	mCamMgr = new OgreBites::CameraMan(mCamNode);
	addInputListener(mCamMgr);
	mCamMgr->setStyle(OgreBites::CS_ORBIT);
}

void IG2App::setupSceneMuneco(void)
{
	// create the camera
	Camera* cam = mSM->createCamera("Cam");
	cam->setNearClipDistance(1);
	cam->setFarClipDistance(10000);
	cam->setAutoAspectRatio(true);
	//cam->setPolygonMode(Ogre::PM_WIREFRAME); 

	mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
	mCamNode->attachObject(cam);

	mCamNode->setPosition(0, 0, 1000);
	mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
	//mCamNode->setDirection(Ogre::Vector3(0, 0, -1));  

	// and tell it to render into the main window
	Viewport* vp = getRenderWindow()->addViewport(cam);
	//vp->setBackgroundColour(Ogre::ColourValue(1, 1, 1));

	//------------------------------------------------------------------------

	// without light we would just get a black screen 

	Light* luz = mSM->createLight("Luz");
	luz->setType(Ogre::Light::LT_DIRECTIONAL);
	luz->setDiffuseColour(1, 0, 0);

	mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
	//mLightNode = mCamNode->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);

	mLightNode->setDirection(Ogre::Vector3(1, -1, -1));  //vec3.normalise();
	//lightNode->setPosition(0, 0, 1000);

	munecoNode = mSM->getRootSceneNode()->createChildSceneNode();

	Ogre::SceneNode* cabeza = munecoNode->createChildSceneNode("cabeza");
	Ogre::Entity* ent1 = mSM->createEntity("sphere.mesh");
	cabeza->attachObject(ent1);
	cabeza->setScale(0.5, 0.5, 0.5);
	cabeza->setPosition(10, 125, 10);

	Ogre::SceneNode* nariz = cabeza->createChildSceneNode("nariz");
	Ogre::Entity* ent2 = mSM->createEntity("sphere.mesh");
	nariz->attachObject(ent2);
	nariz->setScale(0.15, 0.15, 0.15);
	nariz->setPosition(70, 0, 70);

	Ogre::SceneNode* cuerpo = munecoNode->createChildSceneNode("cuerpo");
	Ogre::Entity* ent3 = mSM->createEntity("sphere.mesh");
	cuerpo->attachObject(ent3);
	cuerpo->setPosition(10, 0, 10);

	Ogre::SceneNode* ombligo = cuerpo->createChildSceneNode("ombligo");
	Ogre::Entity* ent4 = mSM->createEntity("sphere.mesh");
	ombligo->attachObject(ent4);
	ombligo->setScale(0.15, 0.15, 0.15);
	ombligo->setPosition(70, 0, 70);


	mCamMgr = new OgreBites::CameraMan(mCamNode);
	addInputListener(mCamMgr);
	mCamMgr->setStyle(OgreBites::CS_ORBIT);
}

