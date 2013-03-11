#include "InputListener.h"
#include "OgreRay.h"
#include <sstream>

InputListener::InputListener (Scene *scene, SceneManager *scmanager, RenderWindow *wnd, Camera *camera) :
		mScene(scene), mSceneMgr(scmanager), mWindow(wnd), mCamera(camera), mContinuer(true), mgoUp(false), mMouvement(
		        Ogre::Vector3::ZERO), mCollisionVect(1, 1, 1), mVitesse(VITESSE), mVitesseRotation(VROTATION), detectionCollision(
		        true)
{
	startOIS();
}

InputListener::~InputListener ()
{
	WindowEventUtilities::removeWindowEventListener(mWindow, this);
	windowClosed(mWindow);
}

void InputListener::startOIS ()
{
	LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	mInputManager = InputManager::createInputSystem(pl);
	mMouse = static_cast<Mouse*>(mInputManager->createInputObject(OISMouse, true));
	mKeyboard = static_cast<Keyboard*>(mInputManager->createInputObject(OISKeyboard, true));

	windowResized(mWindow);
	WindowEventUtilities::addWindowEventListener(mWindow, this);
	mMouse->setEventCallback(this);
	mKeyboard->setEventCallback(this);
}

void InputListener::checkCollisions ()
{
	const int size = 4;
	// Rayon perso pour tester les collisions
	OgreRay ray(mSceneMgr);
	// résultat où est stocké la collision
	Ogre::Vector3 result;
	// place actuelle de la camera
	Ogre::Vector3 camera = mCamera->getPosition();
	// direction du rayon vertical
	Ogre::Vector3 vertical(0, -1, 0);
	// direction des vecteurs horizontaux (4 dans x, -x, z, -z)
	Ogre::Vector3 horizontals[4];

	// initialisation des horizontaux
	for (int i = 0; i < size; i++)
		horizontals[i] = Ogre::Vector3::ZERO;
	// -x
	horizontals[0].x = -1;
	// x
	horizontals[1].x = 1;
	// -z
	horizontals[2].z = -1;
	// z
	horizontals[3].z = 1;

	// détection verticale
	if (ray.RaycastFromPoint(camera, vertical, result))
	{
		Real dist = result.distance(camera);
		if (dist != DIST_VERTICAL)
		{
			mCamera->setPosition(camera.x, camera.y - dist + 100, camera.z);
		}
	}

	// détection horizontale
	for (int i = 0; i < size; i++)
	{
		if (ray.RaycastFromPoint(camera, horizontals[i], result))
		{
			Real dist = result.distance(camera);
			if (dist < DIST_HORIZONTAL)
			{
				if (horizontals[i].x)
					mMouvement.x = 0;
				if (horizontals[i].y)
					mMouvement.y = 0;
				if (horizontals[i].z)
					mMouvement.z = 0;
			}
		}
	}
}

bool InputListener::frameRenderingQueued (const FrameEvent& evt)
{
	if (mWindow->isClosed())
		return false;

	mKeyboard->capture();
	mMouse->capture();

	Ogre::Vector3 deplacement = Ogre::Vector3::ZERO;
	deplacement = mMouvement * mVitesse * evt.timeSinceLastFrame;

	deplacementNinja(evt, deplacement);

	mCamera->moveRelative(deplacement);

	if (mgoUp)
		mCamera->move(Ogre::Vector3(0, mVitesse * evt.timeSinceLastFrame, 0));

	if (detectionCollision)
		checkCollisions();

	return mContinuer;
}

