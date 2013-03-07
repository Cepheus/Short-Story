#ifndef INPUTLISTENER_H
#define INPUTLISTENER_H

#include <Ogre.h>
#include <OIS.h>

using namespace Ogre;
using namespace OIS;

/** Valeur par défaut de la vitesse de déplacement */
#define VITESSE 100
/** Valeur par défaut de la vitesse de rotation */
#define VROTATION 0.2

/**
 * Classe contenant la gestion des inputs (resize window, keyboard, mouse)
 */
class InputListener: public FrameListener, public WindowEventListener, public KeyListener, public MouseListener
{
private:
	/** Le scene manager, qui crée les objets */
	SceneManager* mSceneMgr;
	/** La fenêtre de l'application, créée dans ShortStory */
	RenderWindow* mWindow;
	/** La caméra à gérer avec les touches de clavier et la souris (créée dans ShortStory) */
	Camera* mCamera;
	/** permet de gérer les inputs */
	InputManager* mInputManager;
	/** Permet de capter les inputs de la souris */
	Mouse* mMouse;
	/** Permet de gérer les inputs du clavier */
	Keyboard* mKeyboard;
	// Déplacement
	/** Tant que vrai, le programe s'exécute */
	bool mContinuer;
	/** Vrai si espace est enfoncé (mode noclip / ghost = monter verticalement) */
	bool mgoUp;
	/** Utiliser pour bouger, contient le vecteur de déplacement de la caméra (par rapport au repère local de la cam) */
	Ogre::Vector3 mMouvement;
	/** Vitesse de déplacement, par défaut VITESSE */
	Real mVitesse;
	/** Vitesse de rotation, par défaut VROTATION */
	Real mVitesseRotation;

public:
	/**
	 * Constructeur
	 * @param sceneMgr le scene manager
	 * @param wnd la fenêtre du programme
	 * @param camera la caméra à gérer avec le clavier
	 * @note faudra surement utiliser le node contentant le perso + la cam au lieu de juste la cam
	 */
	InputListener (SceneManager *sceneMgr, RenderWindow *wnd, Camera *camera);

	/** destructeur */
	virtual ~InputListener ();

	/**
	 * @return la vitesse de déplacement
	 */
	const Real & getVitesse () const
	{
		return mVitesse;
	}

	/**
	 * @param vitesse la nouvelle vitesse de déplcaement
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
	void startOIS ();
// ci-dessous, l'implémentation des méthodes purement virtuelles permettant de gérer les inputs
	// FrameListener
	bool frameRenderingQueued (const FrameEvent& evt);

	// WindowEventListener
	virtual void windowResized (RenderWindow* rw);
	virtual void windowClosed (RenderWindow* rw);

	// MouseListener
	virtual bool mouseMoved (const MouseEvent &e);
	virtual bool mousePressed (const MouseEvent &arg, MouseButtonID id);
	virtual bool mouseReleased (const MouseEvent &arg, MouseButtonID id);

	// KeyListener
	virtual bool keyPressed (const KeyEvent &e);
	virtual bool keyReleased (const KeyEvent &e);
};

#endif // INPUTLISTENER_H