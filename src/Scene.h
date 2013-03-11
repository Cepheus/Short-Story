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
	SceneNode* mPersonnageNode;
    /** Le noeud camera */
	SceneNode* nCamera;
	/** Le noeud de l'immeuble */
	SceneNode* nImmeuble;
	/** Distance personnage/caméra */
	Real dDistanceCharacCamera;

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
    /** deplacement du personnage */
    void walkPersonnage();

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
