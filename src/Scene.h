#ifndef SCENE_H
#define SCENE_H

#include <Ogre.h>
#include <Terrain/OgreTerrain.h>

using namespace Ogre;

/**
 * Contient la sc�ne, avec tous les objets import�s et les mesh cr��s.
 */
class Scene
{
private:
    /** Le scene manager, qui cr�e les objets */
    SceneManager* mSceneMgr;
    /** Le terrain */
    Terrain *mTerrain;
    /** Le truc pour g�rer le terrain */
    TerrainGlobalOptions *mGlobals;

public:
    /**
     * Constructeur
     * @param scenemgr le sc�ne manager cr�� dans ShortStory
     */
    Scene(SceneManager *scenemgr);

    /** Destructeur */
    virtual ~Scene();

    /** Cr�� la sc�ne avec tous les meshs blablabla */
    void createScene ();

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
};

#endif // SCENE_H
