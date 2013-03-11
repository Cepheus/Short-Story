#ifndef SCENE_H
#define SCENE_H

#include <Ogre.h>
#include "ShortStory.h"
#include <Terrain/OgreTerrain.h>

using namespace Ogre;

/**
 * Contient la sc�ne, avec tous les objets import�s et les mesh cr��s.
 */
class Scene
{
private:
	/** Le scene manager, qui cr�e les objets */
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
	/** Distance personnage/cam�ra */
	Real dDistanceCharacCamera;

public:
	/**
	 * Constructeur
	 * @param scenemgr le sc�ne manager cr�� dans ShortStory
	 */
	Scene (ShortStory *shortStory);

	/** Destructeur */
	virtual ~Scene ();

	/** Cr�� la sc�ne avec tous les meshs blablabla */
	void createScene ();

    /** R�cup�re le noeud immeuble */
	SceneNode* getImmeubleNode();

	/** R�cup�re le noeud du terrain */
	SceneNode* getTerrainNode();

	/** R�cup�re le noeud de la cam�ra et du personnage */
	SceneNode* getCharacterCameraNode();

	/** R�cup�re le noeud de la cam�ra */
	SceneNode* getCameraNode();

	/** R�cup�re le noeud du personnage */
    SceneNode* getCharacterNode();

    /** R�cup�re la distance entre le personnage et la cam�ra */
    Real getDistanceCharacterCamera();

private:
	/** Met en place la lumi�re */
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
	/** Met en place les diff�rents meshes */
	void setMeshes ();
	/** Met en place la cam�ra */
	void setCamera ();
};

#endif // SCENE_H
