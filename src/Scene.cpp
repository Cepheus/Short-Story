#include "Scene.h"
#include <OgreProgressiveMesh.h>


Scene::Scene (ShortStory *shortStory) :
		mShortStory(shortStory), nTerrain(0), nCamera(0), nCharacter(0), nCharacCamera(0), dDistanceCharacCamera(75.)
{
    nCharacCamera = mShortStory->getSceneManager()->getRootSceneNode()->createChildSceneNode("PersonnageCameraNode");
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
	setCamera();
	setMeshes(false);
}

void Scene::setLight ()
{
    mShortStory->getSceneManager()->setAmbientLight(ColourValue(0.3f, 0.3f, 0.3f));
	Light* ambientLight = mShortStory->getSceneManager()->createLight("MainLight");
	ambientLight->setPosition(20, 80, 50);
}

void Scene::setTerrain ()
{
    //sol palpable
    SceneManager* sceneManager = mShortStory->getSceneManager();
    Plane plan(Vector3::UNIT_Y, 0);
    MeshManager::getSingleton().createPlane("sol", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plan, 5000, 5000, 100, 100, true, 1, 50, 50, Vector3::UNIT_Z);
	Entity *ent= sceneManager->createEntity("EntiteSol", "sol");
    nTerrain = sceneManager->getRootSceneNode()->createChildSceneNode();
    nTerrain->attachObject(ent);
    ent->setMaterialName("Plane");
    ent->setCastShadows(true);

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

    //terrain exterieur non palpable

    //initialisation
    mGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();
    mGlobals->setMaxPixelError(8); //précision avec la quelle le terrain est rendu

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

    //Les paramčtres géométriques
    Ogre::Terrain::ImportData imp;
    imp.inputImage = &img;
    imp.terrainSize = img.getWidth();
    imp.worldSize = 12000; //tail du terrain
    imp.inputScale = imp.worldSize*1/10; //hauteur du terrain
    imp.minBatchSize = 33; //lod terrain min
    imp.maxBatchSize = 65; //lod terrain max : 65 c'est le maximum sinon 2^n+1

    //textures
    imp.layerList.resize(3);
    imp.layerList[0].worldSize = 100; //tail de la texture dans le monde
    imp.layerList[0].textureNames.push_back("grass_green-01_diffusespecular.dds"); //une texture diffuse, qui contient les couleurs, les motifs du matériau ;
    imp.layerList[0].textureNames.push_back("grass_green-01_normalheight.dds"); //une texture normale, contenant des informations sur le relief du matériau.
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

    Ogre::Real minHeight1 = imp.inputScale*5/500;
    Ogre::Real fadeDist1 = imp.inputScale*600/1000;
    Ogre::Real minHeight2 = imp.inputScale*200/1000;
    Ogre::Real fadeDist2 = imp.inputScale*800/1000;

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
        mTerrain->setPosition(Ogre::Vector3(600, -100,0));
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

	immeubleNode->setPosition(0., 0., 0.);
	immeubleNode->scale(100., 100., 100.);

}

void Scene::setPersonnage ()
{
    Entity* personnage = mShortStory->getSceneManager()->createEntity("Personnage", "ninja.mesh");

	nCharacter = nCharacCamera->createChildSceneNode("CharacterNode");
    nCharacter->attachObject(personnage);

    nCharacter->setPosition(300., 0., 500.);
	nCharacter->scale(0.5, 0.5, 0.5);
}

void Scene::walkPersonnage(const FrameEvent &evt){
    Entity* personnage = mShortStory->getSceneManager()->getEntity("Personnage");

    AnimationState *mAnimState;
    AnimationStateSet *set = personnage->getAllAnimationStates();
    AnimationStateIterator it = set->getAnimationStateIterator();

    //load animation
    while(it.hasMoreElements())
    {
        mAnimState = it.getNext();
        mAnimState->setEnabled(false);
    }

    personnage->getAnimationState("Walk")->setEnabled(true);
    personnage->getAnimationState("Walk")->addTime(evt.timeSinceLastFrame);
}

void Scene::idle1Personnage(const FrameEvent &evt){
    Entity* personnage = mShortStory->getSceneManager()->getEntity("Personnage");

    AnimationState *mAnimState;
    AnimationStateSet *set = personnage->getAllAnimationStates();
    AnimationStateIterator it = set->getAnimationStateIterator();

    //load animation
    while(it.hasMoreElements())
    {
        mAnimState = it.getNext();
        mAnimState->setEnabled(false);
    }

    personnage->getAnimationState("Idle1")->setEnabled(true);
    personnage->getAnimationState("Idle1")->addTime(evt.timeSinceLastFrame);
}

