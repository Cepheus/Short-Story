#include "InputListener.h"
#include "OgreRay.h"
#include <sstream>

InputListener::InputListener (Scene *scene, Animations * animations, SceneManager *scmanager, RenderWindow *wnd, Camera *camera) :
        mScene(scene), mAnimations(animations), mSceneMgr(scmanager), mWindow(wnd), mCamera(camera), mContinuer(true), mgoUp(false), mgoDown(
		        false), mMouvement(Ogre::Vector3::ZERO), mCollisionVect(1, 1, 1), mVitesse(VITESSE), mVitesseRotation(
		        VROTATION), detectionCollision(true), isFPS(false)
{
	startOIS();
}

InputListener::~InputListener ()
{
	WindowEventUtilities::removeWindowEventListener(mWindow, this);
	windowClosed(mWindow);
	mStatInBuilding = false;
	mIsInBuilding = false;
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

void InputListener::checkCollisions (SceneNode *toMove, bool detectLesMurs)
{
	const int size = 8, moveOffset = 40, detectOffset = 2;
	// Rayon perso pour tester les collisions
	OgreRay ray(mSceneMgr, mScene->getCharacterNode()->getAttachedObject(0));
	ray.setToBeTouched(mScene->getImmeubleNode()->getAttachedObject(0));
	// résultat où est stocké la collision
	Ogre::Vector3 result;
	// place actuelle du perso
	Ogre::Vector3 nperso = toMove->getPosition();
	// direction du rayon vertical
	Ogre::Vector3 vertical(0, -1, 0);

	// détection verticale
	if (ray.RaycastFromPoint(nperso, vertical, result))
	{
		Real dist = result.distance(nperso);
		if (dist != DIST_VERTICAL)
		{
			toMove->setPosition(nperso.x, nperso.y - dist + DIST_VERTICAL, nperso.z);
		}
		mIsInBuilding = ray.isTouched();
		mScene->setInBuilding(mIsInBuilding);
	}

	if (detectLesMurs)
	{
		// direction des vecteurs horizontaux (4 dans x, -x, z, -z)
		Quaternion quaternions[size];
		// tmp vector pour les côtés
		Ogre::Vector3 tmp;

		// initialisation des horizontaux
		for (int i = 0; i < size; i++)
			quaternions[i] = Quaternion::IDENTITY;
		// x
		quaternions[0].x = 1;
		// -x
		quaternions[1].x = -1;
		// z
		quaternions[2].z = 1;
		// -z
		quaternions[3].z = -1;
		// x, z
		quaternions[4].x = 1;
		quaternions[4].z = 1;
		// -x, z
		quaternions[5].x = -1;
		quaternions[5].z = 1;
		// x, -z
		quaternions[6].x = 1;
		quaternions[6].z = -1;
		// -x, -z
		quaternions[7].x = -1;
		quaternions[7].z = -1;
		for (int i = 0; i < size; i++)
			quaternions[i] = toMove->convertLocalToWorldOrientation(quaternions[i]);

		// détection horizontale
		for (int i = 0; i < size; i++)
		{
			tmp.x = quaternions[i].x;
			tmp.y = quaternions[i].y;
			tmp.z = quaternions[i].z;

			if (ray.RaycastFromPoint(nperso, tmp, result))
			{
				Real dist = result.distance(nperso);
				if (dist < DIST_HORIZONTAL)
				{
					switch (i)
					{
					case 0:
						if (mMouvement.x == 1)
						{
							mMouvement.x = 0;
							if (dist < DIST_HORIZONTAL - detectOffset)
								toMove->setPosition(nperso.x - moveOffset, nperso.y, nperso.z);
						}
						break;
					case 1:
						if (mMouvement.x == -1)
						{
							mMouvement.x = 0;
							if (dist < DIST_HORIZONTAL - detectOffset)
								toMove->setPosition(nperso.x + moveOffset, nperso.y, nperso.z);
						}
						break;
					case 2:
						if (mMouvement.z == 1)
						{
							mMouvement.z = 0;
							if (dist < DIST_HORIZONTAL - detectOffset)
								toMove->setPosition(nperso.x, nperso.y, nperso.z - moveOffset);
						}
						break;
					case 3:
						if (mMouvement.z == -1)
						{
							mMouvement.z = 0;
							if (dist < DIST_HORIZONTAL - detectOffset)
								toMove->setPosition(nperso.x, nperso.y, nperso.z + moveOffset);
						}
						break;
					case 4:
						if (mMouvement.x == 1)
						{
							mMouvement.x = 0;
							if (dist < DIST_HORIZONTAL - detectOffset)
								toMove->setPosition(nperso.x - moveOffset, nperso.y, nperso.z);
						}
						if (mMouvement.z == 1)
						{
							mMouvement.z = 0;
							if (dist < DIST_HORIZONTAL - detectOffset)
								toMove->setPosition(nperso.x, nperso.y, nperso.z - moveOffset);
						}
						break;
					case 5:
						if (mMouvement.x == -1)
						{
							mMouvement.x = 0;
							if (dist < DIST_HORIZONTAL - detectOffset)
								toMove->setPosition(nperso.x + moveOffset, nperso.y, nperso.z);
						}
						if (mMouvement.z == 1)
						{
							mMouvement.z = 0;
							if (dist < DIST_HORIZONTAL - detectOffset)
								toMove->setPosition(nperso.x, nperso.y, nperso.z - moveOffset);
						}
						break;
					case 6:
						if (mMouvement.x == 1)
						{
							mMouvement.x = 0;
							if (dist < DIST_HORIZONTAL - detectOffset)
								toMove->setPosition(nperso.x - moveOffset, nperso.y, nperso.z);
						}
						if (mMouvement.z == -1)
						{
							mMouvement.z = 0;
							if (dist < DIST_HORIZONTAL - detectOffset)
								toMove->setPosition(nperso.x, nperso.y, nperso.z + moveOffset);
						}
						break;
					case 7:
						if (mMouvement.x == -1)
						{
							mMouvement.x = 0;
							if (dist < DIST_HORIZONTAL - detectOffset)
								toMove->setPosition(nperso.x + moveOffset, nperso.y, nperso.z);
						}
						if (mMouvement.z == -1)
						{
							mMouvement.z = 0;
							if (dist < DIST_HORIZONTAL - detectOffset)
								toMove->setPosition(nperso.x, nperso.y, nperso.z + moveOffset);
						}
						break;
					default:
						break;
					}
				}
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

	mCollisionVect.x = 1;
	mCollisionVect.y = 1;
	mCollisionVect.z = 1;
	if (detectionCollision)
		checkCollisions(mScene->getCharacCamera(), true);

	Ogre::Vector3 deplacement = Ogre::Vector3::ZERO;
	deplacement = mMouvement * mCollisionVect * mVitesse * evt.timeSinceLastFrame;

	deplacementNinja(evt, deplacement);
	deplacementRobot(evt);

	mScene->getCharacterCameraNode()->translate(deplacement, SceneNode::TS_LOCAL);

	if (!detectionCollision)
	{
		if (mgoUp)
			mScene->getCharacterCameraNode()->translate(Ogre::Vector3(0, mVitesse * evt.timeSinceLastFrame, 0),
			        SceneNode::TS_LOCAL);
		if (mgoDown)
			mScene->getCharacterCameraNode()->translate(Ogre::Vector3(0, -mVitesse * evt.timeSinceLastFrame, 0),
			        SceneNode::TS_LOCAL);
	}

	if (mIsInBuilding != mStatInBuilding)
	{
		if (mIsInBuilding)
		{
			mSceneMgr->getSceneNode("CharacterRainNode")->setVisible(false);
			mSceneMgr->getSceneNode("rainGaucheNode")->setVisible(true);
			mSceneMgr->getSceneNode("rainDevantNode")->setVisible(true);
		}
		else
		{
			mSceneMgr->getSceneNode("CharacterRainNode")->setVisible(true);
			mSceneMgr->getSceneNode("rainGaucheNode")->setVisible(false);
			mSceneMgr->getSceneNode("rainDevantNode")->setVisible(false);
		}
	}
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
	Real zoom;
	Quaternion orientationCamera;

	mScene->getCharacterCameraNode()->yaw(Degree(-mVitesseRotation * e.state.X.rel), SceneNode::TS_LOCAL);
	mScene->getCameraNode()->pitch(Degree(-mVitesseRotation * e.state.Y.rel));

	orientationCamera = mScene->getCameraNode()->getOrientation();
	if (detectionCollision)
	{
		if (orientationCamera.x > 0.5)
			orientationCamera.x = 0.5;
		if (orientationCamera.x < -0.5)
			orientationCamera.x = -0.5;
		mScene->getCameraNode()->setOrientation(orientationCamera);
	}

	if ((zoom = e.state.Z.rel) != 0)
		mScene->setDistanceCharacCamera(mScene->getDistanceCharacCamera() - zoom / 10);

	return true;
}

bool InputListener::mousePressed (const MouseEvent &arg, MouseButtonID id)
{
	// Rayon
	OgreRay ray(mSceneMgr, mScene->getCharacterNode()->getAttachedObject(0));
	Ogre::Vector3 result;
	Ogre::Vector3 position = mScene->getCharacCamera()->getPosition();
	Ogre::Vector3 direction = Ogre::Vector3::NEGATIVE_UNIT_Y;

	printf("position: %f, %f, %f\n", position.x, position.y, position.z);
	if (ray.RaycastFromPoint(position, direction, result))
	{
		printf("Your mouse is over the position %f,%f,%f\n", result.x, result.y, result.z);
		Ogre::Vector3 distance = position;
		printf("Distance : %f\n", distance.distance(result));
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
	Ogre::Vector3 posCamera, posVoiture,posCharacter;
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
	case OIS::KC_LCONTROL:
		mgoDown = true;
		break;
	case OIS::KC_END:
		detectionCollision = !detectionCollision;
		break;
	case OIS::KC_P:
		isFPS = !isFPS;
		if (isFPS)
			mScene->setFPS();
		else
			mScene->setThirdPerson();
		break;
	case OIS::KC_J:
		posCamera = mCamera->getPosition();
		posVoiture = mSceneMgr->getSceneNode("Voiture")->getPosition();
		mSceneMgr->getSceneNode("Voiture");
		std::cout << "Distance Voiture - Camera : " << posCamera.distance(posVoiture) << std::endl;
		break;
    case OIS::KC_K:
        posCharacter = mScene->getCharacterCameraNode()->getPosition();
        std::cout << "Character: " << posCharacter.x<<" "<<posCharacter.y<<" "<<posCharacter.z<<std::endl;
        break;
    case OIS::KC_L:
        if(mScene->picking.isPicked(mScene->getCharacterCameraNode(),mSceneMgr->getSceneNode("windowNode"),100.f))
            mScene->destroyWindow();
        break;
    case OIS::KC_B:
        mScene->destroyWindow();
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
	case OIS::KC_LCONTROL:
		mgoDown = false;
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
		mPersonnageStat = pWALK;
	}
	else
	{
		if ((mPersonnageStat != pIDLE1) && (mPersonnageStat != pIDLE2) && (mPersonnageStat != pIDLE3))
		{
			mPersonnageStat = pIDLE3;
		}
	}

	//application du mouvement
	switch (mPersonnageStat)
	{
	case pWALK:
        mAnimations->walkPersonnage(evt);
		break;
	case pIDLE1:
        mAnimations->idle1Personnage(evt);
		break;
	case pIDLE2:
        mAnimations->idle2Personnage(evt);
		break;
	case pIDLE3:
        mAnimations->idle3Personnage(evt);
		break;
	case pKICK:
        mAnimations->kickPersonnage(evt);
		break;
	case pSIDEKICK:
        mAnimations->sideKickPersonnage(evt);
		break;
	case pDEATH2:
        mAnimations->death2Personnage(evt);
		break;
	default:
		mPersonnageStat = pIDLE3;
		break;
	}
}

void InputListener::deplacementRobot (const FrameEvent& evt)
{
    mAnimations->displayRobot(Animations::TRACK0,evt);

}
