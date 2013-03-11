#include "Scene.h"

Scene::Scene (ShortStory *shortStory) :
		mShortStory(shortStory), nTerrain(0), nCamera(0), nCharacter(0), nCharacCamera(0)
{
    nCharacCamera = mShortStory->getSceneManager()->getRootSceneNode()->createChildSceneNode("PersonnageCameraNode");
}

Scene::~Scene ()
{
	//OGRE_DELETE mTerrain;
	//OGRE_DELETE mGlobals;
}

void Scene::createScene ()
{
	setLight();
	setTerrain();
	setSky();
	setRain();
	setImmeuble();
	setPersonnage();
	setCamera();
	setMeshes();
}

void Scene::setLight ()
{
	mShortStory->getSceneManager()->setAmbientLight(ColourValue(0.5f, 0.5f, 0.5f));
	Light* ambientLight = mShortStory->getSceneManager()->createLight("MainLight");
	ambientLight->setPosition(20, 80, 50);
}

void Scene::setTerrain ()
{
    SceneManager* sceneManager = mShortStory->getSceneManager();
    Plane plan(Vector3::UNIT_Y, 0);
    MeshManager::getSingleton().createPlane("sol", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plan, 10000, 10000, 1, 1, true, 1, 50, 50, Vector3::UNIT_Z);
	Entity *ent= sceneManager->createEntity("EntiteSol", "sol");
    nTerrain = sceneManager->getRootSceneNode()->createChildSceneNode();
    nTerrain->attachObject(ent);
    ent->setMaterialName("Plane");


    //**street lamp 1**//
    Entity* streetLamp1 = mShortStory->getSceneManager()->createEntity("streetLamp1", "streetLamp.mesh");
    streetLamp1->setCastShadows(true);

    //node
    SceneNode* streetLamp1Node = mShortStory->getSceneManager()->getRootSceneNode()->createChildSceneNode("streetLamp1Node");
    streetLamp1Node->attachObject(streetLamp1);
    streetLamp1Node->setPosition(600., 0., 200.);
    streetLamp1Node->scale(2, 2, 2);

    //light 1
    Ogre::Light* streetLamp1B1 = mShortStory->getSceneManager()->createLight("streetLamp1B1");
    streetLamp1B1->setType(Ogre::Light::LT_SPOTLIGHT);
    streetLamp1B1->setDirection(0, -1, 0);
    streetLamp1B1->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));
    streetLamp1B1->setPosition(streetLamp1Node->getPosition()+Ogre::Vector3( 60, 500, 60));
    streetLamp1B1->setAttenuation(700,0.5,0,0);
    streetLamp1B1->setDiffuseColour(1., 1, 0);
    streetLamp1B1->setSpecularColour(1., 1, 0);

    //light 2
    Ogre::Light* streetLamp1B2 = mShortStory->getSceneManager()->createLight("streetLamp1B2");
    streetLamp1B2->setType(Ogre::Light::LT_SPOTLIGHT);
    streetLamp1B2->setDirection(0, -1, 0);
    streetLamp1B2->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));
    streetLamp1B2->setPosition(streetLamp1Node->getPosition()+Ogre::Vector3( -60, 500, 60));
    streetLamp1B2->setAttenuation(700,0.5,0,0);
    streetLamp1B2->setDiffuseColour(1., 1, 0);
    streetLamp1B2->setSpecularColour(1., 1, 0);

    //light 3
    Ogre::Light* streetLamp1B3 = mShortStory->getSceneManager()->createLight("streetLamp1B3");
    streetLamp1B3->setType(Ogre::Light::LT_SPOTLIGHT);
    streetLamp1B3->setDirection(0, -1, 0);
    streetLamp1B3->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));
    streetLamp1B3->setPosition(streetLamp1Node->getPosition()+Ogre::Vector3( -60, 500, -60));
    streetLamp1B3->setAttenuation(700,0.5,0,0);
    streetLamp1B3->setDiffuseColour(1., 1, 0);
    streetLamp1B3->setSpecularColour(1., 1, 0);

    //**street lamp**//
    Entity* streetLamp2 = mShortStory->getSceneManager()->createEntity("streetLamp2", "streetLamp.mesh");
    streetLamp2->setCastShadows(true);

    //node
    SceneNode* streetLamp2Node = mShortStory->getSceneManager()->getRootSceneNode()->createChildSceneNode("streetLamp2Node");
    streetLamp2Node->attachObject(streetLamp2);
    streetLamp2Node->setPosition(0., 0., 200.);
    streetLamp2Node->scale(2, 2, 2);

    //light 1
    Ogre::Light* streetLamp2B1 = mShortStory->getSceneManager()->createLight("streetLamp2B1");
    streetLamp2B1->setType(Ogre::Light::LT_SPOTLIGHT);
    streetLamp2B1->setDirection(0, -1, 0);
    streetLamp2B1->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));
    streetLamp2B1->setPosition(streetLamp2Node->getPosition()+Ogre::Vector3( 60, 500, 60));
    streetLamp2B1->setAttenuation(700,0.5,0,0);
    streetLamp2B1->setDiffuseColour(1., 1, 0);
    streetLamp2B1->setSpecularColour(1., 1, 0);

    //light 2
    Ogre::Light* streetLamp2B2 = mShortStory->getSceneManager()->createLight("streetLamp2B2");
    streetLamp2B2->setType(Ogre::Light::LT_SPOTLIGHT);
    streetLamp2B2->setDirection(0, -1, 0);
    streetLamp2B2->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));
    streetLamp2B2->setPosition(streetLamp2Node->getPosition()+Ogre::Vector3( -60, 500, 60));
    streetLamp2B2->setAttenuation(700,0.5,0,0);
    streetLamp2B2->setDiffuseColour(1., 1, 0);
    streetLamp2B2->setSpecularColour(1., 1, 0);

    //light 3
    Ogre::Light* streetLamp3B3 = mShortStory->getSceneManager()->createLight("streetLamp2B3");
    streetLamp3B3->setType(Ogre::Light::LT_SPOTLIGHT);
    streetLamp3B3->setDirection(0, -1, 0);
    streetLamp3B3->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));
    streetLamp3B3->setPosition(streetLamp2Node->getPosition()+Ogre::Vector3( -60, 500, -60));
    streetLamp3B3->setAttenuation(700,0.5,0,0);
    streetLamp3B3->setDiffuseColour(1., 1, 0);
    streetLamp3B3->setSpecularColour(1., 1, 0);
}