void Scene::idle2Personnage(const FrameEvent &evt){
    Entity* personnage = mShortStory->getSceneManager()->getEntity("Personnage");

    AnimationState *mAnimState;
    AnimationStateSet *set = personnage->getAllAnimationStates();
    AnimationStateIterator it = set->getAnimationStateIterator();

    //load animation
    while(it.hasMoreElements())
    {
        mAnimState = it.getNext();
        mAnimState->setEnabled(false);
    }

    personnage->getAnimationState("Idle2")->setEnabled(true);
    personnage->getAnimationState("Idle2")->addTime(evt.timeSinceLastFrame);
}

void Scene::idle3Personnage(const FrameEvent &evt){
    Entity* personnage = mShortStory->getSceneManager()->getEntity("Personnage");

    AnimationState *mAnimState;
    AnimationStateSet *set = personnage->getAllAnimationStates();
    AnimationStateIterator it = set->getAnimationStateIterator();

    //load animation
    while(it.hasMoreElements())
    {
        mAnimState = it.getNext();
        mAnimState->setEnabled(false);
    }

    personnage->getAnimationState("Idle3")->setEnabled(true);
    personnage->getAnimationState("Idle3")->addTime(evt.timeSinceLastFrame);
}

void Scene::kickPersonnage(const FrameEvent &evt){
    Entity* personnage = mShortStory->getSceneManager()->getEntity("Personnage");

    AnimationState *mAnimState;
    AnimationStateSet *set = personnage->getAllAnimationStates();
    AnimationStateIterator it = set->getAnimationStateIterator();

    //load animation
    while(it.hasMoreElements())
    {
        mAnimState = it.getNext();
        mAnimState->setEnabled(false);
    }

    personnage->getAnimationState("Kick")->setEnabled(true);
    personnage->getAnimationState("Kick")->addTime(evt.timeSinceLastFrame);
}

void Scene::sideKickPersonnage(const FrameEvent &evt){
    Entity* personnage = mShortStory->getSceneManager()->getEntity("Personnage");

    AnimationState *mAnimState;
    AnimationStateSet *set = personnage->getAllAnimationStates();
    AnimationStateIterator it = set->getAnimationStateIterator();

    //load animation
    while(it.hasMoreElements())
    {
        mAnimState = it.getNext();
        mAnimState->setEnabled(false);
    }

    personnage->getAnimationState("SideKick")->setEnabled(true);
    personnage->getAnimationState("SideKick")->addTime(evt.timeSinceLastFrame);
}

void Scene::death2Personnage(const FrameEvent &evt){
    Entity* personnage = mShortStory->getSceneManager()->getEntity("Personnage");

    if(!personnage->getAnimationState("Death2")->hasEnded()){
        AnimationState *mAnimState;
        AnimationStateSet *set = personnage->getAllAnimationStates();
        AnimationStateIterator it = set->getAnimationStateIterator();

        //load animation
        while(it.hasMoreElements())
        {
            mAnimState = it.getNext();
            mAnimState->setEnabled(false);
        }

        personnage->getAnimationState("Death2")->setLoop(false);
        personnage->getAnimationState("Death2")->setEnabled(true);
        personnage->getAnimationState("Death2")->addTime(evt.timeSinceLastFrame);
    }
}

void Scene::setCamera ()
{
    nCamera = nCharacCamera->createChildSceneNode("CameraNode");
    nCamera->attachObject(mShortStory->getCamera());

    //nCamera->setPosition(nCharacter->getPosition().x, nCharacter->getPosition().y, nCharacter->getPosition().z+dDistanceCharacCamera);
}

void Scene::setMeshes (bool withLod)
{
    if(withLod)
    {
        Ogre::MeshPtr voitureMesh = Ogre::MeshManager::getSingleton().load("Sedan02_license_R.mesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        Ogre::Mesh::LodValueList lodDList;
        lodDList.push_back(700);
        lodDList.push_back(1000);
        lodDList.push_back(1500);
        Ogre::ProgressiveMesh::generateLodLevels(voitureMesh.getPointer(),lodDList, Ogre::ProgressiveMesh::VRQ_PROPORTIONAL, 0.3);
    }

    Ogre::Entity* entVoiture = mShortStory->getSceneManager()->createEntity("Voiture", "Sedan02_license_R.mesh");
    entVoiture->setCastShadows(true);
    Ogre::SceneNode* VoitureNode = mShortStory->getSceneManager()->getRootSceneNode()->createChildSceneNode("Voiture");
    VoitureNode->attachObject(entVoiture);
    VoitureNode->setPosition(-500,43,-100);
    VoitureNode->scale(10,10,10);
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

Real Scene::getDistanceCharacterCamera()
{
    return dDistanceCharacCamera;
}
