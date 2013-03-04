#ifndef INPUTLISTENER_H
#define INPUTLISTENER_H

#include <Ogre.h>
#include <OIS.h>

using namespace Ogre;
using namespace OIS;

/** Valeur par d�faut de la vitesse de d�placement */
#define VITESSE 100
/** Valeur par d�faut de la vitesse de rotation */
#define VROTATION 0.2

/**
 * Classe contenant la gestion des inputs (resize window, keyboard, mouse)
 */
class InputListener: public FrameListener, public WindowEventListener, public KeyListener, public MouseListener
{
private:
    /** Le scene manager, qui cr�e les objets */
    SceneManager* mSceneMgr;
    /** La fen�tre de l'application, cr��e dans ShortStory */
    RenderWindow* mWindow;
    /** La cam�ra � g�rer avec les touches de clavier et la souris (cr��e dans ShortStory) */
    Camera* mCamera;
    /** permet de g�rer les inputs */
    InputManager* mInputManager;
    /** Permet de capter les inputs de la souris */
    Mouse* mMouse;
    /** Permet de g�rer les inputs du clavier */
    Keyboard* mKeyboard;
    // D�placement
    /** Tant que vrai, le programe s'ex�cute */
    bool mContinuer;
    /** Vrai si espace est enfonc� (mode noclip / ghost = monter verticalement) */
    bool mgoUp;
    /** Utiliser pour bouger, contient le vecteur de d�placement de la cam�ra (par rapport au rep�re local de la cam) */
    Ogre::Vector3 mMouvement;
    /** Vitesse de d�placement, par d�faut VITESSE */
    Real mVitesse;
    /** Vitesse de rotation, par d�faut VROTATION */
    Real mVitesseRotation;

public:
    /**
     * Constructeur
     * @param sceneMgr le scene manager
     * @param wnd la fen�tre du programme
     * @param camera la cam�ra � g�rer avec le clavier
     * @note faudra surement utiliser le node contentant le perso + la cam au lieu de juste la cam
     */
    InputListener(SceneManager *sceneMgr, RenderWindow *wnd, Camera *camera);

    /** destructeur */
    virtual ~InputListener();

    /**
     * @return la vitesse de d�placement
     */
    const Real & getVitesse () const
    {
        return mVitesse;
    }

    /**
     * @param vitesse la nouvelle vitesse de d�plcaement
     */
    void setVitesse (const Real& vitesse)
    {
        mVitesse = vitesse;
    }

    /**
     * @return la vitesse de rotation
     */
    const Real & getVitesseRotation () const
    {
        return mVitesseRotation;
    }

    /**
     * @param vitesse la nouvelle vitesse de rotation
     */
    void setVitesseRotation (const Real& vitesse)
    {
        mVitesseRotation = vitesse;
    }

protected:
    /** Initialise la gestion des inputs */
    void startOIS();
// ci-dessous, l'impl�mentation des m�thodes purement virtuelles permettant de g�rer les inputs
    // FrameListener
    bool frameRenderingQueued(const FrameEvent& evt);

    // WindowEventListener
    virtual void windowResized(RenderWindow* rw);
    virtual void windowClosed(RenderWindow* rw);

    // MouseListener
    virtual bool mouseMoved(const MouseEvent &e);
    virtual bool mousePressed( const MouseEvent &arg, MouseButtonID id );
    virtual bool mouseReleased( const MouseEvent &arg, MouseButtonID id );

    // KeyListener
    virtual bool keyPressed(const KeyEvent &e);
    virtual bool keyReleased(const KeyEvent &e);
};

#endif // INPUTLISTENER_H
