#include "ShortStory.h"

ShortStory::ShortStory(): mRoot(0), mWindow(0), mSceneMgr(0), mCamera(0)
{
}

ShortStory::~ShortStory()
{
    OGRE_DELETE mRoot;
}

bool ShortStory::Initialize ()
{
#ifdef _DEBUG
    Ogre::String pluginFile = "plugins_d.cfg";
#else
    Ogre::String pluginFile = "plugins.cfg";
#endif

    // on cr��e le noeud root de la sc�ne
    mRoot = OGRE_NEW Root(pluginFile);
    // on charge les objets
    ConfigFile configFile;
    configFile.load("resources.cfg");
    ConfigFile::SectionIterator seci = configFile.getSectionIterator();
    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        ConfigFile::SettingsMultiMap *settings = seci.getNext();
        ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
        }
    }
    // r�cup�ration des config de l'utilisateur
    if(!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
    {
        return false;
    }
    initScene();

    return true;
}

void ShortStory::initScene ()
{
    // oncr��e la fen�tre
    mWindow = mRoot->initialise(true, "Short Story");
    // on chargeles ressources pour de vrai
    TextureManager::getSingleton().setDefaultNumMipmaps(5);
    ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    // on cr�e le scene manager
    mSceneMgr = mRoot->createSceneManager("DefaultSceneManager", "Scene Manager");
    mSceneMgr->setAmbientLight(ColourValue(1.0f, 1.0f, 1.0f));

    // on cr�e la cam�ra
    mCamera = mSceneMgr->createCamera("PlayerCam");
    mCamera->setPosition(Vector3(0,0,100));
    mCamera->lookAt(Vector3(0,0,0));
    mCamera->setNearClipDistance(5);

    Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(ColourValue(0,0,0));
    mCamera->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));
}

bool ShortStory::start ()
{
    bool continu = true;

    while(continu)
    {
        WindowEventUtilities::messagePump();

        if(mWindow->isClosed())
            continu = false;

        if(!mRoot->renderOneFrame())
            continu = false;
    }
    return continu;
}
