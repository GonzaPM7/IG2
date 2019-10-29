#include "Plano.h"

Plano::Plano(Ogre::SceneNode* node,Camera* cam): EntidadIG(node)
{
	Ogre::MeshManager::getSingleton().createPlane("mPlane1080x800", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Ogre::Plane(Ogre::Vector3::UNIT_Y, 0), 2080, 1800, 100, 80, true, 1, 1.0, 1.0, Ogre::Vector3::UNIT_Z);
	Ogre::SceneNode* PlanoNode = mSM->getRootSceneNode()->createChildSceneNode();
	planoEnt = mSM->createEntity("mPlane1080x800");
	
	planoEnt->setMaterialName("reflejo");
	node->attachObject(planoEnt);

	MovablePlane* mpRef = new MovablePlane(Vector3::UNIT_Y, 0);
	node->attachObject(mpRef);

	mSM->getCamera("RefCam")->enableReflection(mpRef);
	mSM->getCamera("RefCam")->enableCustomNearClipPlane(mpRef);

	TexturePtr rttRef = TextureManager::getSingleton().createManual(
		"rttReflejo", // ejemplo -> (*)
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		TEX_TYPE_2D,
		(Real)cam->getViewport()->getActualWidth(), // ejemplo
		(Real)cam->getViewport()->getActualHeight(), // ejemplo
		0, PF_R8G8B8, TU_RENDERTARGET);

	RenderTexture* renderTexture = rttRef->getBuffer()->getRenderTarget();
	Viewport* vpt = renderTexture->addViewport(mSM->getCamera("RefCam")); // ocupando toda
	vpt->setClearEveryFrame(true); // la textura
	vpt->setBackgroundColour(ColourValue::White);	

	TextureUnitState* tu = planoEnt->getSubEntity(0)->getMaterial()->
		getTechnique(0)->getPass(0)->
		createTextureUnitState("rttReflejo");

	tu->setColourOperation(LBO_MODULATE);
	tu->setProjectiveTexturing(true, mSM->getCamera("RefCam"));	
}

bool Plano::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_p)
	{
		mNode->yaw(Ogre::Degree(5), Ogre::SceneNode::TS_LOCAL);
	}
	else if (evt.keysym.sym == SDLK_r)
	{
		sendEvent(this);
	}
	return true;
}

void Plano::receiveEvent(EntidadIG* entidad)
{	
	if (moving)
	{
		planoEnt->setMaterialName("reflejo2");
	}
	else
	{
		planoEnt->setMaterialName("reflejo");
	}
	moving = !moving;
}
