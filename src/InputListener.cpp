#include "InputListener.h"
#include "OgreRay.h"
#include <sstream>
#include <utility>

InputListener::InputListener (Scene *scene, Animations * animations, AnimationsAuto * animationsAuto,
        SceneManager *scmanager, RenderWindow *wnd, Camera *camera) :
		mScene(scene), mAnimations(animations), mAnimationsAuto(animationsAuto), mSceneMgr(scmanager), mWindow(wnd), mCamera(
		        camera), mContinuer(true), mgoUp(false), mgoDown(false), mMouvement(Ogre::Vector3::ZERO), mCollisionVect(
		        1, 1, 1), mVitesse(VITESSE), mVitesseRotation(VROTATION), detectionCollision(true), isFPS(false)
{
	startOIS();
	stateJeu = false;
	//mAnimationsAuto->setAnimation();
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

void InputListener::Collisions (SceneNode * ObjectNode, MovableObject* objectMove, bool detectLesMurs,
        Real distanceFromGround, bool chat)
{

	// Rayon perso pour tester les collisions
	OgreRay ray(mSceneMgr, objectMove); //
	ray.setToBeTouched(mScene->getImmeubleNode()->getAttachedObject(0));
	// résultat où est stocké la collision
	Ogre::Vector3 result(0, 0, 0);
	double resultX = 0;
	// résultat pour la collision avec le terrain
	std::pair<bool, Ogre::Vector3> resultTerrain;
	bool resultGround;

	// place actuelle du perso
	Ogre::Vector3 pos_node = ObjectNode->getPosition();
	Ogre::Vector3 pos_node2 = ObjectNode->getPosition();
	Ogre::Quaternion orient_node = ObjectNode->getOrientation();

	// direction du rayon vertical
	Ogre::Vector3 vertical(0, -1, 0);
	Ogre::Vector3 honrizontal_X(1, 0, 0);
	Ogre::Vector3 honrizontal_Z(0, 0, 1);

	// détection verticale
	resultTerrain = mScene->getTerrain()->rayIntersects(Ray(pos_node, vertical));
	resultGround = ray.RaycastFromPoint(pos_node, vertical, result);
	if (resultGround || resultTerrain.first)
	{
		Real dist = 0, tmp = 0;

		if (resultTerrain.first)
			dist = resultTerrain.second.distance(pos_node);
		if (resultGround)
		{
			if ((tmp = result.distance(pos_node)) < dist)
				dist = tmp;
		}

		if (resultTerrain.first && pos_node.distance(resultTerrain.second) < dist)
			dist = pos_node.distance(resultTerrain.second);

		if (dist > distanceFromGround + 1)
		{
			ObjectNode->translate(Ogre::Vector3(0, (distanceFromGround - dist) / 10, 0), SceneNode::TS_LOCAL);
		}
		else if (dist < distanceFromGround - 1)
		{
			ObjectNode->translate(Ogre::Vector3(0, distanceFromGround - dist, 0), SceneNode::TS_LOCAL);
		}
		mIsInBuilding = ray.isTouched();
		mScene->setInBuilding(mIsInBuilding);
	}
	//On remonte le rayon du chat sinon reste bloquer sur les marches
	if (chat)
		pos_node2.y = pos_node2.y + 30;
	//On teste chaque axe X -X Z et -Z
	//On garde la valeur de resultX poru lros de la vérification de l'autre mur on ne puisse pas passer par les coins
	if (ray.RaycastFromPoint(pos_node2, honrizontal_X, result))
	{
		if (result.distance(pos_node2) < 50)
		{
			//On vérifie l'oriantation du personnage pour le bloquer dans le sens du mur
			if (fabs(orient_node.x) >= 0.7)
			{
				ObjectNode->setPosition(result.x + 50, pos_node.y, pos_node.z);
				resultX = result.x + 50;
			}
			else
			{
				ObjectNode->setPosition(result.x - 50, pos_node.y, pos_node.z);
				resultX = result.x - 50;
			}
		}
		else
		{

			resultX = pos_node.x;
		}
	}

	if (ray.RaycastFromPoint(pos_node2, -honrizontal_X, result))
	{
		if (result.distance(pos_node2) < 50)
		{
			if (fabs(orient_node.x) >= 0.7)
			{
				ObjectNode->setPosition(result.x - 50, pos_node.y, pos_node.z);
				resultX = result.x - 50;
			}
			else
			{
				ObjectNode->setPosition(result.x + 50, pos_node.y, pos_node.z);
				resultX = result.x + 50;
			}
		}
	}
	if (ray.RaycastFromPoint(pos_node2, honrizontal_Z, result))
	{
		if (result.distance(pos_node2) < 50)
		{
			if (fabs(orient_node.x) >= 0.7)
			{
				ObjectNode->setPosition(resultX, pos_node.y, result.z + 50);
			}
			else
			{
				ObjectNode->setPosition(resultX, pos_node.y, result.z - 50);
			}
		}
	}
	if (ray.RaycastFromPoint(pos_node2, -honrizontal_Z, result))
	{
		if (result.distance(pos_node2) < 50)
		{
			if (fabs(orient_node.x) >= 0.7)
			{
				ObjectNode->setPosition(resultX, pos_node.y, result.z - 50);
			}
			else
			{
				ObjectNode->setPosition(resultX, pos_node.y, result.z + 50);
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

	if (!stateJeu)
	{
		mCollisionVect.x = 1;
		mCollisionVect.y = 1;
		mCollisionVect.z = 1;
		if (detectionCollision)
			Collisions(mScene->getCharacCamera(), mScene->getCharacterNode()->getAttachedObject(0), true, HAUTEUR_PERS,
			        false);

		Ogre::Vector3 deplacement = Ogre::Vector3::ZERO;
		deplacement = mMouvement * mCollisionVect * mVitesse * evt.timeSinceLastFrame;

		deplacementNinja(evt, deplacement);

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
		else
		{
			if (mIsInBuilding)
			{
				isFPS = true;
				mScene->setFPS();
			}
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

			mStatInBuilding = mIsInBuilding;
		}

		//Déplacement du chat
		Ogre::Vector3 pers_pos = mScene->getCharacterCameraNode()->getPosition();
		Ogre::Vector3 chat_pos = mScene->getCatNode()->getPosition();
		Ogre::Vector3 move_cat;

		move_cat.x = pers_pos.x - chat_pos.x;
		move_cat.z = pers_pos.z - chat_pos.z;
		move_cat.y = 0;
		move_cat.normalise();

		//Déplacment du chat selon le vecteur directeur, celui-ci reste un peu éloigner du personnage 200,200 à modifier si nécéssaire
		if ((fabs(pers_pos.x - chat_pos.x) > 200) || (fabs(pers_pos.z - chat_pos.z) > 200))
		{
			mScene->getCatNode()->translate(move_cat * 4);
			//Animation du chat
			deplacementChat(evt, move_cat);
		}
		else
		{
			deplacementChat(evt, move_cat.ZERO);
		}

		//Pour que le chat regarde vers le personnage
		Ogre::Vector3 orientation = mScene->getCatNode()->getOrientation() * Ogre::Vector3::UNIT_X;
		Ogre::Quaternion quat = orientation.getRotationTo(move_cat);
		mScene->getCatNode()->rotate(quat);

		//Collisions du chat
		Collisions(mScene->getCatNode(), mScene->getCatNode()->getAttachedObject(0), true, 40, true);
	}
	else
		filmFin(evt);

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

	if ((zoom = e.state.Z.rel) != 0 && !isFPS)
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
	Ogre::Vector3 posCamera, posVoiture, posCharacter;
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
		std::cout << "Character: " << posCharacter.x << " " << posCharacter.y << " " << posCharacter.z << std::endl;
		break;
	case OIS::KC_L:
		if (mScene->picking.isPicked(mScene->getCharacterCameraNode(), mSceneMgr->getSceneNode("windowNode"), 100.f))
			mScene->destroyWindow();
		break;
    case OIS::KC_H:
        if(mScene->isExistDoor())
            if(mScene->picking.isPicked(mScene->getCharacterCameraNode(),mSceneMgr->getSceneNode("Door"),500.f))
                mScene->openDoor();
		break;
	case OIS::KC_B:
		mScene->destroyWindow();
		break;
	case OIS::KC_M:
		stateJeu = true;
		mAnimationsAuto->setAnimation();
		break;
	case OIS::KC_R:
		stateJeu = true;
		mAnimationsAuto->setAnimation();
		mAnimationsAuto->replay();
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

void InputListener::filmFin (const FrameEvent& evt)
{
	mAnimationsAuto->animationFin(evt);
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

void InputListener::deplacementChat (const FrameEvent& evt, Ogre::Vector3 deplacement)
{
	if (deplacement != deplacement.ZERO)
	{
		mAnimations->walkCat(evt);
	}
	else
	{
		mAnimations->waitCat(evt);
	}
}

