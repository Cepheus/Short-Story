#include "Scene.h"
#include <OgreProgressiveMesh.h>
#include "InputListener.h"

Scene::Scene (ShortStory *shortStory) :
		mShortStory(shortStory), nTerrain(0), nCharacCamera(0), nCharacter(0), nCamera(0), nImmeuble(0), dDistanceCharacCamera(
		        100), mTerrain(0), terrainLight(0), mGlobals(0), inBuilding(false), windowIsDestroy(false),doorIsDestroy(true),
		         picking(mShortStory->getSceneManager())
{
	nCharacCamera = mShortStory->getSceneManager()->getRootSceneNode()->createChildSceneNode("PersonnageCameraNode");
	nCharacCamera->setPosition(300., HAUTEUR_PERS, 500.);
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
	setChat();
	setCamera();
	setMeshes(true);
	//setDoor();
}

void Scene::setLight ()
{
	mShortStory->getSceneManager()->setAmbientLight(ColourValue(0.3f, 0.3f, 0.3f));
	Light* ambientLight = mShortStory->getSceneManager()->createLight("MainLight");
	ambientLight->setPosition(20, 80, 50);
}

void Scene::setTerrain ()
{
    //fog
    mShortStory->getSceneManager()->setFog(Ogre::FOG_EXP2, Ogre::ColourValue::Black, 0.0002, 1500, 2000);

	//sol palpable
	SceneManager* sceneManager = mShortStory->getSceneManager();
	Plane plan(Ogre::Vector3::UNIT_Y, 0);
    MeshManager::getSingleton().createPlane("sol", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plan, 3000, 3000,
	        100, 100, true, 1, 50, 50, Ogre::Vector3::UNIT_Z);
	Entity *ent = sceneManager->createEntity("EntiteSol", "sol");
	nTerrain = sceneManager->getRootSceneNode()->createChildSceneNode();
	nTerrain->attachObject(ent);
    nTerrain->setPosition(-500,0,500);
    ent->setMaterialName("Plane");
	ent->setCastShadows(true);

	//**street lamp 1**//
    Real range = 2000;
	Real attenuation = 1.0;
	Real linear = 4.5 / range;
	Real Quadratic = 75.0 / (range * range);

	Entity* streetLamp1 = mShortStory->getSceneManager()->createEntity("streetLamp1", "streetLamp.mesh");
	streetLamp1->setCastShadows(true);

	//node
	SceneNode* streetLamp1Node = mShortStory->getSceneManager()->getRootSceneNode()->createChildSceneNode(
	        "streetLamp1Node");
	streetLamp1Node->attachObject(streetLamp1);
	streetLamp1Node->setPosition(-400, 0., 0.);
	streetLamp1Node->scale(2, 2, 2);

	//light 1
	Ogre::Light* streetLamp1B1 = mShortStory->getSceneManager()->createLight("streetLamp1B1");
	streetLamp1B1->setType(Ogre::Light::LT_SPOTLIGHT);
	streetLamp1B1->setDirection(0, -1, 0);
	streetLamp1B1->setSpotlightRange(Ogre::Degree(30), Ogre::Degree(90));
	streetLamp1B1->setPosition(streetLamp1Node->getPosition() + Ogre::Vector3(30, 500, 15));
	streetLamp1B1->setAttenuation(range, attenuation, linear, Quadratic);
	streetLamp1B1->setDiffuseColour(1., 1, 0);
	streetLamp1B1->setSpecularColour(1., 1, 0);

	//light 2
	Ogre::Light* streetLamp1B2 = mShortStory->getSceneManager()->createLight("streetLamp1B2");
	streetLamp1B2->setType(Ogre::Light::LT_SPOTLIGHT);
	streetLamp1B2->setDirection(0, -1, 0);
	streetLamp1B2->setSpotlightRange(Ogre::Degree(30), Ogre::Degree(90));
	streetLamp1B2->setPosition(streetLamp1Node->getPosition() + Ogre::Vector3(-30, 500, 15));
	streetLamp1B2->setAttenuation(range, attenuation, linear, Quadratic);
	streetLamp1B2->setDiffuseColour(1., 1, 0);
	streetLamp1B2->setSpecularColour(1., 1, 0);

	//light 3
	Ogre::Light* streetLamp1B3 = mShortStory->getSceneManager()->createLight("streetLamp1B3");
	streetLamp1B3->setType(Ogre::Light::LT_SPOTLIGHT);
	streetLamp1B3->setDirection(0, -1, 0);
	streetLamp1B3->setSpotlightRange(Ogre::Degree(30), Ogre::Degree(90));
	streetLamp1B3->setPosition(streetLamp1Node->getPosition() + Ogre::Vector3(0, 500, -15));
	streetLamp1B3->setAttenuation(range, attenuation, linear, Quadratic);
	streetLamp1B3->setDiffuseColour(1., 1, 0);
	streetLamp1B3->setSpecularColour(1., 1, 0);

	//**street lamp**//
	Entity* streetLamp2 = mShortStory->getSceneManager()->createEntity("streetLamp2", "streetLamp.mesh");
	streetLamp2->setCastShadows(true);

	//node
    SceneNode* streetLamp2Node = mShortStory->getSceneManager()->getRootSceneNode()->createChildSceneNode(
	        "streetLamp2Node");
	streetLamp2Node->attachObject(streetLamp2);
	streetLamp2Node->setPosition(600., 0., 400.);
	streetLamp2Node->scale(2, 2, 2);

	//light 1
	Ogre::Light* streetLamp2B1 = mShortStory->getSceneManager()->createLight("streetLamp2B1");
	streetLamp2B1->setType(Ogre::Light::LT_SPOTLIGHT);
	streetLamp2B1->setDirection(0, -1, 0);
	streetLamp2B1->setSpotlightRange(Ogre::Degree(30), Ogre::Degree(90));
	streetLamp2B1->setPosition(streetLamp2Node->getPosition() + Ogre::Vector3(30, 500, 15));
	streetLamp2B1->setAttenuation(range, attenuation, linear, Quadratic);
	streetLamp2B1->setDiffuseColour(1., 1, 0);
	streetLamp2B1->setSpecularColour(1., 1, 0);

	//light 2
	Ogre::Light* streetLamp2B2 = mShortStory->getSceneManager()->createLight("streetLamp2B2");
	streetLamp2B2->setType(Ogre::Light::LT_SPOTLIGHT);
	streetLamp2B2->setDirection(0, -1, 0);
	streetLamp2B2->setSpotlightRange(Ogre::Degree(30), Ogre::Degree(90));
	streetLamp2B2->setPosition(streetLamp2Node->getPosition() + Ogre::Vector3(30, 500, -15));
	streetLamp2B2->setAttenuation(range, attenuation, linear, Quadratic);
	streetLamp2B2->setDiffuseColour(1., 1, 0);
	streetLamp2B2->setSpecularColour(1., 1, 0);

	//light 3
	Ogre::Light* streetLamp3B3 = mShortStory->getSceneManager()->createLight("streetLamp2B3");
	streetLamp3B3->setType(Ogre::Light::LT_SPOTLIGHT);
	streetLamp3B3->setDirection(0, -1, 0);
	streetLamp3B3->setSpotlightRange(Ogre::Degree(30), Ogre::Degree(90));
	streetLamp3B3->setPosition(streetLamp2Node->getPosition() + Ogre::Vector3(0, 500, -15));
	streetLamp3B3->setAttenuation(range, attenuation, linear, Quadratic);
	streetLamp3B3->setDiffuseColour(1., 1, 0);
	streetLamp3B3->setSpecularColour(1., 1, 0);

	//terrain exterieur non palpable

	//initialisation
	mGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();
	mGlobals->setMaxPixelError(8); //prÃ©cision avec la quelle le terrain est rendu

	//lumiere du terrain
	Ogre::Vector3 lightdir(0.55f, -0.3f, 0.75f);
	terrainLight = mShortStory->getSceneManager()->createLight("terrainLight");
	terrainLight->setType(Ogre::Light::LT_DIRECTIONAL);
	terrainLight->setDirection(lightdir);
	terrainLight->setDiffuseColour(Ogre::ColourValue::Black);
	terrainLight->setSpecularColour(Ogre::ColourValue(0.5f, 0.5f, 0.5f));

	//lumere sur le terrain
	mGlobals->setLightMapDirection(terrainLight->getDerivedDirection());
	mGlobals->setCompositeMapDistance(3000);
	mGlobals->setCompositeMapAmbient(mShortStory->getSceneManager()->getAmbientLight());
	mGlobals->setCompositeMapDiffuse(terrainLight->getDiffuseColour());

	//definition du terrain
	mTerrain = OGRE_NEW Ogre::Terrain(mShortStory->getSceneManager());

	// bump mapping : image
	Ogre::Image img;
	img.load("heightmap.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

    //Les paramÄtres gÃ©omÃ©triques
	Ogre::Terrain::ImportData imp;
	imp.inputImage = &img;
	imp.terrainSize = img.getWidth();
    imp.worldSize = 12000; //tail du terrain
	imp.inputScale = imp.worldSize * 1 / 10; //hauteur du terrain
	imp.minBatchSize = 33; //lod terrain min
	imp.maxBatchSize = 65; //lod terrain max : 65 c'est le maximum sinon 2^n+1

	//textures
	imp.layerList.resize(3);
	imp.layerList[0].worldSize = 100; //tail de la texture dans le monde
	imp.layerList[0].textureNames.push_back("grass_green-01_diffusespecular.dds"); //une texture diffuse, qui contient les couleurs, les motifs du matÃ©riau ;
	imp.layerList[0].textureNames.push_back("grass_green-01_normalheight.dds"); //une texture normale, contenant des informations sur le relief du matÃ©riau.
	imp.layerList[1].worldSize = 300;
	imp.layerList[1].textureNames.push_back("growth_weirdfungus-03_diffusespecular.dds");
	imp.layerList[1].textureNames.push_back("growth_weirdfungus-03_normalheight.dds");
	imp.layerList[2].worldSize = 300;
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

	Ogre::Real minHeight1 = imp.inputScale * 5 / 500;
	Ogre::Real fadeDist1 = imp.inputScale * 600 / 1000;
    Ogre::Real minHeight2 = imp.inputScale * 200 / 1000;
	Ogre::Real fadeDist2 = imp.inputScale * 800 / 1000;

	for (Ogre::uint16 y = 0; y < mTerrain->getLayerBlendMapSize(); ++y)
	{
		for (Ogre::uint16 x = 0; x < mTerrain->getLayerBlendMapSize(); ++x)
		{
			Ogre::Real terrainX, terrainY, transparence;

			blendMap1->convertImageToTerrainSpace(x, y, &terrainX, &terrainY);
			Ogre::Real height = mTerrain->getHeightAtTerrainPosition(terrainX, terrainY);

			transparence = (height - minHeight1) / fadeDist1;
			transparence = Ogre::Math::Clamp(transparence, (Ogre::Real) 0, (Ogre::Real) 1);
			*pBlend1++ = transparence * 255;

			transparence = (height - minHeight2) / fadeDist2;
			transparence = Ogre::Math::Clamp(transparence, (Ogre::Real) 0, (Ogre::Real) 1);
			*pBlend2++ = transparence * 255;
		}
	}

    blendMap1->dirty(); //prÃ©ciser que les donnÃ©es de la TerrainLayerBlendMap sont obsolÄtes
	blendMap1->update(); //mise a jour
	blendMap2->dirty();
	blendMap2->update();

	//fait de la place en memoire
	mTerrain->freeTemporaryResources();
    mTerrain->setPosition(Ogre::Vector3(600, -30, 0));

    //Forets
//    Ogre::FloatRect TextureCoordinates[]={
//        Ogre::FloatRect(113.0/5000.0,121.0/5000.0,851.0/5000.0,1073.0/
//        5000.0),
//        Ogre::FloatRect(1021.0/5000.0,114.0/5000.0,3386.0/5000.0,1984.0/
//        5000.0),
//        Ogre::FloatRect(3825.0/5000.0,1049.0/5000.0,4871.0/
//        5000.0,3588.0/5000.0),
//        Ogre::FloatRect(1739.0/5000.0,2418.0/5000.0,2796.0/
//        5000.0,4774.0/5000.0),
//        Ogre::FloatRect(221.0/5000.0,2723.0/5000.0,1464.0/
//        5000.0,3795.0/5000.0),
//        Ogre::FloatRect(505.0/5000.0,4391.0/5000.0,805.0/
//        5000.0,4662.0/5000.0),
//        Ogre::FloatRect(339.0/5000.0,2085.0/5000.0,482.0/
//        5000.0,2216.0/5000.0),
//        Ogre::FloatRect(2803.0/5000.0,3355.0/5000.0,3891.0/
//        5000.0,4912.0/5000.0)
//    };

//    Ogre::BillboardSet *Trees = mShortStory->getSceneManager()->createBillboardSet("Trees");
//    Trees->setTextureCoords(TextureCoordinates, 8);
//    Trees->setMaterialName("Trees");
//    Trees->setCastShadows(true);
//    Trees->setSortingEnabled(true);
//    Trees->setBillboardType(Ogre::BBT_ORIENTED_COMMON);

//    double x = 0.0;
//    double y = 0.0;
//    double z = 0.0;
//    double TreeWidth;
//    double TreeHeight;
//    int TextureIndex;
//    for (int i = 0; i < 10; i++) {
//        for (int j = 0; j < 10; j++) {
//            x = i * 5;
//            y = j * 5;
//            z = 0;
//            TextureIndex = (i + j) / 10;
//            TreeWidth = (i + j + 10) / 10;
//            TreeHeight = (i + j + 10) / 5;
//            Ogre::Vector3 TreePosition(x/10, y/10, z);
//            Ogre::Billboard* Tree = Trees->createBillboard(TreePosition);
//            Tree->setDimensions(TreeWidth, TreeHeight);
//            Tree->setTexcoordIndex(TextureIndex);
//        }
//    }

//    SceneNode* TreesNode = mShortStory->getSceneManager()->getRootSceneNode()->createChildSceneNode("TreesNode");
//    TreesNode->attachObject(Trees);
//    TreesNode->setPosition(-1000,0,200);
//    TreesNode->rotate(Quaternion(Degree(-90), Vector3::UNIT_X));
//    TreesNode->scale(100,100,100);

    //Arbres
    Ogre::FloatRect TextureCoordinates[]={
        Ogre::FloatRect(113.0/5000.0,121.0/5000.0,851.0/5000.0,1073.0/
        5000.0),
        Ogre::FloatRect(1021.0/5000.0,114.0/5000.0,3386.0/5000.0,1984.0/
        5000.0),
        Ogre::FloatRect(3825.0/5000.0,1049.0/5000.0,4871.0/
        5000.0,3588.0/5000.0),
        Ogre::FloatRect(1739.0/5000.0,2418.0/5000.0,2796.0/
        5000.0,4774.0/5000.0),
        Ogre::FloatRect(221.0/5000.0,2723.0/5000.0,1464.0/
        5000.0,3795.0/5000.0),
        Ogre::FloatRect(505.0/5000.0,4391.0/5000.0,805.0/
        5000.0,4662.0/5000.0),
        Ogre::FloatRect(339.0/5000.0,2085.0/5000.0,482.0/
        5000.0,2216.0/5000.0),
        Ogre::FloatRect(2803.0/5000.0,3355.0/5000.0,3891.0/
        5000.0,4912.0/5000.0)
    };

    Ogre::BillboardSet *Trees = mShortStory->getSceneManager()->createBillboardSet("Tree");
    Trees->setTextureCoords(TextureCoordinates, 8);
    Trees->setMaterialName("Trees");
    Trees->setCastShadows(true);
    Trees->setSortingEnabled(true);
    Trees->setBillboardType(Ogre::BBT_ORIENTED_COMMON);

    Ogre::Vector3 TreePosition(0, 0, 0);
    Ogre::Billboard* Tree = Trees->createBillboard(TreePosition);
    Tree->setTexcoordIndex(1);

    SceneNode* TreesNode = mShortStory->getSceneManager()->getRootSceneNode()->createChildSceneNode("TreeNode");
    TreesNode->attachObject(Trees);
    TreesNode->setPosition(-1030,230,-270);
    TreesNode->rotate(Quaternion(Degree(-90), Ogre::Vector3::UNIT_X));
    TreesNode->scale(5,5,5);
}

void Scene::setSky ()
{
	//mShortStory->getSceneManager()->setSkyDome(true, "CloudySky", 5, 8);
	Plane plane;
    plane.d = 2000;
	plane.normal = Ogre::Vector3::NEGATIVE_UNIT_Y;
    mShortStory->getSceneManager()->setSkyPlane(true, plane, "NightCloudySky", 500, 10, true, 1.5f, 150, 150);
}

void Scene::setRain ()
{
    //plue sur la camera
    ParticleSystem * characterRain = mShortStory->getSceneManager()->createParticleSystem("CharacterRain", "Rain/Personnage");
    SceneNode * characterRainNode = nCharacCamera->createChildSceneNode("CharacterRainNode");
    characterRainNode->setPosition(0,200,0);
    characterRainNode->attachObject(characterRain);
    characterRain->setVisible(true); //visible par defaut

    //pluis exterieur
    SceneNode * rainGeneralNode = mShortStory->getSceneManager()->getRootSceneNode()->createChildSceneNode("rainGeneralNode",Ogre::Vector3(0, 0, 0));

    //gauche
    ParticleSystem * rainParticleGauche = mShortStory->getSceneManager()->createParticleSystem("rainGauche", "Rain");
    SceneNode * rainGaucheNode = rainGeneralNode->createChildSceneNode("rainGaucheNode",
            Ogre::Vector3(50, 3200, -100));
    rainGaucheNode->attachObject(rainParticleGauche);
    rainParticleGauche->setVisible(false); //masquÃ© par defaut

    //devant
    ParticleSystem * rainParticleDevant = mShortStory->getSceneManager()->createParticleSystem("rainDevant", "Rain");
    SceneNode * rainDevantNode = rainGeneralNode->createChildSceneNode("rainDevantNode",
            Ogre::Vector3(0, 3200, -50));
    rainDevantNode->rotate(Ogre::Vector3(0,1,0), Degree(90));
    rainDevantNode->attachObject(rainParticleDevant);
    rainDevantNode->setVisible(false); //masquÃ© par defaut
}

void Scene::setImmeuble ()
{
	Entity* immeuble = mShortStory->getSceneManager()->createEntity("Immeuble", "immeuble2.mesh");
	nImmeuble = mShortStory->getSceneManager()->getRootSceneNode()->createChildSceneNode("ImmeubleNode");
	nImmeuble->attachObject(immeuble);

	nImmeuble->setPosition(0., 0., 0.);
	nImmeuble->scale(120., 100., 100.);

    Entity* window = mShortStory->getSceneManager()->createEntity("window", "VitreCassee.mesh");
    nWindow = mShortStory->getSceneManager()->getRootSceneNode()->createChildSceneNode("windowNode");
    nWindow->attachObject(window);
    nWindow->setPosition(0., 0., 0.);
    nWindow->scale(120., 100., 100.);

}

void Scene::setPersonnage ()
{
	Entity* personnage = mShortStory->getSceneManager()->createEntity("Personnage", "ninja.mesh");

	nCharacter = nCharacCamera->createChildSceneNode("CharacterNode");
	nCharacter->setPosition(0, -HAUTEUR_PERS, 0);
	nCharacter->attachObject(personnage);
	nCharacter->scale(0.75, 0.75, 0.75);
}

void Scene::setChat(){
    Entity* chat = mShortStory->getSceneManager()->createEntity("Chat", "chat.mesh");

    nChat = mShortStory->getSceneManager()->getRootSceneNode()->createChildSceneNode("ChatNode");
    nChat->setPosition(-110, 40, 500);
    nChat->attachObject(chat);
    nChat->scale(0.75, 0.75, 0.75);

    //iterateurs d'animation
    AnimationState *mAnimState;
    AnimationStateSet *set = chat->getAllAnimationStates();
    AnimationStateIterator it = set->getAnimationStateIterator();

    //load animation
    while (it.hasMoreElements())
    {
        mAnimState = it.getNext();
        mAnimState->setEnabled(false);
    }
}

void Scene::setCamera ()
{
	nCamera = nCharacCamera->createChildSceneNode("CameraNode");
	//nCamera->setPosition(0, 0, dDistanceCharacCamera);

	nCamera->attachObject(mShortStory->getCamera());
	mShortStory->getCamera()->setPosition(FAR_PERS_X, FAR_PERS_Y, dDistanceCharacCamera);
}

void Scene::setMeshes (bool withLod)
{
	if (withLod)
	{
		Ogre::MeshPtr voitureMesh = Ogre::MeshManager::getSingleton().load("Sedan02_license_R.mesh",
		        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		Ogre::Mesh::LodValueList lodDList;
		lodDList.push_back(300);
		lodDList.push_back(500);
		lodDList.push_back(700);
		Ogre::ProgressiveMesh::generateLodLevels(voitureMesh.getPointer(), lodDList,
		        Ogre::ProgressiveMesh::VRQ_PROPORTIONAL, 0.3);
	}

	Ogre::Entity* entVoiture = mShortStory->getSceneManager()->createEntity("Voiture", "Sedan02_license_R.mesh");
	entVoiture->setCastShadows(true);
	Ogre::SceneNode* VoitureNode = mShortStory->getSceneManager()->getRootSceneNode()->createChildSceneNode("Voiture");
	VoitureNode->attachObject(entVoiture);
	VoitureNode->setPosition(-500, 43, -100);
	VoitureNode->scale(10, 10, 10);
}

void Scene::setDoor()
{
    Ogre::Entity* entDoor = mShortStory->getSceneManager()->createEntity("Door", "PorteMouvante.mesh");
    Ogre::SceneNode* nDoor = mShortStory->getSceneManager()->getRootSceneNode()->createChildSceneNode("Door");
	nDoor->attachObject(entDoor);
    nDoor->setPosition(360.0, 0., -11.21);
	nDoor->scale(120., 100., 100.);
	doorIsDestroy = false;
}

SceneNode* Scene::getImmeubleNode ()
{
	return nImmeuble;
}

SceneNode* Scene::getTerrainNode ()
{
	return nTerrain;
}

SceneNode* Scene::getCharacterCameraNode ()
{
	return nCharacCamera;
}

SceneNode* Scene::getCameraNode ()
{
	return nCamera;
}

SceneNode* Scene::getCharacterNode ()
{
	return nCharacter;
}

SceneNode* Scene::getCatNode()
{
    return nChat;
}

void Scene::openDoor()
{
    if(!doorIsDestroy)
    {
        mShortStory->getSceneManager()->destroySceneNode("Door");
        doorIsDestroy  =true;
    }
}

void Scene::destroyWindow()
{
    if(!windowIsDestroy)
    {
        windowIsDestroy=true;
        Entity* window = mShortStory->getSceneManager()->getEntity("window");
        window->setVisible(false);
        mShortStory->getSceneManager()->getRootSceneNode()->removeChild(nWindow);
        ParticleSystem * windowPart = mShortStory->getSceneManager()->createParticleSystem("verresecurite", "verresecurite");
        SceneNode * windowPartNode = mShortStory->getSceneManager()->getRootSceneNode()->createChildSceneNode("verresecuriteNode",
                Ogre::Vector3(0, 1000, -600));
        windowPartNode->attachObject(windowPart);
    }
}