void InputListener::windowResized (RenderWindow* wnd)
{
	unsigned int width, height, depth;
	int left, top;
	wnd->getMetrics(width, height, depth, left, top);

	const MouseState &ms = mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

void InputListener::windowClosed (RenderWindow* wnd)
{
	if (wnd == mWindow)
	{
		if (mInputManager)
		{
			mInputManager->destroyInputObject(mMouse);
			mInputManager->destroyInputObject(mKeyboard);

			InputManager::destroyInputSystem(mInputManager);
			mInputManager = 0;
		}
	}
}

bool InputListener::mouseMoved (const MouseEvent &e)
{
	mCamera->yaw(Degree(-mVitesseRotation * e.state.X.rel));
	mCamera->pitch(Degree(-mVitesseRotation * e.state.Y.rel));
	return true;
}

bool InputListener::mousePressed (const MouseEvent &arg, MouseButtonID id)
{
	// Rayon
	OgreRay ray(mSceneMgr);
	Ogre::Vector3 result;
	Ogre::Vector3 direction = mCamera->getDirection();
	if (ray.RaycastFromPoint(mCamera->getPosition(), direction, result))
	{
		printf("Your mouse is over the position %f,%f,%f\n", result.x, result.y, result.z);
		Ogre::Vector3 distance = mCamera->getPosition();
		printf("Distance : %lf\n", distance.distance(result));
	}
	else
	{
		printf("No mouse collision\n Are you looking the sky ?\n");
	}

	return true;
}

bool InputListener::mouseReleased (const MouseEvent &arg, MouseButtonID id)
{
	return true;
}

bool InputListener::keyPressed (const KeyEvent &e)
{
	switch (e.key)
	{
	case OIS::KC_ESCAPE:
		mContinuer = false;
		break;
#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		case OIS::KC_W:
		mMouvement.z = -1;
		break;
		case OIS::KC_S:
		mMouvement.z = 1;
		break;
		case OIS::KC_A:
		mMouvement.x = -1;
		break;
		case OIS::KC_D:
		mMouvement.x = 1;
		break;
#else
	case OIS::KC_Z:
		mMouvement.z = -1;
		break;
	case OIS::KC_S:
		mMouvement.z = 1;
		break;
	case OIS::KC_Q:
		mMouvement.x = -1;
		break;
	case OIS::KC_D:
		mMouvement.x = 1;
		break;
#endif
	case OIS::KC_LSHIFT:
		mVitesse = 3 * VITESSE;
		break;
	case OIS::KC_SPACE:
		mgoUp = true;
		break;
	case OIS::KC_END:
		detectionCollision = !detectionCollision;
		break;
	default:
		break;
	}

	return mContinuer;
}

bool InputListener::keyReleased (const KeyEvent &e)
{
	switch (e.key)
	{
#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	case OIS::KC_W:
	mMouvement.z = 0;
	break;
	case OIS::KC_S:
	mMouvement.z = 0;
	break;
	case OIS::KC_A:
	mMouvement.x = 0;
	break;
	case OIS::KC_D:
	mMouvement.x = 0;
	break;
#else
	case OIS::KC_Z:
		mMouvement.z = 0;
		break;
	case OIS::KC_S:
		mMouvement.z = 0;
		break;
	case OIS::KC_Q:
		mMouvement.x = 0;
		break;
	case OIS::KC_D:
		mMouvement.x = 0;
		break;
#endif
	case OIS::KC_LSHIFT:
		mVitesse = VITESSE;
		break;
	case OIS::KC_SPACE:
		mgoUp = false;
		break;
	default:
		break;
	}
	return true;
}

void InputListener::deplacementNinja (const FrameEvent& evt, Ogre::Vector3 deplacement)
{
	//selection de l'etat
	if (deplacement != Ogre::Vector3(0, 0, 0))
	{
		mPersonnageStat = WALK;
	}
	else
	{
		if ((mPersonnageStat != IDLE1) && (mPersonnageStat != IDLE2) && (mPersonnageStat != IDLE3))
		{
			mPersonnageStat = IDLE3;
		}
	}

	//application du mouvement
	switch (mPersonnageStat)
	{
	case WALK:
		mScene->walkPersonnage(evt);
		break;
	case IDLE1:
		mScene->idle1Personnage(evt);
		break;
	case IDLE2:
		mScene->idle2Personnage(evt);
		break;
	case IDLE3:
		mScene->idle3Personnage(evt);
		break;
	case KICK:
		mScene->kickPersonnage(evt);
		break;
	default:
		mPersonnageStat = IDLE3;
		break;
	}
}
