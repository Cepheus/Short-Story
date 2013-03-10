#include "Scene.h"

Scene::Scene (ShortStory *shortStory) :
		mShortStory(shortStory), mTerrain(0), terrainLight(0), mGlobals(0)
{
}

Scene::~Scene ()
{
	OGRE_DELETE mTerrain;
	OGRE_DELETE mGlobals;
}

void Scene::createScene ()
{
	mShortStory->getCamera()->setPosition(Vector3(300, 500, 1000));

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
	//lumiere du terrain
	Ogre::Vector3 lightdir(0.55f, -0.3f, 0.75f);
	terrainLight = mShortStory->getSceneManager()->createLight("terrainLight");
	terrainLight->setType(Ogre::Light::LT_DIRECTIONAL);
	terrainLight->setDirection(lightdir);
	terrainLight->setDiffuseColour(Ogre::ColourValue::White);
	terrainLight->setSpecularColour(Ogre::ColourValue(0.4f, 0.4f, 0.4f));

	mShortStory->getSceneManager()->setAmbientLight(ColourValue(0.5f, 0.5f, 0.5f));
	Light* ambientLight = mShortStory->getSceneManager()->createLight("MainLight");
	ambientLight->setPosition(20, 80, 50);
}

void Scene::setTerrain ()
{
	//initialisation
	mGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();
	mGlobals->setMaxPixelError(8); //précision avec la quelle le terrain est rendu

	//lumere sur le terrain
	mGlobals->setLightMapDirection(terrainLight->getDerivedDirection());
	mGlobals->setCompositeMapDistance(3000);
	mGlobals->setCompositeMapAmbient(mShortStory->getSceneManager()->getAmbientLight());
	mGlobals->setCompositeMapDiffuse(terrainLight->getDiffuseColour());

	//definition du terrain
	mTerrain = OGRE_NEW Ogre::Terrain(mShortStory->getSceneManager());

	// bump mapping : image
	Ogre::Image img;
	img.load("terrain.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

	//Les paramčtres géométriques
	Ogre::Terrain::ImportData imp;
	imp.inputImage = &img;
	imp.terrainSize = img.getWidth();
	imp.worldSize = 50000; //tail du terrain
	imp.inputScale = 0; //hauteur du terrain
	imp.minBatchSize = 33; //lod terrain min
	imp.maxBatchSize = 65;  //lod terrain max : 65 c'est le maximum sinon 2^n+1

	//textures
	imp.layerList.resize(3);
	imp.layerList[0].worldSize = 200; //taille de la texture dans le monde
	imp.layerList[0].textureNames.push_back("ground.jpg"); //une texture diffuse, qui contient les couleurs, les motifs du matériau ;
	imp.layerList[0].textureNames.push_back("ground.jpg"); //une texture normale, contenant des informations sur le relief du matériau.


	//charge le terrain dans la scene
	mTerrain->prepare(imp);
	mTerrain->load();

	//fait de la place en memoire
	mTerrain->freeTemporaryResources();
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

	immeubleNode->setPosition(0., mTerrain->getHeightAtPoint(0., 0.)+1., 0.);
	immeubleNode->scale(100., 100., 100.);

}

void Scene::setPersonnage ()
{
	Entity* personnage = mShortStory->getSceneManager()->createEntity("Personnage", "Personnage.mesh");
	SceneNode* personnageNode = mShortStory->getSceneManager()->getRootSceneNode()->createChildSceneNode("PersonnageNode");
	personnageNode->attachObject(personnage);

	personnageNode->setPosition(300., mTerrain->getHeightAtPoint(0., 0.)+100., 200.);
	personnageNode->scale(0.5, 0.5, 0.5);
}

void Scene::setMeshes ()
{

}
