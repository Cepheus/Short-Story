#ifndef SCENE_H
#define SCENE_H

#include <Ogre.h>
#include "ShortStory.h"
#include <Terrain/OgreTerrain.h>

using namespace Ogre;

/**
 * Contient la scène, avec tous les objets importés et les mesh créés.
 */
class Scene
{
private:
	/** Le scene manager, qui crée les objets */
	ShortStory* mShortStory;
	/** Le terrain */
    SceneNode* nTerrain;
    /** Le noeuf personnage/camera */
    SceneNode* nCharacCamera;
    /** Le noeud personnage */
	SceneNode* nCharacter;
    /** Le noeud camera */
	SceneNode* nCamera;
	/** Le noeud de l'immeuble */
	SceneNode* nImmeuble;
	/** Distance personnage/caméra */
	Real dDistanceCharacCamera;

    /** Le terrain heightmap */
    Terrain *mTerrain;
    /** La lumiere dy terrain, initialis� dans lumiere, utilis� dans terrain */
    Light *terrainLight;
    /** Le truc pour g�rer le terrain */
    TerrainGlobalOptions *mGlobals;

public:
	/**
	 * Constructeur
	 * @param scenemgr le scène manager créé dans ShortStory
	 */
	Scene (ShortStory *shortStory);

	/** Destructeur */
	virtual ~Scene ();

	/** Créé la scène avec tous les meshs blablabla */
	void createScene ();

    /** Récupère le noeud immeuble */
	SceneNode* getImmeubleNode();

	/** Récupère le noeud du terrain */
	SceneNode* getTerrainNode();

	/** Récupère le noeud de la caméra et du personnage */
	SceneNode* getCharacterCameraNode();
    void walkPersonnage(const FrameEvent& evt);
    void idle1Personnage(const FrameEvent &evt);
    void idle2Personnage(const FrameEvent &evt);
    void idle3Personnage(const FrameEvent &evt);
    void kickPersonnage(const FrameEvent &evt);
    void sideKickPersonnage(const FrameEvent &evt);
    void death2Personnage(const FrameEvent &evt);

	/** Récupère le noeud de la caméra */
	SceneNode* getCameraNode();

	/** Récupère le noeud du personnage */
    SceneNode* getCharacterNode();

    /** Récupère la distance entre le personnage et la caméra */
    Real getDistanceCharacterCamera();

private:
	/** Met en place la lumière */
	void setLight ();
	/** Met en place le terrain */
	void setTerrain ();
	/** Met en place le ciel */
	void setSky ();
	/** Met en place la pluie */
	void setRain ();
	/** Met en place l'immeuble */
	void setImmeuble ();
	/** Met en place le personnage */
	void setPersonnage ();
	/** Met en place les différents meshes */
	void setMeshes ();
	/** Met en place la caméra */
	void setCamera ();
};

#endif // SCENE_H
