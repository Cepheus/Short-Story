/*
Filename:    MainApplication.cpp
*/
#include "MainApplication.h"

using namespace Ogre;
using namespace std;

MainApplication::MainApplication(void)
{
}

MainApplication::~MainApplication(void)
{
}

void MainApplication::createScene(void)
{
    //sky
    mSceneMgr->setSkyDome(true, "CloudySky", 5, 8);

    // Light
    mSceneMgr->setAmbientLight(ColourValue(0.5f, 0.5f, 0.5f));
    Light* ambientLight = mSceneMgr->createLight( "MainLight" );
    ambientLight->setPosition(20, 80, 50);

    // Création du sol
    MeshManager::getSingleton().createPlane("sol", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Plane(Ogre::Vector3::UNIT_Y, 0), 2000, 2000, 20, 20, true, 1, 1, 1, Vector3::UNIT_Z);
    Entity *sol= mSceneMgr->createEntity("EntiteSol", "sol");
    sol->setMaterialName("Examples/GrassFloor");

    SceneNode* solNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("sol");
    solNode->setPosition(Ogre::Vector3(0, 0, 0));
    solNode->attachObject(sol);

    // Terrain

    // Immeuble
    Entity* immeuble = mSceneMgr->createEntity("Immeuble", "immeuble.mesh");
    SceneNode* immeubleNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("ImmeubleNode");
    immeubleNode->attachObject(immeuble);

    immeubleNode->setPosition(0.,80.,0.); //0.,42.,0.
    immeubleNode->scale(100.,100.,100.);

    //rain
    Ogre::ParticleSystem * rainParticle = mSceneMgr->createParticleSystem("rain", "Rain");
    Ogre::SceneNode * rainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode( "rainNode", Ogre::Vector3( 100, 0, 0 ) );
    rainNode->translate(0, 900, 0, Ogre::Node::TS_PARENT);
    rainNode->attachObject(rainParticle);

    // Rayon
    /*Ray ray = Ray(Vector3(mCamera->getPosition().x, 1000.0f, mCamera->getPosition().z), Vector3::NEGATIVE_UNIT_Y);
    pair<bool, Vector3> result = terrain->rayIntersects(ray);

    if (result.first) {
        mCamera->setY(result.second.y + 10);
    }*/

}

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        MainApplication app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
