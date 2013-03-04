#include "Scene.h"

Scene::Scene (SceneManager *scenemgr) :
		mSceneMgr(scenemgr), mTerrain(0), mGlobals(0)
{
}

Scene::~Scene ()
{
	OGRE_DELETE mTerrain;
	OGRE_DELETE mGlobals;
}

void Scene::createScene ()
{
	setLight();
	setTerrain();
	setSky();
	setRain();
	setImmeuble();
	setPersonnage();
	setMeshes();
}

void Scene::setLight ()
{
	mSceneMgr->setAmbientLight(ColourValue(0.5f, 0.5f, 0.5f));
	Light* ambientLight = mSceneMgr->createLight("MainLight");
	ambientLight->setPosition(20, 80, 50);
}

void Scene::setTerrain ()
{
	MeshManager::getSingleton().createPlane("sol", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	        Plane(Ogre::Vector3::UNIT_Y, 0), 2000, 2000, 20, 20, true, 1, 1, 1, Vector3::UNIT_Z);
	Entity *sol = mSceneMgr->createEntity("EntiteSol", "sol");
	sol->setMaterialName("Examples/GrassFloor");

	SceneNode* solNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("sol");
	solNode->setPosition(Ogre::Vector3(0, 0, 0));
	solNode->attachObject(sol);

	/*mGlobals = OGRE_NEW TerrainGlobalOptions();
	 mGlobals->setMaxPixelError(8);

	 Vector3 lightdir(0.55f, -0.3f, 0.75f);
	 mLight = mSceneMgr->createLight("terrainLight");
	 mLight->setType(Light::LT_DIRECTIONAL);
	 mLight->setDirection(lightdir);
	 mLight->setDiffuseColour(ColourValue::White);
	 mLight->setSpecularColour(ColourValue(0.4f, 0.4f, 0.4f));

	 mGlobals->setLightMapDirection(mLight->getDerivedDirection());
	 mGlobals->setCompositeMapDistance(3000);
	 mGlobals->setCompositeMapAmbient(mSceneMgr->getAmbientLight());
	 mGlobals->setCompositeMapDiffuse(mLight->getDiffuseColour());

	 mTerrain = OGRE_NEW Terrain(mSceneMgr);*/
}

void Scene::setSky ()
{
	mSceneMgr->setSkyDome(true, "CloudySky", 5, 8);
}

void Scene::setRain ()
{
	ParticleSystem * rainParticle = mSceneMgr->createParticleSystem("rain", "Rain");
	SceneNode * rainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("rainNode", Ogre::Vector3(100, 0, 0));
	rainNode->translate(0, 900, 0, Node::TS_PARENT);
	rainNode->attachObject(rainParticle);
}

void Scene::setImmeuble ()
{
	Entity* immeuble = mSceneMgr->createEntity("Immeuble", "immeuble.mesh");
	SceneNode* immeubleNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("ImmeubleNode");
	immeubleNode->attachObject(immeuble);

	immeubleNode->setPosition(0., 80., 0.); //0.,42.,0.
	immeubleNode->scale(100., 100., 100.);
}

void Scene::setPersonnage ()
{
	//Entity* personnage = mSceneMgr->createEntity("Personnage", "");
}

void Scene::setMeshes ()
{

}
