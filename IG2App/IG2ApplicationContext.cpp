/*
-----------------------------------------------------------------------------

Adaptado de OgreApplicationContext.cpp  en OGREbites\src

-----------------------------------------------------------------------------
*/

#include "IG2ApplicationContext.h"

#include <OgreRoot.h>
#include <OgreGpuProgramManager.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreViewport.h>
#include <OgreDataStream.h>
#include <OgreBitesConfigDialog.h>
#include <OgreWindowEventUtilities.h>

//#include <OgreConfigPaths.h>    // IG2: lo quito xq las rutas son absolutas y deben ser relativas al directorio de la solución
//#include <OgreOverlaySystem.h>  // IG2: lo he incluido en el .h para evitar declaraciones adelantadas
//#include <SDL.h>				  // IG2: lo he incluido en el .h para evitar declaraciones adelantadas
#include <SDL_video.h>
#include <SDL_syswm.h>
#include <SDLInputMapping.h>


namespace OgreBites {

	IG2ApplicationContext::IG2ApplicationContext(const Ogre::String& appName)
	{
		mAppName = appName;
		mFSLayer = new Ogre::FileSystemLayer(mAppName);
		mRoot = nullptr;
		mOverlaySystem = nullptr;
		mFirstRun = true;

		mShaderGenerator = nullptr;
		mMaterialMgrListener = nullptr;
	}

	IG2ApplicationContext::~IG2ApplicationContext()
	{
		delete mFSLayer;
	}

	void IG2ApplicationContext::initApp()
	{
		createRoot();

		if (oneTimeConfig())
			setup();
	}

	void IG2ApplicationContext::closeApp()
	{
		if (mRoot != nullptr)
		{
			mRoot->saveConfig();
		}
		shutdown();
		delete mRoot;
		mRoot = nullptr;
	}

	void IG2ApplicationContext::createRoot()
	{
	    Ogre::String pluginsPath;
		pluginsPath = mFSLayer->getConfigFilePath("plugins.cfg");

		if (!Ogre::FileSystemLayer::fileExists(pluginsPath))    
		{	// IG2: OGRE_CONFIG_DIR tiene un valor absoluto no portable
			//pluginsPath = Ogre::FileSystemLayer::resolveBundlePath(OGRE_CONFIG_DIR "/plugins" OGRE_BUILD_SUFFIX ".cfg");
			OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, "plugins.cfg",	"IG2ApplicationContext::createRoot");
		}

		mSolutionPath = pluginsPath;    // IG2: añadido para definir directorios relativos al de la solución 
		mSolutionPath.erase(mSolutionPath.find_last_of("\\") + 1, mSolutionPath.size() - 1);
		mFSLayer->setHomePath(mSolutionPath);   // IG2: para los archivos de configuración ogre. (en el bin de la solubión)
		mSolutionPath.erase(mSolutionPath.find_last_of("\\") + 1, mSolutionPath.size() - 1);   // IG2: Quito /bin

		mRoot = new Ogre::Root(pluginsPath, mFSLayer->getWritablePath("ogre.cfg"), mFSLayer->getWritablePath("ogre.log"));


		// mRoot->showConfigDialog(OgreBites::getNativeConfigDialog());//Para que se muestre la caja de dialogos

