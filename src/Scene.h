#ifndef SCENE_H
#define SCENE_H

#include <Ogre.h>
#include "ShortStory.h"
#include <Terrain/OgreTerrain.h>

/** La distance entre la tête du bonhomme et le sol */
#define HAUTEUR_PERS 110
/** distance de la caméra au perso en X */
#define FAR_PERS_X 25
/** distance de la caméra au perso en Y */
#define FAR_PERS_Y 15

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
    /** La lumiere dy terrain, initialisé dans lumiere, utilisé dans terrain */
	Light *terrainLight;
    /** Le truc pour gérer le terrain */
	TerrainGlobalOptions *mGlobals;
	/** true si le perso est dans l'immeuble, faux sinon */
	bool inBuilding;

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
	SceneNode* getImmeubleNode ();

	/** Récupère le noeud du terrain */
	SceneNode* getTerrainNode ();

	/** Récupère le noeud de la caméra et du personnage */
	SceneNode* getCharacterCameraNode ();

	/** Récupère le noeud de la caméra */
	SceneNode* getCameraNode ();

	/** Récupère le noeud du personnage */
	SceneNode* getCharacterNode ();

    /** Destruction de la fenetre */
    void destroyWindow();

    inline SceneNode* getCharacCamera ()
	{
		return nCharacCamera;
	}

    inline Real getDistanceCharacCamera () const
	{
		return dDistanceCharacCamera;
	}

    inline void setDistanceCharacCamera (Real distanceCharacCamera)
	{
		if (distanceCharacCamera > 25 && distanceCharacCamera < 300)
		{
			dDistanceCharacCamera = distanceCharacCamera;
			mShortStory->getCamera()->setPosition(FAR_PERS_X, FAR_PERS_Y, dDistanceCharacCamera);
		}
	}

    inline void setFPS ()
	{
		// on se met devant le mesh pour éviter de le voir de l'intérieur, sinon faudrait le suppr
		mShortStory->getCamera()->setPosition(-5, 12, -12);
	}

    inline void setThirdPerson ()
	{
		mShortStory->getCamera()->setPosition(FAR_PERS_X, FAR_PERS_Y, dDistanceCharacCamera);
	}

    inline bool isInBuilding () const
	{
		return inBuilding;
	}

    inline void setInBuilding (bool inBuilding)
	{
		this->inBuilding = inBuilding;
	}

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
    /** Met en place le robot */
    void setRobot();
	/** Met en place les différents meshes */
	void setMeshes (bool withLod);
	/** Met en place la caméra */
	void setCamera ();

};

#endif // SCENE_H
