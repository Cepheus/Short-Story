#ifndef SHORTSTORY_H
#define SHORTSTORY_H

#include <Ogre.h>

using namespace Ogre;

/**
 * Classe permettant d'initialiser un projet, et contenant la boucle de rendu.
 * Il faut commencer par appeler la méthode Initialize() puis start() qui lancera la boucle de rendu.
 */
class ShortStory
{
private:
    /** La racine de Ogre */
    Root *mRoot;
    /** Le renderWindow, la fenêtre de l'appli */
    RenderWindow* mWindow;
    /** Le scene manager, qui crée les objets */
    SceneManager* mSceneMgr;
    /** La caméra */
    Camera* mCamera;

public:
    /** Constructeur */
    ShortStory();

    /** Destructeur */
    virtual ~ShortStory();

    /** Initialise l'appli Ogre, notamment la gestion des inputs */
    bool Initialize ();

    /** Lance la boucle de rendu */
    bool start ();

    Root * getRoot ()
    {
        return mRoot;
    }

    RenderWindow * getWindow ()
    {
        return mWindow;
    }

    SceneManager * getSceneManager ()
    {
        return mSceneMgr;
    }

    Camera * getCamera ()
    {
        return mCamera;
    }

private:
    /**
     * Initialise les objets généraux de la scène.
     * Lumière par défaut, caméra...
     */
    virtual void initScene ();
};

#endif // SHORTSTORY_H
