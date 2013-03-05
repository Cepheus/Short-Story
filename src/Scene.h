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
	Terrain *mTerrain;
	/** La lumiere dy terrain, initialisé dans lumiere, utilisé dans terrain */
	Light *terrainLight;
	/** Le truc pour gérer le terrain */
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
};

#endif // SCENE_H
