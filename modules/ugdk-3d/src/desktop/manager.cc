#include <ugdk/desktop/3D/manager.h>

#include <ugdk/desktop/3D/window.h>
#include <ugdk/desktop/module.h>
#include <ugdk/desktop/windowsettings.h>
#include <ugdk/math/integer2D.h>
#include <ugdk/debug/log.h>
#include <ugdk/system/engine.h>
#include <ugdk/system/config.h>

#ifdef UGDK_OGRE_STATIC
// FIXME: HELP, WE'RE HARD CODING THIS
#define OGRE_STATIC_GL
#define OGRE_STATIC_OctreeSceneManager
#endif

#include <OgreStaticPluginLoader.h>
#include <OgreSceneManager.h>
#include <OgreStringConverter.h>
#include <OgreRoot.h>

#include <string>
#include <sstream>
#include <vector>

#include "SDL.h"
#include "SDL_syswm.h"
#include "SDL_video.h"
#include "SDL_opengl.h"

namespace ugdk {
namespace desktop {
namespace mode3d {

using std::string;
using std::vector;
using std::stringstream;
using std::stoi;
using std::make_shared;

#ifdef OGRE_DEBUG_MODE
#define UGDK_OGRE_PLUGIN_DIR OGRE_PLUGIN_DIR_DBG
#else
#define UGDK_OGRE_PLUGIN_DIR OGRE_PLUGIN_DIR_REL
#endif

Manager::Manager(const std::vector<std::string>& plugins, const std::string& renderer_name)
: ogre_plugins_(plugins), renderer_name_(renderer_name)
{
}

Manager::~Manager() {
    delete root_;
#ifdef UGDK_OGRE_STATIC
    static_loader_->unload();
    delete static_loader_;
#endif
}

void Manager::LoadPlugin(const std::string& plugin_name) {
#ifndef UGDK_OGRE_STATIC
    std::stringstream ss;
    ss << UGDK_OGRE_PLUGIN_DIR "/" << plugin_name << OGRE_BUILD_SUFFIX;
    root_->loadPlugin(ss.str());
#endif
}

bool Manager::Initialize() {

    const auto& config = system::CurrentConfiguration();

    std::string mResourcesCfg = config.base_path + ("resources" OGRE_BUILD_SUFFIX ".cfg");

    // Create the Root
    root_ = new Ogre::Root();

#ifdef UGDK_OGRE_STATIC
    // Load static plugins
    static_loader_ = new Ogre::StaticPluginLoader();
    static_loader_->load();
#else
    for (const auto& plugin : ogre_plugins_)
        LoadPlugin(plugin);
#endif
    
    
    // Setup resources
    Ogre::ConfigFile cf;
    cf.load(mResourcesCfg);
    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements()) {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)     {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                config.base_path + (archName), typeName, secName);
        }
    }
    
    // Initialize the Root
    
    // Choose and set render system to use.
    //TODO: actually choose which render system to use, instead of using the first one.
    Ogre::RenderSystem* render_system = root_->getRenderSystemByName(renderer_name_);
    if (!render_system) {
        render_system = root_->getAvailableRenderers().front();
        debug::Log(ugdk::debug::LogLevel::WARNING, "Desktop 3D Manager", "Could not find Ogre renderer '"+renderer_name_+"', defaulting to use '"+render_system->getName()+"'.");
    }
    // Config selected render system
    //TODO: update this to actually set any non-default config options that we want.
    
    // Initialize ogre
    root_->setRenderSystem(render_system);
    root_->initialise(false);

    return true;
}

void Manager::Release() {
    // FIXME: DO SOMETHING?
}

void Manager::PresentAll(/*double dt*/) {
    //TODO: check if we dont need to use the overload which receives delta_t
    root_->renderOneFrame();
    window_->Present();
}

Ogre::RenderWindow& Manager::window() {
    return window_->ogre_window();
}

std::shared_ptr<desktop::Window> Manager::DoCreateWindow(const WindowSettings& settings) {

    Uint32 flags = SDL_WINDOW_OPENGL;
    if(settings.fullscreen) flags |= SDL_WINDOW_FULLSCREEN;

    SDL_Window* window  = SDL_CreateWindow(settings.title.c_str(),
                               SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               settings.size.x, settings.size.y,
                               flags);

    //get the native whnd
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);

    if (SDL_GetWindowWMInfo(window, &wmInfo) == SDL_FALSE)
        return std::shared_ptr<desktop::Window>(); //Couldn't get WM Info!

    SDL_GLContext glcontext = nullptr;
#ifndef __MACOSX__
    glcontext = SDL_GL_CreateContext(window);
    if (!glcontext) {
        ugdk::debug::Log(ugdk::debug::CRITICAL, "SDL_GL_CreateContext failed: " + std::string(SDL_GetError()));
        return std::shared_ptr<desktop::Window>();
    }
#endif

    Ogre::NameValuePairList params; //TODO: this could (should?) be a parameter

    switch (wmInfo.subsystem)
    {
#ifdef WIN32
    case SDL_SYSWM_WINDOWS:
        // Windows code

        params["externalGLControl"] = "1";

        // only supported for Win32 on Ogre 1.8 not on other platforms (documentation needs fixing to accurately reflect this)
        params["externalGLContext"] = Ogre::StringConverter::toString( (unsigned long)glcontext );
        params["externalWindowHandle"] = Ogre::StringConverter::toString( (unsigned long) wmInfo.info.win.window );

        break;
#elif __MACOSX__
    case SDL_SYSWM_COCOA:

        params["externalGLControl"] = "1";
        // only supported for Win32 on Ogre 1.8 not on other platforms (documentation needs fixing to accurately reflect this)
        // params["externalGLContext"] = Ogre::StringConverter::toString( glcontext );
        params["externalWindowHandle"] = OSX_cocoa_view( window->sdl_window_ );
        params["macAPI"] = "cocoa";
        params["macAPICocoaUseNSView"] = "true";

        break;
#else
    case SDL_SYSWM_X11:

        params["externalGLControl"] = "1";
        // not documented in Ogre 1.8 mainline, supported for GLX and EGL{Win32,X11}
        params["currentGLContext"] = "1";

        // NOTE: externalWindowHandle is reported as deprecated (GLX Ogre 1.8)
        //SDL_WindowData * x11_window_data = (SDL_WindowData*)window->driverdata;
        params["parentWindowHandle"] = Ogre::StringConverter::toString((unsigned long) wmInfo.info.x11.window);

        break;
#endif
    default:
        //unexpected WM
        return std::shared_ptr<desktop::Window>();
    }

    Ogre::RenderWindow* ogre_window = root_->createRenderWindow(Ogre::String(settings.title), 
                                                                settings.size.x, settings.size.y, 
                                                                settings.fullscreen, &params);
    
    // Set default number of mipmaps. Not sure if this particularly needed, but...
    //Pretty sure these calls need a RenderWindow created to work, that's why they are here for now...
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    // Initialize resource groups.
    // TODO: We might need to set resource listeners, if any, before this call.    
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    
    window_.reset(new ugdk::desktop::mode3d::Window(window, ogre_window));
    return window_;
}

std::shared_ptr<desktop::Window> Manager::DoCreateWindow(unsigned long hwnd) {
    //TODO: Not sure how to do this, or even if we can do this. So just return null
    return std::shared_ptr<desktop::Window>();
}


} // namespace mode3d
} // namespace desktop
} // namespace ugdk