		mOverlaySystem = new Ogre::OverlaySystem();
	}

	void IG2ApplicationContext::shutdown()
	{
		// Destroy the RT Shader System.
		destroyRTShaderSystem();

		if (mWindow.render != nullptr) 
		{
			mRoot->destroyRenderTarget(mWindow.render);
			mWindow.render = nullptr;
		}

		delete mOverlaySystem;
		mOverlaySystem = nullptr;

		if (mWindow.native != nullptr) 
		{
			SDL_DestroyWindow(mWindow.native);
			SDL_QuitSubSystem(SDL_INIT_VIDEO);
			mWindow.native = nullptr;
		}
	}

	void IG2ApplicationContext::setup()
	{
		mRoot->initialise(false);
		createWindow(mAppName);
		setWindowGrab(false);   // IG2: ratón libre

		locateResources();
		initialiseRTShaderSystem();
		loadResources();

		// adds context as listener to process context-level (above the sample level) events
		mRoot->addFrameListener(this);
	}

	bool IG2ApplicationContext::oneTimeConfig()
	{
		if (!mRoot->restoreConfig()) 
		{
			return mRoot->showConfigDialog(OgreBites::getNativeConfigDialog());
		}
		else return true;
	}
	bool IG2ApplicationContext::initialiseRTShaderSystem()
	{
		if (Ogre::RTShader::ShaderGenerator::initialize())
		{
			mShaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
			// Core shader libs not found -> shader generating will fail.
			if (mRTShaderLibPath.empty()) 
				return false;
			// Create and register the material manager listener if it doesn't exist yet.
			if (!mMaterialMgrListener) {
				mMaterialMgrListener = new SGTechniqueResolverListener(mShaderGenerator);
				Ogre::MaterialManager::getSingleton().addListener(mMaterialMgrListener);
			}
		}

		return true;
	}

	void IG2ApplicationContext::destroyRTShaderSystem()
	{
		// Restore default scheme.
		Ogre::MaterialManager::getSingleton().setActiveScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);

		// Unregister the material manager listener.
		if (mMaterialMgrListener != nullptr)
		{
			Ogre::MaterialManager::getSingleton().removeListener(mMaterialMgrListener);
			delete mMaterialMgrListener;
			mMaterialMgrListener = nullptr;
		}

		// Destroy RTShader system.
		if (mShaderGenerator != nullptr)
		{
			Ogre::RTShader::ShaderGenerator::destroy();
			mShaderGenerator = nullptr;
		}
	}

	NativeWindowPair IG2ApplicationContext::createWindow(const Ogre::String& name)
	{
		uint32_t w, h; 
		Ogre::NameValuePairList miscParams;
		
		Ogre::ConfigOptionMap ropts = mRoot->getRenderSystem()->getConfigOptions();

		std::istringstream mode(ropts["Video Mode"].currentValue);
		Ogre::String token;
		mode >> w; // width
		mode >> token; // 'x' as seperator between width and height
		mode >> h; // height
				
		miscParams["FSAA"] = ropts["FSAA"].currentValue;
		miscParams["vsync"] = ropts["VSync"].currentValue;
		miscParams["gamma"] = ropts["sRGB Gamma Conversion"].currentValue;  

		if (!SDL_WasInit(SDL_INIT_VIDEO)) SDL_InitSubSystem(SDL_INIT_VIDEO);

		Uint32 flags = SDL_WINDOW_RESIZABLE;

		if (ropts["Full Screen"].currentValue == "Yes")  flags = SDL_WINDOW_FULLSCREEN;
		//else  flags = SDL_WINDOW_RESIZABLE;
		
		mWindow.native = SDL_CreateWindow(name.c_str(),	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flags);

		SDL_SysWMinfo wmInfo;
		SDL_VERSION(&wmInfo.version);
		SDL_GetWindowWMInfo(mWindow.native, &wmInfo);

		miscParams["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));

		mWindow.render = mRoot->createRenderWindow(name, w, h, false, &miscParams);
		return mWindow;
	}

	void IG2ApplicationContext::setWindowGrab(bool _grab)
	{
		SDL_bool grab = SDL_bool(_grab);
		SDL_SetWindowGrab(mWindow.native, grab);
		//SDL_SetRelativeMouseMode(grab);
		SDL_ShowCursor(grab);
	}

	bool IG2ApplicationContext::frameRenderingQueued(const Ogre::FrameEvent& evt)
	{
		for (std::set<InputListener*>::iterator it = mInputListeners.begin(); it != mInputListeners.end(); ++it)
		{
			(*it)->frameRendered(evt);
		}

		return true;
	}
	
	void IG2ApplicationContext::pollEvents()   // from frameStarted
	{
		if (mWindow.native == nullptr) 
			return;  // SDL events not initialized

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				mRoot->queueEndRendering();
				break;
			case SDL_WINDOWEVENT:
				if (event.window.windowID == SDL_GetWindowID(mWindow.native)) {
					if (event.window.event == SDL_WINDOWEVENT_RESIZED)
					{
						Ogre::RenderWindow* win = mWindow.render;
						//win->resize(event.window.data1, event.window.data2);  // IG2: ERROR 
						win->windowMovedOrResized();
						windowResized(win);
					}
				}
				break;
			default:
				_fireInputEvent(convert(event));
				break;
			}
		}

		// just avoid "window not responding"
		WindowEventUtilities::messagePump();  
	}

	void IG2ApplicationContext::_fireInputEvent(const Event& event) const
	{
		for (std::set<InputListener*>::iterator it = mInputListeners.begin(); it != mInputListeners.end(); ++it)
		{
			InputListener& l = **it;

			switch (event.type)
			{
			case KEYDOWN:
				l.keyPressed(event.key);
				break;
			case KEYUP:
				l.keyReleased(event.key);
				break;
			case MOUSEBUTTONDOWN:
				l.mousePressed(event.button);
				break;
			case MOUSEBUTTONUP:
				l.mouseReleased(event.button);
				break;
			case MOUSEWHEEL:
				l.mouseWheelRolled(event.wheel);
				break;
			case MOUSEMOTION:
				l.mouseMoved(event.motion);
				break;
			case FINGERDOWN:
				// for finger down we have to move the pointer first
				l.touchMoved(event.tfinger);
				l.touchPressed(event.tfinger);
				break;
			case FINGERUP:
				l.touchReleased(event.tfinger);
				break;
			case FINGERMOTION:
				l.touchMoved(event.tfinger);
				break;
			}
			
		}
	}

	void IG2ApplicationContext::loadResources()
	{
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}

	void IG2ApplicationContext::locateResources()
	{
		// load resource paths from config file
		Ogre::ConfigFile cf;

		Ogre::String resourcesPath = mFSLayer->getConfigFilePath("resources.cfg");
		if (Ogre::FileSystemLayer::fileExists(resourcesPath))
		{
			cf.load(resourcesPath);
		}
		else
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
							Ogre::FileSystemLayer::resolveBundlePath(mSolutionPath + "\\media"), 
							"FileSystem", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		}

		Ogre::String sec, type, arch;
		// go through all specified resource groups
		Ogre::ConfigFile::SettingsBySection_::const_iterator seci;
		for (seci = cf.getSettingsBySection().begin(); seci != cf.getSettingsBySection().end(); ++seci) {
			sec = seci->first;
			const Ogre::ConfigFile::SettingsMultiMap& settings = seci->second;
			Ogre::ConfigFile::SettingsMultiMap::const_iterator i;

			// go through all resource paths
			for (i = settings.begin(); i != settings.end(); i++)
			{
				type = i->first;
				arch = Ogre::FileSystemLayer::resolveBundlePath(i->second);
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
			}
		}

		sec = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
		const Ogre::ResourceGroupManager::LocationList genLocs = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(sec);

		OgreAssert(!genLocs.empty(), ("Resource Group '" + sec + "' must contain at least one entry").c_str());

		arch = genLocs.front().archive->getName();
		type = genLocs.front().archive->getType();

		// Add locations for supported shader languages
		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSLES", type, sec);
		}
		else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL120", type, sec);

			if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl150"))
			{
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL150", type, sec);
			}
			else
			{
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL", type, sec);
			}

			if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl400"))
			{
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL400", type, sec);
			}
		}
		else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/HLSL", type, sec);
		}

		mRTShaderLibPath = arch + "/RTShaderLib";
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/materials", type, sec);

		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/GLSL", type, sec);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/GLSLES", type, sec);
		}
		else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/GLSL", type, sec);
		}
		else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/HLSL", type, sec);
		}
	}


}

