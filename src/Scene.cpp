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