void Scene::setSky ()
{
	//mShortStory->getSceneManager()->setSkyDome(true, "CloudySky", 5, 8);
    Plane plane;
    plane.d = 10000;
    plane.normal = Ogre::Vector3::NEGATIVE_UNIT_Y;
    mShortStory->getSceneManager()->setSkyPlane(true, plane, "NightCloudySky", 1500, 10, true, 1.5f, 150, 150);
}

void Scene::setRain ()
{
	ParticleSystem * rainParticle = mShortStory->getSceneManager()->createParticleSystem("rain", "Rain");
	SceneNode * rainNode = mShortStory->getSceneManager()->getRootSceneNode()->createChildSceneNode("rainNode",
	        Ogre::Vector3(100, 0, 0));
	rainNode->translate(0, 3000, 0, Node::TS_PARENT);
	rainNode->attachObject(rainParticle);
}

void Scene::setImmeuble ()
{
	Entity* immeuble = mShortStory->getSceneManager()->createEntity("Immeuble", "immeuble2.mesh");
	SceneNode* immeubleNode = mShortStory->getSceneManager()->getRootSceneNode()->createChildSceneNode("ImmeubleNode");
	immeubleNode->attachObject(immeuble);

	immeubleNode->setPosition(0., 1., 0.);
	immeubleNode->scale(100., 100., 100.);

}

void Scene::setPersonnage ()
{
	Entity* personnage = mShortStory->getSceneManager()->createEntity("Personnage", "Personnage.mesh");

	nCharacter = nCharacCamera->createChildSceneNode("CharacterNode");
    nCharacter->attachObject(personnage);

	nCharacter->setPosition(300., 100., 200.);
	nCharacter->scale(0.5, 0.5, 0.5);
}

void Scene::setCamera ()
{
    mShortStory->getCamera()->setPosition(Vector3(300, 500, 1000));

    nCharacCamera->attachObject(mShortStory->getCamera());
}

void Scene::setMeshes ()
{

}

SceneNode* Scene::getImmeubleNode()
{
    return nImmeuble;
}

SceneNode* Scene::getTerrainNode()
{
    return nTerrain;
}

SceneNode* Scene::getCharacterCameraNode()
{
    return nCharacCamera;
}

SceneNode* Scene::getCameraNode()
{
    return nCamera;
}

SceneNode* Scene::getCharacterNode()
{
    return nCharacter;
}
