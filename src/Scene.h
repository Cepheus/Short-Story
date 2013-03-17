#ifndef SCENE_H
#define SCENE_H

#include <Ogre.h>
#include "ShortStory.h"
#include "Picking.h"
#include <Terrain/OgreTerrain.h>

/** La distance entre la tÃªte du bonhomme et le sol */
#define HAUTEUR_PERS 110
/** distance de la camÃ©ra au perso en X */
#define FAR_PERS_X 25
/** distance de la camÃ©ra au perso en Y */
#define FAR_PERS_Y 15

using namespace Ogre;

/**
 * Contient la scÃ¨ne, avec tous les objets importÃ©s et les mesh crÃ©Ã©s.
 */
class Scene
{
private:
	/** Le scene manager, qui crÃ©e les objets */
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
	/** Distance personnage/camÃ©ra */
	Real dDistanceCharacCamera;

	/** Le terrain heightmap */
	Terrain *mTerrain;
    /** La lumiere dy terrain, initialisÃ© dans lumiere, utilisÃ© dans terrain */
	Light *terrainLight;
    /** Le truc pour gÃ©rer le terrain */
	TerrainGlobalOptions *mGlobals;
	/** true si le perso est dans l'immeuble, faux sinon */
	bool inBuilding;
	/** false, window can be destroied, true, window is already destroied */
	bool windowIsDestroy;

public:
    /** Picking system */
	Picking picking;

public:
	/**
	 * Constructeur
	 * @param scenemgr le scÃ¨ne manager crÃ©Ã© dans ShortStory
	 */
	Scene (ShortStory *shortStory);

	/** Destructeur */
	virtual ~Scene ();

	/** CrÃ©Ã© la scÃ¨ne avec tous les meshs blablabla */
	void createScene ();

	/** RÃ©cupÃ¨re le noeud immeuble */
	SceneNode* getImmeubleNode ();

	/** RÃ©cupÃ¨re le noeud du terrain */
	SceneNode* getTerrainNode ();

	/** RÃ©cupÃ¨re le noeud de la camÃ©ra et du personnage */
	SceneNode* getCharacterCameraNode ();

	/** RÃ©cupÃ¨re le noeud de la camÃ©ra */
	SceneNode* getCameraNode ();

	/** RÃ©cupÃ¨re le noeud du personnage */
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
		// on se met devant le mesh pour Ã©viter de le voir de l'intÃ©rieur, sinon faudrait le suppr
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
	/** Met en place la lumiÃ¨re */
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
	/** Met en place les diffÃ©rents meshes */
	void setMeshes (bool withLod);
	/** Met en place la camÃ©ra */
	void setCamera ();

};

#endif // SCENE_H
