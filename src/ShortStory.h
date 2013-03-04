#ifndef SHORTSTORY_H
#define SHORTSTORY_H

#include <Ogre.h>

using namespace Ogre;

/**
 * Classe permettant d'initialiser un projet, et contenant la boucle de rendu.
 * Il faut commencer par appeler la m�thode Initialize() puis start() qui lancera la boucle de rendu.
 */
class ShortStory
{
private:
    /** La racine de Ogre */
    Root *mRoot;
    /** Le renderWindow, la fen�tre de l'appli */
    RenderWindow* mWindow;
    /** Le scene manager, qui cr�e les objets */
    SceneManager* mSceneMgr;
    /** La cam�ra */
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
     * Initialise les objets g�n�raux de la sc�ne.
     * Lumi�re par d�faut, cam�ra...
     */
    virtual void initScene ();
};

#endif // SHORTSTORY_H
