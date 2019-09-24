/*
-----------------------------------------------------------------------------

Adaptado de OgreApplicationContext.h en OGREbites\include

-----------------------------------------------------------------------------
*/

#ifndef __IG2ApplicationContext_H__
#define __IG2ApplicationContext_H__

#include <string>

#include <OgreBitesPrerequisites.h>
#include <OgreBuildSettings.h>
#include <OgreLogManager.h>
#include <OgrePlugin.h>
#include <OgreFileSystemLayer.h>

#include <OgreFrameListener.h>
#include <OgreSGTechniqueResolverListener.h>
#include <OgreInput.h>
#include <OgreOverlaySystem.h> 
#include <SDL.h>  

namespace OgreBites
{
	typedef SDL_Window NativeWindowType;

	/**
	link between a renderwindow and a platform specific window
	*/
	struct NativeWindowPair
	{
		Ogre::RenderWindow* render = nullptr;
		NativeWindowType* native = nullptr;
	};

	/**
	Base class responsible for setting up a common context for applications.
	Subclass to implement specific event callbacks.
	*/
	class IG2ApplicationContext : public Ogre::FrameListener
	{
	public:
		explicit IG2ApplicationContext(const Ogre::String& appName = OGRE_VERSION_NAME);

		virtual ~IG2ApplicationContext();

		/**
		get the main RenderWindow owns the context on OpenGL
		*/
		Ogre::RenderWindow* getRenderWindow() const { return mWindow.render; }

		Ogre::Root* getRoot() const { return mRoot;	}

		Ogre::OverlaySystem* getOverlaySystem() const {	return mOverlaySystem; }

		/**
		This function initializes the render system and resources.
		*/
		void initApp();

		/**
		This function closes down the application - saves the configuration then shutdowns.
		*/
		void closeApp();

		// callback interface copied from various listeners to be used by ApplicationContext
		virtual bool frameStarted(const Ogre::FrameEvent& evt) { pollEvents(); return true;	}
		virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
		virtual bool frameEnded(const Ogre::FrameEvent& evt) { return true; }
		virtual void windowMoved(Ogre::RenderWindow* rw) {}
		virtual void windowResized(Ogre::RenderWindow* rw) {}
		virtual bool windowClosing(Ogre::RenderWindow* rw) { return true; }
		virtual void windowClosed(Ogre::RenderWindow* rw) {}
		virtual void windowFocusChange(Ogre::RenderWindow* rw) {}

		/**
		inspect the event and call one of the corresponding functions on the registered InputListener
		@param event Input Event
		@param windowID only call listeners of this window
		*/
		void _fireInputEvent(const Event& event) const;

		/**
		Initialize the RT Shader system.
		*/
		bool initialiseRTShaderSystem();

		/**
		Destroy the RT Shader system.
		*/
		void destroyRTShaderSystem();

		/**
		Sets up the context after configuration.
		*/
		virtual void setup();

		/**
		Creates the OGRE root.
		*/
		virtual void createRoot();

		/**
		Configures the startup settings for OGRE. I use the config dialog here,
		but you can also restore from a config file. Note that this only happens
		when you start the context, and not when you reset it.
		*/
		virtual bool oneTimeConfig();

		/**
		When input is grabbed the mouse is confined to the window.
		*/
		void setWindowGrab(bool grab);  

		/**
		Finds context-wide resource groups. I load paths from a config file here,
		but you can choose your resource locations however you want.
		*/
		virtual void locateResources();

		/**
		Loads context-wide resource groups. I chose here to simply initialise all
		groups, but you can fully load specific ones if you wish.
		*/
		virtual void loadResources();

		/**
		Cleans up and shuts down the context.
		*/
		virtual void shutdown();

		/**
		process all window events since last call
		*/
		void pollEvents();

		/** attach input listener
		@param lis the listener
		@param win the window to receive the events for.
		*/
		void addInputListener(InputListener* lis) { mInputListeners.insert(lis); }

		/** detatch input listener
		@param lis the listener
		@param win the window to receive the events for.
		*/
		void removeInputListener(InputListener* lis) { mInputListeners.erase(lis); };

		/**
		Create a new render window
		You must use SDL and not an auto-created window as SDL does not get the events otherwise.
		By default the values from ogre.cfg are used for w, h and miscParams.
		*/
		virtual NativeWindowPair createWindow(const Ogre::String& name);

	protected:

		Ogre::Root* mRoot;        // OGRE root
		NativeWindowPair mWindow; // the window

		Ogre::FileSystemLayer* mFSLayer; // File system abstraction layer
		Ogre::OverlaySystem* mOverlaySystem;  // Overlay system
		
		std::set<InputListener*> mInputListeners;

		bool mFirstRun;
		Ogre::String mAppName;
		Ogre::String mSolutionPath;    // IG2: variable para hacer las rutas relativas al directorio de la solución
		
		Ogre::String mRTShaderLibPath;
		Ogre::RTShader::ShaderGenerator * mShaderGenerator; // The Shader generator instance.
		SGTechniqueResolverListener * mMaterialMgrListener; // Shader generator material manager listener.

	};
}
/** @} */
/** @} */

#endif
