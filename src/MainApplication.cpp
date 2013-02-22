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
    // Light
    mSceneMgr->setAmbientLight(ColourValue(0.5f, 0.5f, 0.5f));
    Light* light = mSceneMgr->createLight( "MainLight" );
    light->setPosition(20, 80, 50);

    // Création du sol
    Plane plan(Vector3::UNIT_Y, 0);
    MeshManager::getSingleton().createPlane("sol", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plan, 2000, 2000, 20, 20, true, 1, 1, 1, Vector3::UNIT_Z);
    Entity *ent= mSceneMgr->createEntity("EntiteSol", "sol");
    SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    node->attachObject(ent);
    ent->setMaterialName("Examples/GrassFloor");

    // Terrain


    // Immeuble
    Entity* cube = mSceneMgr->createEntity("Cube", "Cube.mesh");
    Entity* cube001 = mSceneMgr->createEntity("Cube001", "Cube001.mesh");
    Entity* cube002 = mSceneMgr->createEntity("Cube002", "Cube002.mesh");
    Entity* cube004 = mSceneMgr->createEntity("Cube004", "Cube004.mesh");
    Entity* cube008 = mSceneMgr->createEntity("Cube008", "Cube008.mesh");
    Entity* cube020 = mSceneMgr->createEntity("Cube020", "Cube020.mesh");
    Entity* cube022 = mSceneMgr->createEntity("Cube022", "Cube022.mesh");
    Entity* cube023 = mSceneMgr->createEntity("Cube023", "Cube023.mesh");
    Entity* mesh031 = mSceneMgr->createEntity("Mesh031", "Mesh031.mesh");
    Entity* plane128 = mSceneMgr->createEntity("Plane128", "plane128.mesh");
    SceneNode* immeubleNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("ImmeubleNode");
    //immeubleNode->attachObject(cube);
    immeubleNode->attachObject(cube001);
    immeubleNode->attachObject(cube002);
    //immeubleNode->attachObject(cube004);
    immeubleNode->attachObject(cube008);
    //immeubleNode->attachObject(cube020);
    //immeubleNode->attachObject(cube022);
    //immeubleNode->attachObject(cube023);
    //immeubleNode->attachObject(mesh031);
    //immeubleNode->attachObject(plane128);

    immeubleNode->setPosition(0.,50.,0.);

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
