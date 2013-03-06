#include "Scene.h"

Scene::Scene (ShortStory *shortStory) :
		mShortStory(shortStory), mTerrain(0), mGlobals(0), terrainLight(0)
{
}

Scene::~Scene ()
{
	OGRE_DELETE mTerrain;
	OGRE_DELETE mGlobals;
}

void Scene::createScene ()
{
    mShortStory->getCamera()->setPosition(Vector3(1000, 1500, 1000)); //deterre la camera, !! c'est temporaire !

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
    imp.worldSize = 6000; //tail du terrain
    imp.inputScale = 1200; //hauteur du terrain
    imp.minBatchSize = 33; //lod terrain min
    imp.maxBatchSize = 65;  //lod terrain max : 65 c'est le maximum sinon 2^n+1

    //textures
    imp.layerList.resize(3);
    imp.layerList[0].worldSize = 100; //tail de la texture dans le monde
    imp.layerList[0].textureNames.push_back("grass_green-01_diffusespecular.dds"); //une texture diffuse, qui contient les couleurs, les motifs du matériau ;
    imp.layerList[0].textureNames.push_back("grass_green-01_normalheight.dds"); //une texture normale, contenant des informations sur le relief du matériau.
    imp.layerList[1].worldSize = 30;
    imp.layerList[1].textureNames.push_back("growth_weirdfungus-03_diffusespecular.dds");
    imp.layerList[1].textureNames.push_back("growth_weirdfungus-03_normalheight.dds");
    imp.layerList[2].worldSize = 200;
    imp.layerList[2].textureNames.push_back("dirt_grayrocky_diffusespecular.dds");
    imp.layerList[2].textureNames.push_back("dirt_grayrocky_normalheight.dds");

    //charge le terrain dans la scene
    mTerrain->prepare(imp);
    mTerrain->load();

    //gestion des differant niveau de textures
    Ogre::TerrainLayerBlendMap* blendMap1 = mTerrain->getLayerBlendMap(1);
    Ogre::TerrainLayerBlendMap* blendMap2 = mTerrain->getLayerBlendMap(2);

    float* pBlend1 = blendMap1->getBlendPointer();
    float* pBlend2 = blendMap2->getBlendPointer();

    Ogre::Real minHeight1 = 70;
    Ogre::Real fadeDist1 = 400;
    Ogre::Real minHeight2 = 300;
    Ogre::Real fadeDist2 = 200;

    for (Ogre::uint16 y = 0; y < mTerrain->getLayerBlendMapSize(); ++y)
    {
        for (Ogre::uint16 x = 0; x < mTerrain->getLayerBlendMapSize(); ++x)
        {
            Ogre::Real terrainX, terrainY, transparence;

            blendMap1->convertImageToTerrainSpace(x, y, &terrainX, &terrainY);
            Ogre::Real height = mTerrain->getHeightAtTerrainPosition(terrainX, terrainY);

            transparence = (height - minHeight1) / fadeDist1;
            transparence = Ogre::Math::Clamp(transparence, (Ogre::Real)0, (Ogre::Real)1);
            *pBlend1++ = transparence * 255;

            transparence = (height - minHeight2) / fadeDist2;
            transparence = Ogre::Math::Clamp(transparence, (Ogre::Real)0, (Ogre::Real)1);
            *pBlend2++ = transparence * 255;
        }
    }

    blendMap1->dirty(); //préciser que les données de la TerrainLayerBlendMap sont obsolčtes
    blendMap1->update(); //mise a jour
    blendMap2->dirty();
    blendMap2->update();

    //fait de la place en memoire
    mTerrain->freeTemporaryResources();
}

void Scene::setSky ()
{
	mShortStory->getSceneManager()->setSkyDome(true, "CloudySky", 5, 8);
}

void Scene::setRain ()
{
	ParticleSystem * rainParticle = mShortStory->getSceneManager()->createParticleSystem("rain", "Rain");
	SceneNode * rainNode = mShortStory->getSceneManager()->getRootSceneNode()->createChildSceneNode("rainNode", Ogre::Vector3(100, 0, 0));
	rainNode->translate(0, 3000, 0, Node::TS_PARENT);
	rainNode->attachObject(rainParticle);
}

void Scene::setImmeuble ()
{
	Entity* immeuble = mShortStory->getSceneManager()->createEntity("Immeuble", "immeuble.mesh");
	SceneNode* immeubleNode = mShortStory->getSceneManager()->getRootSceneNode()->createChildSceneNode("ImmeubleNode");
	immeubleNode->attachObject(immeuble);

	immeubleNode->setPosition(0., 900., 0.);
	immeubleNode->scale(100., 100., 100.);
}

void Scene::setPersonnage ()
{
	//Entity* personnage = mShortStory->getSceneManager()->createEntity("Personnage", "");
}

void Scene::setMeshes ()
{

}
